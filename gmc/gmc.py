# gmc.py gmc_6_0_sh_mask.h output.h

# python script to convert AMD asic registers into C bitfields.
# The design target is a stripped edition of the asic_reg/gmc/*_sh_mask.h
# header files.
#
# For example the input file would look like,

#define ATC_ATS_CNTL__CREDITS_ATS_RPB_MASK 0x00003f00L                          
#define ATC_ATS_CNTL__CREDITS_ATS_RPB__SHIFT 0x00000008
#define ATC_ATS_CNTL__DEBUG_ECO_MASK 0x000f0000L
#define ATC_ATS_CNTL__DEBUG_ECO__SHIFT 0x00000010
#define ATC_ATS_CNTL__DISABLE_ATC_MASK 0x00000001L
#define ATC_ATS_CNTL__DISABLE_ATC__SHIFT 0x00000000
#define ATC_ATS_CNTL__DISABLE_PASID_MASK 0x00000004L
#define ATC_ATS_CNTL__DISABLE_PASID__SHIFT 0x00000002
#define ATC_ATS_CNTL__DISABLE_PRI_MASK 0x00000002L
#define ATC_ATS_CNTL__DISABLE_PRI__SHIFT 0x00000001



from gmpy2 import popcount
from sys import argv

class bitfield:
	name: str
	entries: list
	longest_name: int

	def add_maskshift(self, name: str, mask: int, shift: int):
		# inclusvie [] bitfield notation. [3:0] is 4 bits
		num_bits = popcount(mask)
		if (num_bits == 0):
			return
		if (len(name) > self.longest_name):
			self.longest_name = len(name)
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

	def __init__(self, name: str):
		self.name = name
		self.longest_name = len("rsvd00")
		self.entries = []


def text_to_dict(file_text: str):
	entry_array = file_text.split("\n")[:-1] # pop blank '\n'
	pp_dict = {}
	parts = []
	for entry in entry_array:
		parts = entry.split()
		assert (parts[0] == "#define"), parts
		assert (len(parts) == 3), parts
		pp_dict[parts[1]] = parts[2]
	return pp_dict

def asic_reg_to_bitfield(file_text: str):
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
		if (k[-4:] != "MASK"): # enter with a mask then find shift
			continue
		mask_key = k
		shift_key = k[:-4] + "_SHIFT"
		name_parts = shift_key.split("__")

		if (name_parts[0] != current_bf_name):
			assert(name_parts[0] not in old_bf_names)
			old_bf_names.append(current_bf_name)
			current_bf_name = name_parts[0]
			bitfields.append(bitfield(name_parts[0].lower()))
			bf_i += 1

		if (pp_dict[mask_key][-1] == "L"): # python int() doesn't like C ints
			mask = int(pp_dict[mask_key][:-1], 16)
		else:
			mask = int(pp_dict[mask_key], 16)
		if (pp_dict[shift_key][-1] == "L"):
			shift = int(pp_dict[shift_key][:-1], 16)
		else:
			shift = int(pp_dict[shift_key], 16)

		bitfields[bf_i].add_maskshift(name_parts[1].lower(), mask, shift)

	bitfields = bitfields
	for b in bitfields:
		b.sort() # sort because we added in a disordered way
		b.find_reserved()
	return bitfields


def bitfield_to_header(bitfields: list):
	bf_string_start = """
union %s {
	uint32_t %s;
	struct { uint32_t
"""
	bf_string_mid = "\t\t%s %s:%u-%u +1,"
	bf_string_end = """\
	};
};
"""
	start_vals = (); mid_vals = ()

	header_out = ""
	for bf in bitfields:
		start_vals = (bf.name, bf.name)
		header_out += (bf_string_start % start_vals)
		for entry in bf.entries:
			mid_vals = (
				entry["name"],
				" " * (bf.longest_name - len(entry["name"])),
				entry["hi"],
				entry["lo"],
			)
			header_out += (bf_string_mid % mid_vals) + "\n"
		header_out = header_out[:-2] + ";\n" # comma to colon
		header_out += bf_string_end
	return header_out


def get_val_from_bf(val: int, field: dict):
	return (val >> field["lo"]) & ( (1<<(field["hi"]-field["lo"])) -1)

def bf_regression(bitfields: list, registers: list):
	# the intent is to brute-force possible register definitions for a set of
	# straps to the same field.
	# Go through all bitfields and find the ones that have the 'rsvd' valued
	# at 0
	candidates = []
	isbad = 0
	for bf in bitfields:
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

def main():
	argc = len(argv)
	assert (1 < argc)
	bitfields = []
	with open(argv[1],'r', encoding="utf-8") as f:
		bitfields = asic_reg_to_bitfield(f.read())

	if (2 < argc):
		with open(argv[2], 'w', encoding="utf-8") as f:
			f.write(bitfield_to_header(bitfields))

	straps_to_be_tested = [] # CHANGE ME if you want!!
	if len(straps_to_be_tested):
		candidates = bf_regression(bitfields, straps_to_be_tested)
		for c in candidates:
			print(c.name)

if (__name__ == "__main__"):
	main()