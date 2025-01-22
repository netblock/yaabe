#!/usr/bin/env python
# -*- coding: utf-8 -*-

# a script to process AMD's include/asic_reg/'s sh_mask.h and offset.h
# to output something that is a little more readable.

#basic usage: asic_reg.py mode files
#
# mode = 0
# Convert an inputted asic_reg shift-mask files into C bitfields, with relevant
# register number definition adjacent. If multiple shmask-d pairs are given,
# this also finds commonality and associate versions.
# asic_reg.py 0 gmc_out.h gmc_8_1_sh_mask.h gmc_8_1_d.h
# asic_reg.py 0 gmc_out.h gmc_8_1_sh_mask.h gmc_8_1_d.h gmc_7_0_sh_mask.h gmc_7_0_d.h
# an example of gmc_out.h would be atom/gmc.h and atom/gc.h
#
# mode = 1
# Works just like mode 0. Print out bitfields in the style of PPATUI JSON5.
# an example would be atomtree/atui/tables/atui_gmc.json5
# see also scripts/ppatui.py
#
# mode = 2
# Searchfield. Print out register names by the order of their address.
# see atomtree/asic_reg_tools.h
#
# mode = 3
# For manual bitfield hacking. Intersect bitfields with a collection of
# register values, to find what bitfields the values are about.
# Specifically, find all bitfields that keep the 'rsvd' fields zero in value.
# asic_reg.py 3 gmc_8_1_sh_mask.h # # # #

# takes a lot of files;  cleaned from command ls -lr
# gmc/{gmc_8_2_sh_mask.h,gmc_8_2_d.h,gmc_8_1_sh_mask.h,gmc_8_1_d.h,gmc_7_1_sh_mask.h,gmc_7_1_d.h,gmc_7_0_sh_mask.h,gmc_7_0_d.h,gmc_6_0_sh_mask.h,gmc_6_0_d.h}

# gc/{gc_9_4_3_sh_mask.h,gc_9_4_3_offset.h,gc_9_4_2_sh_mask.h,gc_9_4_2_offset.h,gc_9_4_1_sh_mask.h,gc_9_4_1_offset.h,gc_9_2_1_sh_mask.h,gc_9_2_1_offset.h,gc_9_1_sh_mask.h,gc_9_1_offset.h,gc_9_0_sh_mask.h,gc_9_0_offset.h,gc_11_5_0_sh_mask.h,gc_11_5_0_offset.h,gc_11_0_3_sh_mask.h,gc_11_0_3_offset.h,gc_11_0_0_sh_mask.h,gc_11_0_0_offset.h,gc_10_3_0_sh_mask.h,gc_10_3_0_offset.h,gc_10_1_0_sh_mask.h,gc_10_1_0_offset.h}


import re
from gmpy2 import popcount
from sys import argv
from typing import Callable

class bitfield_entry:
	name:str
	hi:int
	lo:int
	def __init__(self,
			name:str,
			hi:int,
			lo:int
			):
		self.name = name
		self.hi = hi
		self.lo = lo
	def __eq__(self, other):
		return (
			(self.name == other.name)
			and (self.hi == other.hi)
			and (self.lo == other.lo)
		)

class bitfield:
	name:str
	entries:list # bitfield entries [bitfield_entry..]
	num_bits:int
	ver_addr:dict # version:[name, address] sets; by-version association
	addr_ver:dict # address:[name, ver, ver..] sets; by-address association
	base_ver:dict # base_index:[ver, ver, ver..] sets

	longest_named:dict

	def add_maskshift(self,
			name:str,
			mask:int,
			shift:int
			):
		# inclusvie [] bitfield notation. [3:0] is 4 bits
		num_bits:int = popcount(mask)
		if (num_bits == 0):
			assert 0, (self.name, name, mask, shift)
			return
		self.entries.append(bitfield_entry(
			name,  (shift + num_bits - 1),  shift
		))


	def sort(self
			):
		self.entries.sort(key=lambda e: e.lo)

	def find_num_bits(self
			):
		highest_hi:int = self.entries[-1].hi
		if highest_hi < 32:
			self.num_bits = 32
		elif highest_hi < 64:
			self.num_bits = 64
		else:
			assert 0, "%s %s %u" %\
				(self.name, self.entries[-1].name, highest_hi)

	def find_reserved(self
			):
		# find if there's any undefined gaps in the bitfield

		self.sort()
		self.find_num_bits()

		reserved_n:int = 0
		hi_end:int = 0
		new_lo:int = 0
		lo:int = 0
		entries_i:int = 0
		entries_end:int = len(self.entries)

		while (entries_i <= entries_end):
			if (entries_i == entries_end):
				hi_end = self.num_bits
				new_lo = self.num_bits
			else:
				hi_end = self.entries[entries_i].lo
				new_lo = self.entries[entries_i].hi + 1

			if (hi_end - lo):
				self.entries.insert(entries_i, bitfield_entry(
					("_rsvd%02u" % reserved_n),
					hi_end-1,  lo
				))
				reserved_n += 1
				entries_i += 2
				entries_end += 1
			else:
				entries_i += 1
			lo = new_lo


	def find_longest_named(self
			):
		longest:bitfield_entry = self.entries[0]
		len_long:int = len(longest.name)
		len_e:int = 0
		e:bitfield_entry
		for e in self.entries[1:]:
			len_e:int = len(e.name)
			if len_e >= len_long: # find little-endian leftmost longest
				longest = e
				len_long = len_e
		self.longest_named = longest
		return longest

	def __init__(self,
			name:str
			):
		self.name = name
		self.entries = []
		self.num_bits = 0
		self.ver_addr = {}
		self.addr_ver = {}
		self.base_ver = {}
		self.longest = None


def text_to_dict(
		version:str,
		file_text:str
		) -> dict:
	# very primitive preprocessor parser
	dupicate_warning:str = "WARNING: %s %s: replacing val %s with %s"
	pp_dict:dict = {}
	end:int = len(file_text)
	i:int = 0
	while (i < end):
		if file_text[i:i+len("/*")] == "/*": # skip /* */ comments
			i+=2
			while ((i < end) and (file_text[i:i+len("*/")] != "*/")):
				i+=1
		elif file_text[i:i+len("#define")] == "#define":
			line:str = file_text[i:].split("\n",1)[0]
			i += len(line) + 1
			line = line.lower() # santise out mixed-case
			parts:list = line.split()
			if len(parts) == 3:
				if ((parts[1] in pp_dict.keys())
						and (pp_dict[parts[1]] != parts[2])
						):
					warning_parts:tuple = (
						version, parts[1], pp_dict[parts[1]], parts[2]
					)
					print(dupicate_warning % warning_parts)
				pp_dict[parts[1]] = parts[2]
		else:
			i+=1
	return pp_dict


def c_literal_to_int(
		literal:str
		) -> int:
	# python int() doesn't like C int suffixes
	len_str:int = len(literal)
	base:int = 10
	i:int = 0
	if (2 <= len_str):
		if "0x" == literal[:2]:
			base = 16
			i += 2
		elif "0b" == literal[:2]:
			base = 2
			i += 2

	while (i < len_str):
		if literal[i] in {"u","l"}:
			break
		i += 1
	return int(literal[0:i], base)

def shmask_filetext_to_bitfields(
		version:str,
		file_text:str
		) -> dict:
	# the mask-shift pairs in the sh_mask.h files may not be physically
	# adjacent within the header file, so do a primitive preprocessor parse for
	# a basic namespace (the python dict).
	pp_dict:dict = text_to_dict(version, file_text)
	assert(0 == (len(pp_dict) % 2))

	bitfields:list = []
	bf_i:int = -1
	current_bf_name:str = ""
	old_bf_names:list = []

	mask:int = 0
	shift:int = 0

	keys:list = list(pp_dict.keys())
	keys.sort()
	k:str
	for k in keys:
		if (k[-4:] != "mask"): # enter with a mask then find shift
			continue
		mask_key:str = k
		shift_key:str = k[:-4] + "_shift"
		name_parts:str = shift_key.split("__")

		if (name_parts[0] != current_bf_name):
			assert(name_parts[0] not in old_bf_names), name_parts
			old_bf_names.append(current_bf_name)
			current_bf_name = name_parts[0]
			bitfields.append(bitfield(name_parts[0]))
			bf_i += 1

		mask = c_literal_to_int(pp_dict[mask_key])
		shift = c_literal_to_int(pp_dict[shift_key])

		bitfields[bf_i].add_maskshift(name_parts[1], mask, shift)

	bitfields_dict:dict = {}
	for b in bitfields:
		b.find_reserved()
		bitfields_dict[b.name] = b

	return bitfields_dict

def bitfields_attach_reg_ids(
		version:str,
		bitfields:dict,
		reg_name_id_pairs:dict
		):
	# associate shmask with offsets/index
	bf_name:str = ""
	reg_name:str
	for reg_name in reg_name_id_pairs:
		if reg_name[:2] in {"ix", "mm"}:
			bf_name = reg_name[2:]
		elif reg_name[:3] == "reg":
			bf_name = reg_name[3:]
		else:
			bf_name = reg_name

		base_idx_name:str = bf_name[:-9]
		if ((reg_name[-9:] == '_base_idx') and (base_idx_name in bitfields)):
			bf:bitfield = bitfields[base_idx_name]
			assert (version not in bf.base_ver), (bf_name, version)
			base_index = int(reg_name_id_pairs[reg_name])
			bf.base_ver[base_index] = [version]
		elif bf_name in bitfields:
			bf:bitfield = bitfields[bf_name]
			assert (version not in bf.ver_addr), (bf_name, version)
			address:int = c_literal_to_int(reg_name_id_pairs[reg_name])
			bf.ver_addr[version] = (reg_name, address)
			bf.addr_ver[address] = [reg_name, version]
		else:
			print("WARNING: %s: %s has no shmask!" % (version, bf_name.upper()))

	ver_addr:dict = {}
	for bf_name in bitfields:
		ver_addr:dict = bitfields[bf_name].ver_addr
		if version not in ver_addr:
			print("WARNING: %s: %s has no offset!" % (version, bf_name.upper()))
			ver_addr[version]:list = []
		if not bitfields[bf_name].base_ver:
			pass
			#print("WARNING: %s: %s has no base offset!" %\
			#	(version, bf_name.upper()))


def bitfields_intersect_add(
		bitfields_by_file:list
		) -> dict:
	# find if there are any duplicate bitfields (in name and in fields) and
	# condense them
	assert (0 < len(bitfields_by_file))

	final_fields:dict = {} # name:[bf,bf]
	name:str
	for name in bitfields_by_file[0]: # blindly eat the first set
		final_fields[name]:list = [bitfields_by_file[0][name]]
	bitfields_by_file = bitfields_by_file[1:]

	bf_set:dict
	for bf_set in bitfields_by_file: # then compare
		name:str
		for name in bf_set:
			bf:bitfield = bf_set[name]
			if name in final_fields:
				final_bf:bitfield
				for final_bf in final_fields[name]:
					if bf.entries == final_bf.entries:
						final_bf.ver_addr.update(bf.ver_addr) # by version
						ver:str = tuple(bf.ver_addr)[0]
						if bf.ver_addr[ver]: # some versions don't have addrs
							addr:int = bf.ver_addr[ver][1]
							if addr in final_bf.addr_ver: # by address
								final_bf.addr_ver[addr].append(ver)
							else:
								final_bf.addr_ver[addr] = bf.addr_ver[addr]
						if bf.base_ver:
							base:int = tuple(bf.base_ver)[0]
							if base in final_bf.base_ver:
								final_bf.base_ver[base].append(ver)
							else:
								final_bf.base_ver[base]:list = [ver]
						break
				else:
					final_fields[name].append(bf)
			else:
				final_fields[name]:list = [bf]
	return final_fields

def composite_bitfields_sort(
		composite_bitfields:dict
		) -> dict:
	# "name": [bf,bf,bf]
	# sort the version-address association dict within each bitfield
	# sort the versions of the address-version association dict
	# sort the address-version association dict
	# sort the order of the bitfields of a shared name based on the version
	# sort the bitfields overall by name.

	# "11_0_3" -> [11,0,3]
	key_veraddr:Callable = \
		lambda d_items: [int(n) for n in d_items[0].split("_")]
	key_addrver_vers:Callable = \
		lambda v: [int(n) for n in v.split("_")]
	key_addrver:Callable = \
		lambda d_items: [int(n) for n in d_items[1][-1].split("_")]
	key_basever_vers:Callable = key_addrver_vers
	key_basever:Callable = key_addrver
	key_bf:Callable = \
		lambda bf: [int(n) for n in tuple(bf.ver_addr)[-1].split("_")]

	name:str
	for name in composite_bitfields:
		bf:bitfield
		for bf in composite_bitfields[name]:
			bf.ver_addr = dict(sorted(bf.ver_addr.items(), key=key_veraddr))
			if bf.addr_ver:
				addr:str
				for addr in bf.addr_ver:
					ver_set:list = bf.addr_ver[addr][1:]
					ver_set.sort(key=key_addrver_vers)
					bf.addr_ver[addr]:list = bf.addr_ver[addr][0:1] + ver_set
				bf.addr_ver = dict(sorted(bf.addr_ver.items(), key=key_addrver))
			if bf.base_ver:
				base:int
				for base in bf.base_ver:
					bf.base_ver[base].sort(key=key_basever_vers)
				bf.base_ver:dict = dict(sorted(
					bf.base_ver.items(), key=key_basever
				))
		composite_bitfields[name].sort(key=key_bf)
	return dict(sorted(composite_bitfields.items()))


def get_newest_index_name(
		addr:int,
		bitfield:bitfield
		) -> str:
	# typically, mm -> reg
	latest_ver:str = bitfield.addr_ver[addr][-1]
	return bitfield.ver_addr[latest_ver][0]



# mode == 0
def bitfield_to_header(
		ip_name:str,
		versions:list,
		composite_bitfields:dict
		) -> str:
	header_header:str = """\
/*
autogenerated with asic_reg.py
Considers %s versions: %s
*/

#ifndef %s_H
#define %s_H
#pragma pack(push, 1) // bios data must use byte alignment

"""
	header_ender:str = """\
#pragma pack(pop) // restore old packing
#endif
"""

	def_index_str:str = "#define %s_%s %s%s\n"
	comment_start:str = " //"
	bf_string_start:str = """\
union %s_%s {%s
	%s raw_data;
	struct { %s
"""
	bf_string_mid:str = "\t\t%s%s:%u-%u +1,\n"
	bf_string_end:str = """\
	};
};

"""
	versions.sort(key=lambda v: [int(n) for n in v.split("_")])
	out_text:str = header_header % (
		ip_name,
		", ".join(versions),
		ip_name, ip_name
	)

	name:str
	for name in composite_bitfields:
		bf:bitfield
		for bf in composite_bitfields[name]:
			ver_addr:dict = bf.ver_addr
			addr_ver:dict = bf.addr_ver
			base_ver:dict = bf.base_ver

			addr:int
			for addr in addr_ver: #  #define mmNAME_ver 0xABCD // ver, ver
				# for mm/ix/reg and recapsing
				addr_name:str = get_newest_index_name(addr, bf)
				if addr_name[:2] in {"ix", "mm"}: # caps name
					assert(addr_name[2:] == name), name
					addr_name = addr_name[:2] + addr_name[2:].upper()
				elif addr_name[:3] == "reg": # caps name
					assert(addr_name[3:] == name), name
					addr_name = addr_name[:3] + addr_name[3:].upper()
				else:
					assert(addr_name == name), name
					addr_name.upper()

				ver_str:str = comment_start # secondary versions
				ver:str
				for ver in addr_ver[addr][1:]:
					ver_str +=  ver + ", "
				ver_str = ver_str[:-2] # lop off last ", "
				ver = addr_ver[addr][1] # primary version

				addr_str:str = "0x%X" % addr
				out_text += def_index_str % (
					addr_name, ver, addr_str, ver_str
				)
			base:int
			for base in base_ver: #  #define mmNAME_BASE_IDX_ver 0 // ver, ver
				addr_name:str = ver_addr[ base_ver[base][-1] ][0] # get latest
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

				ver_str:str = comment_start # secondary versions
				ver:str
				for ver in base_ver[base]:
					ver_str += ver + ", "
				ver_str = ver_str[:-2] # lop off last ", "
				ver:str = base_ver[base][0] # primary version

				out_text += def_index_str % (
					addr_name, ver, str(base), ver_str
				)

			# union name {
			ver_str:str = comment_start
			ver:str
			for ver in ver_addr:
				ver_str += ver + ", "
			ver_str = ver_str[:-2] # lop off last ", "
			c_type:str = ""
			match bf.num_bits:
				case 32:
					c_type = "uint32_t"
				case 64:
					c_type = "uint64_t"
				case _:
					assert 0
			out_text += bf_string_start % (
				name, tuple(ver_addr)[0], ver_str, c_type, c_type
			)

			longest_named:str = bf.find_longest_named()
			len_longest:int = len(longest_named.name)
			long_hi_double:bool = (10 <= longest_named.hi)
			entry:bitfield_entry
			for entry in bf.entries: #  name :hi-lo +1,
				len_entry:int = len(entry.name)
				num_spaces:int = (
					len_longest - len_entry + 1 # push out, replace, extra
					+      (long_hi_double and (10 > entry.hi))
					- (not (long_hi_double or  (10 > entry.hi)))
				)
				out_text += bf_string_mid % (
					entry.name,
					" " * num_spaces,
					entry.hi,
					entry.lo,
				)
			out_text = out_text[:-2] + ";\n" # comma to colon

			out_text += bf_string_end # }; };

		out_text += "\n"
	out_text += header_ender
	return out_text


# mode == 1
def bitfield_to_json5(
		ip_name:str,
		versions:list,
		composite_bitfields:dict
		) -> str:
	json5_header:str = """\
/*
autogenerated with asic_reg.py
Considers %s versions: %s
*/

{class: "branch",
global_default: {
	branch_defaults: {
		c_prefix: "union",
		atomtree: "atui_nullstruct",
		table_start: "bios",
		table_size: "sizeof(*bios)",
	},
	leaf_defaults: {
		generic: {
			access: "bios->raw_data",
			display: "ATUI_BIN",
			fancy: "ATUI_BITFIELD",
		},
		bitchild: {
			display: "ATUI_DEC",
			fancy: "ATUI_NOFANCY",
		},
		dynpattern: {
			display: "ATUI_DEC",
			fancy: "ATUI_NOFANCY",
		},
	},
}, branches: [

"""
	json5_ender:str = """\

], }
"""
	branch_template:str = """\
{
	c_type: "%s_%s",
	leaves: [{
		name: "%s",
		fancy_data: { fields: [
%s\
		],},
	},],
},
"""
	bf_entry_template:str = """\
			{access: "%s",},
"""

	out_text:str = "" # the final buffer
	bf_entries:str = ""

	versions.sort(key=lambda v: [int(n) for n in v.split("_")])
	ver_str:str = ", ".join(versions)
	out_text:str = json5_header % (ip_name, ver_str)

	name:str
	for name in composite_bitfields:
		bf:bitfield
		for bf in composite_bitfields[name]:
			bf_entries:str = ""
			entry:bitfield_entry
			for entry in bf.entries:
				bf_entries += bf_entry_template % entry.name
			out_text += branch_template % (
				name, tuple(bf.ver_addr)[0],
				name, bf_entries
			)
	#lazy approach: },\n{  to  }, {
	out_text = re.sub("(\t*)},\n(\t*){\n", "\\g<1>}, {\n", out_text) # lazy
	return out_text + json5_ender


# mode == 2
def bitfield_to_reglist(
		ip_name:str,
		versions:list,
		composite_bitfields:dict
		) -> str:
	# register search fields. see atomtree/asic_reg_tools.h
	# "name": [bf,bf,bf]
	json5_header:str = """\
/*
autogenerated with asic_reg.py
Considers %s versions: %s
*/

{class: "searchfield", fields: [

{name: "%s", registers: [
"""
	json5_entry:str = """\
	{
		index: \"%s\",
		field: \"%s\",
	},
"""
	json5_ender:str = "]},\n\n]}"

	versions.sort(key=lambda v: [int(n) for n in v.split("_")])
	ver_str:str = ", ".join(versions)
	out_text:str = json5_header % (ip_name, ver_str, ip_name)

	# get index names
	reg_list:dict = {} # addr:[name,name]
	bf_name:str
	for bf_name in composite_bitfields:
		bf:bitfield
		for bf in composite_bitfields[bf_name]:
			addr:int
			for addr in bf.addr_ver:
				# bitfields may have multiple numeric indexes, differing on ver
				indexname:str = get_newest_index_name(addr, bf)
				if indexname[:2] in {"ix", "mm"}: # caps name
					indexname = indexname[:2] + indexname[2:].upper()
				elif indexname[:3] == "reg": # caps name
					indexname = indexname[:3] + indexname[3:].upper()
				else:
					indexname.upper()
				# indexname is primary ver
				indexname:str  = indexname + "_" + bf.addr_ver[addr][1]
				fieldname:str = bf.name + "_" + tuple(bf.ver_addr)[0]
				indexname_fieldname:tuple = (indexname, fieldname)
				if addr in reg_list: 
					assert (indexname_fieldname not in reg_list[addr])
					reg_list[addr].append(indexname_fieldname)
				else:
					reg_list[addr] = [indexname_fieldname]

	# compose json5 file
	entry_count:int = 0
	reg_list:dict = dict(sorted(reg_list.items())) # sort by the address integer
	addr:int
	for addr in reg_list:
		entry_count += len(reg_list[addr])
		reg_list[addr].sort( # sort alphabetically within a numetic index
			key = lambda indexname_fieldname: indexname_fieldname[0]
		)
		indexname_fieldname:tuple
		for indexname_fieldname in reg_list[addr]:
			out_text += json5_entry % (
				indexname_fieldname[0], indexname_fieldname[1]
			)
	out_text = re.sub("(\t*)},\n(\t*){\n", "\\g<1>}, {\n", out_text) # lazy
	return out_text + json5_ender

# mode == 3
def get_val_from_bf(
		val:int,
		field:bitfield_entry
		) -> int:
	return (val >> field.lo) & ( (1<<(field.hi-field.lo)) -1)
def bf_regression(
		bitfields:dict,
		registers:list
		) -> list:
	# the intent is to brute-force possible register definitions for a set of
	# straps to the same field.
	# Go through all bitfields and find the ones that have the 'rsvd' valued
	# at 0
	candidates = []
	isbad:int = 0
	k:str
	for k in bitfields:
		bf:bitfield = bitfields[k]
		isbad:int = 0
		r:str
		for r in registers:
			f:bitfield_entry
			for f in bf.entries:
				if ((f.name[:4] == "rsvd") and (get_val_from_bf(int(r), f))):
					isbad = 1
					break
			if (isbad):
				break
		if not (isbad):
			candidates.append(bf)
	return candidates


def get_ver(
		file_name:str
		) -> str:
	fname_parts:list = file_name.split("_")
	verstr:str = fname_parts[1] + "_" + fname_parts[2] # major, minor
	if fname_parts[3].isdigit(): # patch
		verstr += "_" + fname_parts[3]
	return verstr

def main(
		argc:int,
		argv:list
		):
	assert (2 <= argc)
	arg_i:int = 1 # 1 to pop off the self name

	mode:int = int(argv[arg_i])
	arg_i += 1

	assert(0 <= mode)

	if 0 <= mode <= 2:
		assert(5 <= argc) # asic_reg.py mode outfile shmask offset
		output_file:str = argv[arg_i]
		arg_i += 1
		ip_name:str = argv[arg_i].split("_")[0].split("/")[-1].upper()

		num_input_files = argc - arg_i
		assert (num_input_files % 2 == 0) # shmask, offset pairs
		versions:list = []
		bitfields_byfile:list = []
		while (arg_i < argc):
			version:str = get_ver(argv[arg_i])
			versions.append(version)
			bitfields:dict
			with open(argv[arg_i], 'r', encoding="utf-8") as f:
				bitfields = shmask_filetext_to_bitfields(version, f.read())
			arg_i += 1
			assert(version == get_ver(argv[arg_i]))
			reg_name_id_pairs:dict
			with open(argv[arg_i], 'r', encoding="utf-8") as f:
				reg_name_id_pairs = text_to_dict(version, f.read())
			arg_i += 1
			bitfields_attach_reg_ids(version, bitfields, reg_name_id_pairs)
			bitfields_byfile.append(bitfields.copy())

		composite_bitfields = bitfields_intersect_add(bitfields_byfile)
		composite_bitfields = composite_bitfields_sort(composite_bitfields)

		# branch table
		output_text:str = (
			bitfield_to_header,
			bitfield_to_json5,
			bitfield_to_reglist,
		)[mode](ip_name, versions, composite_bitfields)

		with open(output_file, 'w', encoding="utf-8") as f:
			f.write(output_text)
	elif mode == 3:
		assert(4 <= argc)
		bitfields:dict
		with open(argv[arg_i],'r', encoding="utf-8") as f:
			bitfields = shmask_filetext_to_bitfields(version, f.read())
		straps_to_be_tested:list = argv[arg_i:]
		candidates = bf_regression(bitfields, straps_to_be_tested)
		c:bitfield
		for c in candidates:
			print(c.name)
	else:
		assert(0) # unsupported mode

if (__name__ == "__main__"):
	main(len(argv), argv)
