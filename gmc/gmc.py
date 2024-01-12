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
	mask = 0; shift = 0

	for k in pp_dict.keys():
		if (k[-4:] != "MASK"): # enter with a mask then find shift
			continue
		mask_key = k
		shift_key = k[:-4] + "_SHIFT"
		name_parts = shift_key.split("__")
		# name_parts[0] is bitfield name
		assert (name_parts[0] == mask_key.split("__")[0]), name_parts

		if (name_parts[0] != current_bf_name):
			bitfields.append(bitfield(name_parts[0].lower()))
			current_bf_name = name_parts[0]
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

def main():
	argc = len(argv)
	assert (1 < argc)
	bitfields = []
	with open(argv[1],'r', encoding="utf-8") as f:
		bitfields = asic_reg_to_bitfield(f.read())

	if (2 < argc):
		with open(argv[2], 'w', encoding="utf-8") as f:
			f.write(bitfield_to_header(bitfields))

if (__name__ == "__main__"):
	main()
