# asic_reg.py is a script to process asic_reg's sh_mask.h and offset.h to output
# something that is a little more readable.

#asic_reg.py mode files
# mode = 0
# Convert an inputted asic_reg shift-mask files into C bitfields, with relevant
# register number definition adjacent. 
# If multiple shmask-d pairs are given, find commonality and associate versions.
# gmc.py 0 gmc_out.h gmc_8_1_sh_mask.h gmc_8_1_d.h
# gmc.py 0 gmc_out.h gmc_8_1_sh_mask.h gmc_8_1_d.h gmc_7_0_sh_mask.h gmc_7_0_d.h

# mode = 1
# intersect bitfields with a collection of register values, to find what
# bitfields the values are about. Specifically, find all bitfields that keep
# the 'rsvd' fields zero in value.
# asic_reg.py 1 gmc_8_1_sh_mask.h # # # #

from gmpy2 import popcount
from sys import argv

class bitfield:
	name:str
	entries:list # bitfield entries [{name hi lo}]
	num_bits:int
	ver_addr:dict # version:[name, address] sets; by-version association
	addr_ver:dict # address:[name, ver, ver..] sets; by-address association
	base_ver:dict # base_index:[ver, ver, ver..] sets

	longest_named:dict

	def add_maskshift(self, name:str, mask:int, shift:int):
		# inclusvie [] bitfield notation. [3:0] is 4 bits
		num_bits = popcount(mask)
		if (num_bits == 0):
			assert 0, "%s %s %u %u" % (self.name, name, mask, shift)
			return
		self.entries.append({
			"name": name,
			"hi": (shift + num_bits - 1),
			"lo": shift,
		})

	def sort(self):
		self.entries.sort(key=lambda e: e["lo"])

	def find_num_bits(self):
		highest_hi = self.entries[-1]["hi"]
		if highest_hi < 32:
			self.num_bits = 32
		elif highest_hi < 64:
			self.num_bits = 64
		else:
			assert 0, "%s %s %u" %\
				(self.name, self.entries[-1]["name"], highest_hi)

	def find_reserved(self):
		# find if there's any undefined gaps in the bitfield

		self.sort()
		self.find_num_bits()

		reserved_n = 0
		hi_end = 0; new_lo = 0
		lo = 0
		entries_i = 0
		entries_end = len(self.entries)
	
		while (entries_i <= entries_end):
			if (entries_i == entries_end):
				hi_end = self.num_bits
				new_lo = self.num_bits
			else:
				hi_end = self.entries[entries_i]["lo"]
				new_lo = self.entries[entries_i]["hi"] + 1

			if (hi_end - lo):
				self.entries.insert(entries_i, {
					"name": ("_rsvd%02u" % reserved_n),
					"hi": hi_end - 1,
					"lo": lo,
				})
				reserved_n += 1
				entries_i += 2
				entries_end += 1
			else:
				entries_i += 1
			lo = new_lo


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
		self.entries = []
		self.num_bits = 0
		self.ver_addr = {}
		self.addr_ver = {}
		self.base_ver = {}
		self.longest = None


def text_to_dict(version:str, file_text:str):
	# very primitive preprocessor parser
	dupicate_warning = "WARNING: %s %s: replacing val %s with %s"
	warning_parts = ()
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
				if ((parts[1] in pp_dict.keys())
						and (pp_dict[parts[1]] != parts[2])
						):
					warning_parts = (
						version, parts[1], pp_dict[parts[1]], parts[2]
					)
					print(dupicate_warning % warning_parts)
				pp_dict[parts[1]] = parts[2]
		else:
			i+=1
	return pp_dict


def c_literal_to_int(literal:str):
	# python int() doesn't like C int suffixes
	len_str = len(literal)
	base = 10
	i = 0
	if (2 <= len_str):
		if "0x" == literal[:2]:
			base = 16
			i += 2
		elif "0b" == literal[:2]:
			base = 2
			i += 2

	while (i < len_str):
		if literal[i] in ("u","l"):
			break
		i += 1
	return int(literal[0:i], base)

def shmask_filetext_to_bitfields(version:str, file_text:str):
	# the mask-shift pairs in the sh_mask.h files may not be physically
	# adjacent within the header file, so do a primitive preprocessor parse for
	# a basic namespace (the python dict). 
	pp_dict = text_to_dict(version, file_text)
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
			assert(name_parts[0] not in old_bf_names), name_parts
			old_bf_names.append(current_bf_name)
			current_bf_name = name_parts[0]
			bitfields.append(bitfield(name_parts[0]))
			bf_i += 1

		mask = c_literal_to_int(pp_dict[mask_key])
		shift = c_literal_to_int(pp_dict[shift_key])

		bitfields[bf_i].add_maskshift(name_parts[1], mask, shift)

	bitfields_dict = {}
	for b in bitfields:
		b.find_reserved()
		bitfields_dict[b.name] = b

	return bitfields_dict

def bitfields_attach_reg_ids(version:str, bitfields:dict, reg_name_id_pairs:dict):
	base_idx_name = ""
	base_index = 0
	bf_name = ""
	address = 0
	for reg_name in reg_name_id_pairs:
		if reg_name[:2] in ("ix", "mm"):
			bf_name = reg_name[2:]
		elif reg_name[:3] == "reg":
			bf_name = reg_name[3:]
		else:
			bf_name = reg_name

		base_idx_name = bf_name[:-9]
		if ((reg_name[-9:] == '_base_idx') and (base_idx_name in bitfields)):
			bf = bitfields[base_idx_name]
			assert(version not in bf.base_ver), "%s %s" % (bf_name, version)
			base_index = int(reg_name_id_pairs[reg_name])
			bf.base_ver[base_index] = [version]
		elif bf_name in bitfields:
			bf = bitfields[bf_name]
			assert(version not in bf.ver_addr), "%s %s" % (bf_name, version)
			address = c_literal_to_int(reg_name_id_pairs[reg_name])
			bf.ver_addr[version] = (reg_name, address)
			bf.addr_ver[address] = [reg_name, version]
		else:
			print("WARNING: %s: %s has no shmask!" % (version, bf_name.upper()))

	ver_addr = {}
	for bf_name in bitfields:
		ver_addr = bitfields[bf_name].ver_addr
		if version not in ver_addr:
			print("WARNING: %s: %s has no offset!" % (version, bf_name.upper()))
			ver_addr[version] = []
		if not bitfields[bf_name].base_ver:
			pass
			#print("WARNING: %s: %s has no base offset!" %\
			#	(version, bf_name.upper()))


def bitfields_intersect_add(bitfields_by_file:list):
	# find if there are any duplicate bitfields (in name and in fields) and
	# condense them
	assert(0 < len(bitfields_by_file))

	ver = ""
	addr = 0
	base = 0

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
						ver = tuple(bf.ver_addr)[0]
						if bf.ver_addr[ver]: # some versions don't have addrs
							addr = bf.ver_addr[ver][1]
							if addr in final_bf.addr_ver: # by address
								final_bf.addr_ver[addr].append(ver)
							else:
								final_bf.addr_ver[addr] = bf.addr_ver[addr]
						if bf.base_ver:
							base = tuple(bf.base_ver)[0]
							if base in final_bf.base_ver:
								final_bf.base_ver[base].append(ver)
							else:
								final_bf.base_ver[base] = [ver]
						break
				else:
					final_fields[name].append(bf)
			else:
				final_fields[name] = [bf]
	return final_fields

def composite_bitfields_sort(composite_bitfields:dict):
	# sort the version-address association dict within each bitfield
	# sort the versions of the address-version association dict
	# sort the address-version association dict
	# sort the order of the bitfields of a shared name based on the version
	# sort the bitfields overall by name.

	# "11_0_3" -> [11,0,3]
	key_veraddr = lambda d_items: [int(n) for n in d_items[0].split("_")]
	key_addrver_vers = lambda v: [int(n) for n in v.split("_")]
	key_addrver = lambda d_items: [int(n) for n in d_items[1][-1].split("_")]
	key_basever_vers = key_addrver_vers
	key_basever = key_addrver
	key_bf = lambda bf: [int(n) for n in tuple(bf.ver_addr)[-1].split("_")]

	ver_set = []
	for name in composite_bitfields:
		for bf in composite_bitfields[name]:
			bf.ver_addr = dict(sorted(bf.ver_addr.items(), key=key_veraddr))
			if bf.addr_ver:
				for addr in bf.addr_ver:
					ver_set = bf.addr_ver[addr][1:]
					ver_set.sort(key=key_addrver_vers)
					bf.addr_ver[addr] = bf.addr_ver[addr][0:1] + ver_set
				bf.addr_ver = dict(sorted(bf.addr_ver.items(), key=key_addrver))
			if bf.base_ver:
				for base in bf.base_ver:
					bf.base_ver[base].sort(key=key_basever_vers)
				bf.base_ver = dict(sorted(bf.base_ver.items(), key=key_basever))
		composite_bitfields[name].sort(key=key_bf)
	return dict(sorted(composite_bitfields.items()))


def get_newest_index_name(addr:int, ver_addr:dict, addr_ver: dict):
	# typically, mm -> reg
	latest_ver = addr_ver[addr][-1]
	return ver_addr[latest_ver][0]

def bitfield_to_header(name:str, versions:list, composite_bitfields:dict):
	header_header = """\
/*
autogenerated with asic_reg.py
Considers %s versions: %s
*/

#ifndef %s_H
#define %s_H

#pragma pack(push, 1) // bios data must use byte alignment

"""
	header_ender = """\
#pragma pack(pop) // restore old packing

#endif
"""

	def_index_str = "#define %s_%s %s%s\n"
	comment_start = " //"
	bf_string_start = """\
union %s_%s {%s
	%s raw_data;
	struct { %s
"""
	bf_string_bitness = ("uint32_t", "uint64_t")
	bf_string_mid = "\t\t%s%s:%u-%u +1,"
	bf_string_end = """\
	};
};

"""
	header_out = "" # the final buffer
	c_type = "" # uint32_t, etc
	define_vals = (); bf_startvals = (); bf_midvals = () # for the %s
	ver_str = "" # for comment_start

	composite_bitfields = composite_bitfields_sort(composite_bitfields)
	ver_addr = {}
	addr_ver = {}
	base_ver = {}
	addr_name = "" # for mm/ix/reg and recapsing
	addr_str = ""

	versions.sort(key=lambda v: [int(n) for n in v.split("_")])
	ver_str = ", ".join(versions)
	header_out = header_header % (name, ver_str, name, name)

	for name in composite_bitfields:
		for bf in composite_bitfields[name]:
			ver_addr = bf.ver_addr
			addr_ver = bf.addr_ver
			base_ver = bf.base_ver

			for addr in addr_ver: #  #define mmNAME_ver 0xABCD // ver, ver
				addr_name = get_newest_index_name(addr, ver_addr, addr_ver)
				if addr_name[:2] in ("ix", "mm"): # caps name
					assert(addr_name[2:] == name), name
					addr_name = addr_name[:2] + addr_name[2:].upper()
				elif addr_name[:3] == "reg": # caps name
					assert(addr_name[3:] == name), name
					addr_name = addr_name[:3] + addr_name[3:].upper()
				else:
					assert(addr_name == name), name
					addr_name.upper()

				ver_str = comment_start # secondary versions
				for ver in addr_ver[addr][1:]:
					ver_str += " %s," % ver
				ver_str = ver_str[:-1] # lop off last comma
				ver = addr_ver[addr][1] # primary version

				addr_str = "0x%X" % addr
				define_vals = (addr_name, ver, addr_str, ver_str)
				header_out += def_index_str % define_vals

			for base in base_ver: # #define mmNAME_BASE_IDX_ver 0 // ver, ver
				addr_name = ver_addr[ base_ver[base][-1] ][0] # get latest name
				if addr_name[:2] in ("ix", "mm"): # caps name
					assert(addr_name[2:] == name), name
					addr_name = addr_name[:2] + addr_name[2:].upper()
				elif addr_name[:3] == "reg": # caps name
					assert(addr_name[3:] == name), name
					addr_name = addr_name[:3] + addr_name[3:].upper()
				else:
					assert(addr_name == name), name
					addr_name.upper()
				addr_name += "_BASE_IDX"

				ver_str = comment_start # secondary versions
				for ver in base_ver[base]:
					ver_str += " %s," % ver
				ver_str = ver_str[:-1] # lop off last comma
				ver = base_ver[base][0] # primary version

				define_vals = (addr_name, ver, base, ver_str)
				header_out += def_index_str % define_vals

				

			# union name {
			ver_str = comment_start
			for ver in ver_addr:
				ver_str += " %s," % ver
			ver_str = ver_str[:-1] # lop off last comma
			if (bf.num_bits == 32):
				c_type = bf_string_bitness[0]
			else:
				assert(bf.num_bits == 64)
				c_type = bf_string_bitness[1]
			bf_startvals = (
				name, tuple(ver_addr)[0], ver_str, c_type, c_type
			)
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
	header_out += header_ender
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
	verstr = fname_parts[1] + "_" + fname_parts[2] # major, minor
	if fname_parts[3].isdigit(): # patch
		verstr += "_" + fname_parts[3]
	return verstr


def main(argc:int, argv:list):
	assert(2 <= argc)
	arg_i = 1 # 1 to pop off the self name

	mode = int(argv[arg_i])
	arg_i += 1

	assert(0 <= mode)

	version = ""
	versions = []
	ip_name = ""
	bitfields = {}
	reg_name_id_pairs = {}
	bitfields_byfile = []

	if mode == 0: # shmask.h d.h  shmask.h d.h
		assert(5 <= argc)
		output_file = argv[arg_i]
		arg_i += 1

		num_input_files = argc - arg_i
		assert (num_input_files % 2 == 0) # shmask, offset pairs

		ip_name = argv[arg_i].split("_")[0].split("/")[-1].upper()

		while (arg_i < argc):
			version = get_ver(argv[arg_i])
			versions.append(version)
			with open(argv[arg_i], 'r', encoding="utf-8") as f:
				bitfields = shmask_filetext_to_bitfields(version, f.read())
			arg_i += 1
			assert(version == get_ver(argv[arg_i]))
			with open(argv[arg_i], 'r', encoding="utf-8") as f:
				reg_name_id_pairs = text_to_dict(version, f.read())
			arg_i += 1
			bitfields_attach_reg_ids(version, bitfields, reg_name_id_pairs)
			bitfields_byfile.append(bitfields.copy())

		arg_i += num_input_files
		composite_bitfield_sets = bitfields_intersect_add(bitfields_byfile)
		with open(output_file, 'w', encoding="utf-8") as f:
			f.write(bitfield_to_header(
				ip_name, versions, composite_bitfield_sets
			))
	elif mode == 1:
		assert(4 <= argc)
		with open(argv[arg_i],'r', encoding="utf-8") as f:
			bitfields = shmask_filetext_to_bitfields(version, f.read())
		straps_to_be_tested = argv[arg_i:]
		candidates = bf_regression(bitfields, straps_to_be_tested)
		for c in candidates:
			print(c.name)
	else:
		assert(0) # unsupported mode

if (__name__ == "__main__"):
	main(len(argv), argv)
