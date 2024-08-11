#!/usr/bin/env python
# -*- coding: utf-8 -*-

# In the python shell,
# from scripts.atui_tools import *
#
# Regex-based functions to use in a python interactive terminal to transform
# various C structures seen in atom/ into ATUI JSON5 as seen in
# atomtree/atui/tables/*.json5


import re

class __regexvar:
	# https://docs.python.org/3/howto/regex.html
	# nc is noncapture; it does not have a referencable group num

	white = "\s*"
	tabs_nc = "(?:\t+)"
	tabs = "(" + tabs_nc + ")"
	space = "( +)"
	spacetab = "[ \t]*"
	nums = "(\d+)"

	c_prefix_nc = "(?:struct|union)"
	c_prefix = "(" + c_prefix_nc + ")" + white
	c_num_types_nc = "(?:(?:u?int|char|float|uq\d+_)\d+_t)"
	c_num_types = "(" + c_num_types_nc + ")" + white
	c_ints_nc = "(?:(?:u?int|char)[0-9]+_t)"
	c_ints = "(" + c_ints_nc + ")" + white
	name_nc = "(?:[a-zA-Z_]\w*)"
	name = "(" + name_nc + ")" + white

	#array_alnum =  "\["+white+ "(\w*)"          +white+"\]" +white
	#array_var =    "\["+white+ name             +white+"\]" +white
	array_num =     "\["+white+ "(\d*)"          +white+"\]" +white
	array_vlaflex = "\["+white+ "("+name_nc+")?" +white+"\]" +white
	#array_countedby_nc = "(?:__counted_by\(\w*\))?" +white
	array_countedby_var = "(__counted_by\((\w*)\))" +white
	array_countedby_whole_q = "(__counted_by\(\w*\))?" +white

	struct_or_cnumtype = "("  \
		+ "(?:" + c_prefix_nc + white + name_nc + ")"  \
		+ "|(?:" + c_num_types_nc + ")"  \
	+ ")" + white

	hi_lo = ":" + nums + "-" + nums + " \+1[,;]"

	c_enum = "(enum)" + white
	c_enum_type = ":" + white + c_num_types
	c_enum_equals = "=" + white + "([^,]+)," + spacetab

	comments = "(?:" + white + "(//\s*(.*)))?"
	flagged_comment = "__ATUIDESCR//\s*(.*)"
	no_comment = tabs + "__ATUIDESCR\n"

def __atui_regex_prepare(
		text:str
		):
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("[ \t]+\n", "\n", text)
	text = re.sub("\"","\\\"",text) # for comments
	return text

def struct_to_atui(
		text:str,
		explicit_attributes:bool=False,
		print_text:bool=True
		):
	s = __regexvar()
	text = __atui_regex_prepare(text)
	atui_dec = "\g<1>\t\tdisplay: \"ATUI_DEC\",\n"

	# self struct:
	branch_text = """{\n\tc_type: "\g<2>",\n"""
	if explicit_attributes:
		branch_text = """\
{
	c_prefix:"\g<1>", c_type: "\g<2>",
	atomtree: "atui_nullstruct",
"""
	branch_text += """\
	__ATUIDESCR\g<3>
	leaves: [\
"""
	text = re.sub(
		s.c_prefix + s.name + "{" + s.comments,
		branch_text,
		text
	)
	text = re.sub("};","\t],\n},", text)

	# ATUI_DYNARRAY
	dynarray = """
		{
			access: "bios->\g<2>",
			name: "\g<2>",
			__ATUIDESCR\g<5>
			display: "ATUI_DISPLAY",
			fancy: "ATUI_DYNARRAY", fancy_data: {
				deferred: "NULL",
				count: "\g<3>\g<4>",
				enum: "ATUI_NULL",
				pattern: [
				\g<1> \g<2>;
				],
			},
		},\
"""
	text = re.sub(
		"\s*" + s.struct_or_cnumtype + s.name + s.array_vlaflex
		+ s.array_countedby_whole_q + ";" + s.comments,
		dynarray,
		text
	)
	text = re.sub(
		"count: \"" + s.array_countedby_var + "\"",
		"count: \"bios->\g<2>\"",
		text
	)

	# ATUI_GRAFT
	inline = """\
\g<1>	{
\g<1>		access: "bios->\g<4>",
\g<1>		name: "\g<4>",
\g<1>		display: "ATUI_DISPLAY",
\g<1>		fancy: "ATUI_GRAFT", fancy_data: "\g<3>",
\g<1>		__ATUIDESCR\g<7>
\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_prefix + s.name + s.name + "("+s.array_num+")?;"
		+ s.comments,
		inline,
		text
	)

	# ATUI_ENUM
	enum = """\
\g<1>	{
\g<1>		access: "bios->\g<4>",
\g<1>		name: "\g<4>",
"""
	if explicit_attributes:
		enum += atui_dec
	enum += """\
\g<1>		fancy: "ATUI_ENUM", fancy_data: "\g<3>",
\g<1>		__ATUIDESCR\g<7>
\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_enum + s.name + s.name + "("+s.array_num+")?;"
		+ s.comments,
		enum,
		text
	)

	# ATUI_NOFANCY
	simple_nums = """\
\g<1>	{
\g<1>		access: "bios->\g<3>",
\g<1>		name: "\g<3>",
"""
	if explicit_attributes:
		simple_nums += atui_dec
	simple_nums += """\
\g<1>		__ATUIDESCR\g<4>
\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_num_types + s.name + ";" + s.comments,
		simple_nums,
		text
	)

	# ATUI_ARRAY
	num_arrays = """\
\g<1>	{
\g<1>		access: "bios->\g<3>",
\g<1>		name: "\g<3>",
\g<1>		display: "ATUI_HEX",
\g<1>		fancy: "ATUI_ARRAY",
\g<1>		__ATUIDESCR\g<5>
\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_num_types + s.name + s.array_num + ";" + s.comments,
		num_arrays,
		text
	)

	# descriptions
	descriptions = """\
\g<1>description: [
\g<1>	{language: "english", text: "\g<2>",},
\g<1>],\
"""
	text = re.sub(
		s.tabs + s.flagged_comment,
		descriptions,
		text
	)
	text = re.sub(s.no_comment, "", text)

	text = re.sub(
		s.tabs + "},\n" + s.tabs + "{\n",
		"\g<1>}, {\n",
		text
	)

	if print_text:
		print(text)
	else:
		return text


def bitfield_to_atui(
		text:str,
		explicit_attributes:bool=False,
		print_text:bool=True
		):
	s = __regexvar()
	text = __atui_regex_prepare(text)

	union_text = """{\n\tc_type: "\g<2>",\n"""
	if explicit_attributes:
		union_text = """\
{
	c_prefix:"\g<1>", c_type: "\g<2>",
	atomtree: "atui_nullstruct",
"""
	union_text += """\
	__ATUIDESCR\g<3>
	leaves: [\
"""
	text = re.sub(
		s.c_prefix + s.name + "{" + s.comments,
		union_text,
		text
	)
	text = re.sub(
		"\t};\n};",
		"\t\t\t],\n\t\t},\n\t],\n},",
		text
	)


	# main leaf
	bitfield_leaf = """\
\g<1>	{
\g<1>		access: "bios->\g<3>",
\g<1>		name: "\g<3>",
\g<1>		display: "ATUI_BIN",
\g<1>		__ATUIDESCR\g<4>
\g<1>		fancy: "ATUI_BITFIELD", fancy_data: [\
"""
	text = re.sub(
		s.tabs + s.c_ints + s.name + ";" + s.comments,
		bitfield_leaf,
		text
	)

	# eat struct { uint
	text = re.sub("\tstruct { uint[0-9]+_t\n", "", text)

	# bitfield enries
	bit_child = """\
\g<1>		{
\g<1>			name: "\g<2>",
\g<1>			hi: \g<4>, lo: \g<5>,
\g<1>			__ATUIDESCR\g<6>
"""
	if explicit_attributes:
		bit_child += "\g<1>\t\t\tdisplay: \"ATUI_DEC\",\n"
	bit_child += "\g<1>\t\t},"
	text = re.sub(
		s.tabs + s.name + s.space + s.hi_lo + s.comments,
		bit_child,
		text
	)

	# descriptions
	descriptions = """\
\g<1>description: [
\g<1>	{language: "english", text: "\g<2>",},
\g<1>],\
"""
	text = re.sub(
		s.tabs + s.flagged_comment,
		descriptions,
		text
	)
	text = re.sub(s.no_comment, "", text)

	text = re.sub(
		s.tabs + "},\n" + s.tabs + "{\n",
		"\g<1>}, {\n",
		text
	)

	if print_text:
		print(text)
	else:
		return text


def enum_to_atui(
		text:str,
		explicit_attributes:bool=False,
		print_text:bool=True
		):
	s = __regexvar()
	text = __atui_regex_prepare(text)

	# main enum body
	enum_text = """\
{name: "\g<2>",
	__ATUIDESCR\g<5>
	constants: [\
"""
	text = re.sub(
		s.c_enum + s.name + "("+s.c_enum_type+")?"+ "{" + s.comments,
		enum_text,
		text
	)
	text = re.sub("};","]},", text)

	# enum entries
	var_text = """\
		{name: "\g<2>",
			__ATUIDESCR\g<4>
		},\
"""
	text = re.sub(
		s.tabs + s.name + s.c_enum_equals + s.comments,
		var_text,
		text
	)

	# descriptions
	descriptions = """\
\g<1>description: [
\g<1>	{language: "english", text: "\g<2>",},
\g<1>],\
"""
	text = re.sub(
		s.tabs + s.flagged_comment,
		descriptions,
		text
	)
	text = re.sub(s.no_comment, "", text)
	text = re.sub("(?<!\],)\n" +s.tabs+ "},\n", "},\n", text)

	if print_text:
		pass
		print(text)
	else:
		return text
