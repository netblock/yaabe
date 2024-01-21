# gmc.py is a script to process asic_reg/gmc/* to output something that is a
# little more readable.

#gmc.py mode files
# mode = 0
# Convert an inputted GMC file into C bitfields, with relevant register number
# definition adjacent. 
# If multiple shmask-d pairs are given, find commonality and associate versions.
# gmc.py 0 gmc_out.h gmc_8_1_sh_mask.h gmc_8_1_d.h
# gmc.py 0 gmc_out.h gmc_8_1_sh_mask.h gmc_8_1_d.h gmc_7_0_sh_mask.h gmc_7_0_d.h

# mode = 1
# intersect bitfields with a collection of register values, to find what
# bitfields the values are about. Specifically, find all bitfields that keep
# the 'rsvd' fields zero in value.
# gmc.py 1 gmc_8_1_sh_mask.h # # # #

from gmpy2 import popcount
from sys import argv

class bitfield:
	name:str
	entries:list # bitfield entries [{name hi lo}]
	ver_addr:dict # version:(name, address) sets; by-version association
	addr_ver:dict # address:(name, ver, ver..) sets; by-address association


	longest_named:dict

	def add_maskshift(self, name:str, mask:int, shift:int):
		# inclusvie [] bitfield notation. [3:0] is 4 bits
		num_bits = popcount(mask)
		if (num_bits == 0):
			return
		self.entries.append({
			"name": name,
			"hi": (shift + num_bits - 1),
			"lo": shift,
		})
		assert (32 > (shift + num_bits - 1)),name # AMD's regs should be 32-bit

	def sort(self):
		self.entries.sort(key=lambda e: e["lo"])

	def find_reserved(self):
		# assumes the entries are in order
		# find if there's any undefined gaps in the bitfield
		reserved_n = 0
		high = 0; wol = 0; empty_bits = 0
		i = 0;
		end = len(self.entries) - 1
		while (i <= end):
			high = self.entries[i]["hi"]
			if (end - i): 
				wol = self.entries[i+1]["lo"]
			else:
				wol = 32 # 32-bit registers
			empty_bits = wol - high - 1;
			assert (empty_bits >= 0), self.entries[i]["name"]
			if empty_bits:
				self.entries.insert(i+1, {
					"name": ("rsvd%u" % reserved_n),
					"hi": high + empty_bits,
					"lo": high + 1,
				})
				reserved_n += 1
				end += 1
				i += 1
			i += 1

	def find_longest_named(self):
		longest = self.entries[0]
		len_long = len(longest["name"])
		len_e = 0
		for e in self.entries[1:]:
			len_e = len(e["name"])
			if len_e >= len_long: # find little-endian leftmost longest
				longest = e
				len_long = len_e
		self.longest_named = longest
		return longest

	def __init__(self, name:str):
		self.name = name
		self.longest = None
		self.entries = []
		self.ver_addr = {}
		self.addr_ver = {}

def text_to_dict(file_text:str):
	# very primitive preprocessor parser
	pp_dict = {}
	end = len(file_text)
	i = 0
	line = ""
	parts = []
	while (i < end):
		if file_text[i:i+len("/*")] == "/*": # skip /* */ comments
			i+=2
			while ((i < end) and (file_text[i:i+len("*/")] != "*/")):
				i+=1
		elif file_text[i:i+len("#define")] == "#define":
			line = file_text[i:].split("\n",1)[0]
			i += len(line) + 1
			line = line.lower() # santise out mixed-case
			parts = line.split()
			if len(parts) == 3:
				assert(parts[1] not in pp_dict.keys())
				pp_dict[parts[1]] = parts[2]
		else:
			i+=1
	return pp_dict

def shmask_filetext_to_bitfields(file_text:str):
	# the mask-shift pairs in the sh_mask.h files may not be physically
	# adjacent within the header file, so do a primitive preprocessor parse for
	# a basic namespace (the python dict). 
	pp_dict = text_to_dict(file_text)
	assert(0 == (len(pp_dict) % 2))

	bitfields = []
	bf_i = -1;
	current_bf_name = ""
	old_bf_names = []

	mask = 0; shift = 0

	keys = list(pp_dict.keys())
	keys.sort()
	for k in keys:
		if (k[-4:] != "mask"): # enter with a mask then find shift
			continue
		mask_key = k
		shift_key = k[:-4] + "_shift"
		name_parts = shift_key.split("__")

		if (name_parts[0] != current_bf_name):
			assert(name_parts[0] not in old_bf_names)
			old_bf_names.append(current_bf_name)
			current_bf_name = name_parts[0]
			bitfields.append(bitfield(name_parts[0]))
			bf_i += 1

		# python int() doesn't like C int suffixes
		if (pp_dict[mask_key][-1] == "l"):
			mask = int(pp_dict[mask_key][:-1], 16)
		else:
			mask = int(pp_dict[mask_key], 16)
		if (pp_dict[shift_key][-1] == "l"):
			shift = int(pp_dict[shift_key][:-1], 16)
		else:
			shift = int(pp_dict[shift_key], 16)

		bitfields[bf_i].add_maskshift(name_parts[1], mask, shift)

	bitfields_dict = {}
	for b in bitfields:
		b.sort() # sort because we added in a disordered way
		b.find_reserved()
		bitfields_dict[b.name] = b

	return bitfields_dict


def bitfields_attach_reg_ids(version:str, bitfields:dict, reg_name_id_pairs:dict):
	bf_name = ""
	address = 0
	for reg_name in reg_name_id_pairs:
		if reg_name[:2] in ("ix", "mm"):
			bf_name = reg_name[2:]
		else:
			bf_name = reg_name
		if bf_name in bitfields:
			bf = bitfields[bf_name]
			assert(version not in bf.ver_addr.keys())
			address = int(reg_name_id_pairs[reg_name], 16)
			bf.ver_addr[version] = (reg_name, address)
			bf.addr_ver[address] = [reg_name, version]
		else:
			print("WARNING: %s: %s has no shmask!" % (version, bf_name.upper()))


def bitfields_intersect_add(bitfields_by_file:list):
	# find if there are any duplicate bitfields (in name and in fields) and
	# condense them
	assert(0 < len(bitfields_by_file))

	ver = ""
	address = 0

	final_fields = {} # name:[bf,bf]
	for name in bitfields_by_file[0]: # blindly eat the first set
		final_fields[name] = [bitfields_by_file[0][name]]
	bitfields_by_file = bitfields_by_file[1:]

	for bf_set in bitfields_by_file: # then compare
		for name in bf_set: 
			bf = bf_set[name]
			if name in final_fields:
				for final_bf in final_fields[name]:
					if bf.entries == final_bf.entries:
						final_bf.ver_addr.update(bf.ver_addr) # by version
						ver = tuple(bf.ver_addr.keys())[0]
						address = bf.ver_addr[ver][1]
						if address in final_bf.addr_ver: # by address
							assert(bf.ver_addr[ver][0] # name
								== final_bf.addr_ver[address][0]
							)
							final_bf.addr_ver[address].append(ver)
						else:
							final_bf.addr_ver[address] = bf.addr_ver[address]
						break
				else:
					final_fields[name].append(bf)
			else:
				final_fields[name] = [bf]
	return final_fields


def composite_bitfields_sort(composite_bitfields:dict):
	# sort the version-address association dict within each bitfield
	# sort the address-version association dict within each bitfield
	# sort the order of the bitfields of a shared name based on the version
	# sort the bitfields overall by name.
	sort_bf = lambda bf: tuple(bf.ver_addr.keys())[-1]
	sort_addr = lambda dict_items: dict_items[-1]
	ver_set = []
	for name in composite_bitfields:
		for bf in composite_bitfields[name]:
			bf.ver_addr = dict(sorted(bf.ver_addr.items()))
			for addr in bf.addr_ver:
				ver_set = bf.addr_ver[addr][1:]
				ver_set.sort()
				bf.addr_ver[addr] = bf.addr_ver[addr][0:1] + ver_set
			bf.addr_ver = dict(sorted(bf.addr_ver.items(), key=sort_addr))
		composite_bitfields[name].sort(key=sort_bf)
	return dict(sorted(composite_bitfields.items()))


def bitfield_to_header(composite_bitfields:dict):
	def_index_str = "#define %s_%s %s%s\n"
	comment_start = " //"
	bf_string_start = """\
union %s_%s {%s
	uint32_t %s;
	struct { uint32_t
"""
	bf_string_mid = "\t\t%s%s:%u-%u +1,"
	bf_string_end = """\
	};
};

"""
	def_addr_vals = (); bf_startvals = (); bf_midvals = () # for the %s
	ver_str = "" # for comment_start
	header_out = "" # the final buffer

	composite_bitfields = composite_bitfields_sort(composite_bitfields)
	addr_ver = {}
	addr_name = "" # for mm/ix and recapsing
	addr_str = ""

	for name in composite_bitfields:
		for bf in composite_bitfields[name]:
			addr_ver = bf.addr_ver
			for addr in addr_ver: #  #define mmNAME_ver 0xABCD // ver, ver
				addr_name = addr_ver[addr][0]
				assert(addr_name[2:] == name)
				if addr_name[:2] in ("ix", "mm"): # caps name
					addr_name = addr_name[:2] + addr_name[2:].upper()
				else:
					addr_name.upper()

				ver_str = comment_start # secondary versions
				for ver in addr_ver[addr][1:]:
					ver_str += " %s," % ver
				ver_str = ver_str[:-1] # lop off last comma
				ver = addr_ver[addr][1] # primary version

				addr_str = "0x%X" % addr
				def_addr_vals = (addr_name, ver, addr_str, ver_str)
				header_out += def_index_str % def_addr_vals

			# union name {
			ver_str = comment_start
			for ver in bf.ver_addr:
				ver_str += " %s," % ver
			ver_str = ver_str[:-1] # lop off last comma
			bf_startvals = (name, tuple(bf.ver_addr)[0], ver_str, name)
			header_out += bf_string_start % bf_startvals

			longest_named = bf.find_longest_named()
			len_longest = len(longest_named["name"])
			long_hi_double = (10 <= longest_named["hi"])
			for entry in bf.entries: #  name :hi-lo +1,
				len_entry = len(entry["name"])
				num_spaces = (
					len_longest - len_entry + 1 # push out, replace, extra
					+      (long_hi_double and (10 > entry["hi"]))
					- (not (long_hi_double or  (10 > entry["hi"])))
				)
				bf_midvals = (
					entry["name"],
					" " * num_spaces,
					entry["hi"],
					entry["lo"],
				)
				header_out += (bf_string_mid % bf_midvals) + "\n"
			header_out = header_out[:-2] + ";\n" # comma to colon

			header_out += bf_string_end # }; };

		header_out += "\n"

	return header_out


def get_val_from_bf(val:int, field:dict):
	return (val >> field["lo"]) & ( (1<<(field["hi"]-field["lo"])) -1)

def bf_regression(bitfields:dict, registers:list):
	# the intent is to brute-force possible register definitions for a set of
	# straps to the same field.
	# Go through all bitfields and find the ones that have the 'rsvd' valued
	# at 0
	candidates = []
	isbad = 0
	for k in bitfields:
		bf = bitfields[k]
		isbad = 0
		for r in registers:
			for f in bf.entries:
				if ((f["name"][:4] == "rsvd") and (get_val_from_bf(r, f))):
					isbad = 1
					break
			if (isbad):
				break
		if not (isbad):
			candidates.append(bf)
	return candidates


def get_ver(file_name:str):
	fname_parts = file_name.split("_")
	return fname_parts[1] + "_" + fname_parts[2]


def main(argc:int, argv:list):
	assert(2 <= argc)
	arg_i = 1 # 1 to pop off the self name

	mode = int(argv[arg_i])
	arg_i += 1

	assert(0 <= mode)

	fname_parts = []
	bitfields = {}
	version = ""
	reg_name_id_pairs = {}
	bitfields_byfile = []

	if mode == 0: # shmask.h d.h  shmask.h d.h
		assert(5 <= argc)
		output_file = argv[arg_i]
		arg_i += 1

		num_shmask_d_pairs = (argc - arg_i)/2
		assert (num_shmask_d_pairs == int(num_shmask_d_pairs))
		while (arg_i < argc):
			version = get_ver(argv[arg_i])
			with open(argv[arg_i], 'r', encoding="utf-8") as f:
				bitfields = shmask_filetext_to_bitfields(f.read())
			arg_i += 1
			assert(version == get_ver(argv[arg_i]))
			with open(argv[arg_i], 'r', encoding="utf-8") as f:
				reg_name_id_pairs = text_to_dict(f.read())
			arg_i += 1
			bitfields_attach_reg_ids(version, bitfields, reg_name_id_pairs)
			bitfields_byfile.append(bitfields.copy())

		arg_i += num_shmask_d_pairs*2
		composite_bitfield_sets = bitfields_intersect_add(bitfields_byfile)
		with open(output_file, 'w', encoding="utf-8") as f:
			f.write(bitfield_to_header(composite_bitfield_sets))
	elif mode == 1:
		assert(4 <= argc)
		with open(argv[arg_i],'r', encoding="utf-8") as f:
			bitfields = shmask_filetext_to_bitfields(f.read())
		straps_to_be_tested = argv[arg_i:]
		candidates = bf_regression(bitfields, straps_to_be_tested)
		for c in candidates:
			print(c.name)
	else:
		assert(0) # unsupported mode

if (__name__ == "__main__"):
	main(len(argv), argv)
