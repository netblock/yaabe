#!/usr/bin/env python
# -*- coding: utf-8 -*-

# In the python shell,
# from scripts.atui_tools import *
#
# Regex-based functions to use in a python interactive terminal to transform
# various C structures seen in atom/ into ATUI JSON5 as seen in
# atomtree/atui/tables/*.json5
#
# Many double backslash is to escape python for a literal \ to escape regex

import re

class __regexvar:
	# https://docs.python.org/3/howto/regex.html
	# nc is noncapture; it does not have a referencable group num

	white_0:str = "\\s*"
	white_1:str = "\\s+"
	tabs_nc:str = "(?:\t*)"
	tabs:str = "(" + tabs_nc + ")"
	space:str = "( +)"
	spacetab:str = "[ \t]*"
	nums:str = "(\\d+)"

	c_prefix_nc:str = "(?:struct|union)"
	c_prefix:str = "(" + c_prefix_nc + ")" + white_1
	c_num_types_nc:str = "(?:(?:u?int|float|uq\\d+_)\\d+_t)"
	c_num_types:str = "(" + c_num_types_nc + ")" + white_1
	c_ints_nc:str = "(?:(?:u?int)\\d+_t)"
	c_ints:str = "(" + c_ints_nc + ")" + white_1
	c_str_nc:str = "(?:char(?:\\d+_t)?)"
	c_str:str = "(" + c_str_nc +")" + white_1
	name_nc:str = "(?:[a-zA-Z_]\\w*)"
	name:str = "(" + name_nc + ")" + white_0

	array_alnum:str =   "\\["+white_0+ "(\\w*)"         +white_0+"\\]" +white_0
	array_var:str =     "\\["+white_0+ name             +white_0+"\\]" +white_0
	array_num:str =     "\\["+white_0+ "(\\d*)"         +white_0+"\\]" +white_0
	array_vlaflex:str = "\\["+white_0+ "("+name_nc+")?" +white_0+"\\]" +white_0
	#array_countedby_nc:str = "(?:__counted_by\\([\\w\\.]*\\))?" +white_0
	array_countedby_var:str = "(__counted_by\\(([\\w\\.]*)\\))" +white_0
	array_countedby_whole_q:str = "(__counted_by\\([\\w\\.]*\\))?" +white_0
	nonstring_nc:str = "(?:__nonstring)?" +white_0

	struct_or_cnumtype:str = "("  \
		+ "(?:" + c_prefix_nc + white_1 + name_nc + ")"  \
		+ "|(?:" + c_num_types_nc + ")"  \
	+ ")" + white_1

	hi_lo:str = ":" + nums + "-" + nums + " \\+1[,;]"

	c_enum:str = "(enum)" + white_1
	c_enum_equals:str = "=" + white_1 + "(\\S+),?" + spacetab

	comments:str = "(?:" + white_0 + "(//\\s*(.*)))?"
	flagged_comment:str = "__ATUIDESCR//\\s*(.*)"
	no_comment:str = tabs + "__ATUIDESCR\n"

def __atui_regex_prepare(
		text:str
		):
	text = re.sub("(\n\t*)    ","\\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\\g<1>\t", text)
	text = re.sub("[ \t]+\n", "\n", text)
	text = re.sub("\"","\\\"",text) # for comments
	return text

def struct_to_atui(
		text:str,
		explicit_attributes:bool=False,
		print_text:bool=True
		):
	s:__regexvar = __regexvar
	text = __atui_regex_prepare(text)
	atui_dec:str = "\\g<1>\t\tdisplay: \"ATUI_DEC\",\n"

	# self struct:
	branch_text:str = """{\n\tc_type: "\\g<2>",\n"""
	if explicit_attributes:
		branch_text = """\
{
	c_prefix:"\\g<1>", c_type: "\\g<2>",
	atomtree: "atui_nullstruct",
"""
	branch_text += """\
	__ATUIDESCR\\g<3>
	leaves: [\
"""
	text = re.sub(
		s.c_prefix + s.name + "{" + s.comments,
		branch_text,
		text
	)
	text = re.sub("};","\t],\n},", text)

	# ATUI_DYNARRAY part 1
	dynarray:str = """
		{
			access: "bios->\\g<2>",
			name: "\\g<2>",
			__ATUIDESCR\\g<5>
			display: "ATUI_DISPLAY",
			fancy: "ATUI_DYNARRAY", fancy_data: {
				deferred: "NULL",
				count: "\\g<3>\\g<4>",
				enum: "ATUI_NULL",
				pattern: [\
			\\g<1> \\g<2>;],
			},
		},\
"""
	text = re.sub(
		"\\s*" + s.struct_or_cnumtype + s.name + s.array_vlaflex
		+ s.array_countedby_whole_q + ";" + s.comments,
		dynarray,
		text
	)
	text = re.sub(
		"count: \"" + s.array_countedby_var + "\"",
		"count: \"bios->\\g<2>\"",
		text
	)

	# ATUI_GRAFT
	inline:str = """\
\\g<1>	{
\\g<1>		access: "bios->\\g<4>",
\\g<1>		name: "\\g<4>",
\\g<1>		display: "ATUI_DISPLAY",
\\g<1>		fancy: "ATUI_GRAFT", fancy_data: "\\g<3>",
\\g<1>		__ATUIDESCR\\g<7>
\\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_prefix + s.name + s.name + "("+s.array_num+")?;"
		+ s.comments,
		inline,
		text
	)

	# ATUI_ENUM
	enum:str = """\
\\g<1>	{
\\g<1>		access: "bios->\\g<4>",
\\g<1>		name: "\\g<4>",
\\g<1>		display: ["ATUI_DEC", "ATUI_ENUM",],
\\g<1>		__ATUIDESCR\\g<7>
\\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_enum + s.name + s.name + "("+s.array_num+")?;"
		+ s.comments,
		enum,
		text
	)

	# ATUI_NOFANCY
	simple_nums:str = """\
\\g<1>	{
\\g<1>		access: "bios->\\g<3>",
\\g<1>		name: "\\g<3>",
"""
	if explicit_attributes:
		simple_nums += atui_dec
	simple_nums += """\
\\g<1>		__ATUIDESCR\\g<4>
\\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_num_types + s.name + ";" + s.comments,
		simple_nums,
		text
	)

	# ATUI_ARRAY
	num_arrays:str = """\
\\g<1>	{
\\g<1>		access: "bios->\\g<3>",
\\g<1>		name: "\\g<3>",
\\g<1>		display: "ATUI_HEX",
\\g<1>		fancy: "ATUI_ARRAY",
\\g<1>		__ATUIDESCR\\g<5>
\\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_num_types + s.name + s.array_num + ";"
		+ s.comments,
		num_arrays,
		text
	)

	# ATUI_ARRAY based string
	string_arrays:str = """\
\\g<1>	{
\\g<1>		access: "bios->\\g<3>",
\\g<1>		name: "\\g<3>",
\\g<1>		display: "ATUI_NAN",
\\g<1>		fancy: "ATUI_ARRAY",
\\g<1>		__ATUIDESCR\\g<5>
\\g<1>	},\
"""
	text = re.sub(
		s.tabs + s.c_str + s.name + s.array_num + s.nonstring_nc + ";"
		+ s.comments,
		string_arrays,
		text
	)

	# descriptions
	descriptions:str = """\
\\g<1>description: [
\\g<1>	{language: "english", text: "\\g<2>",},
\\g<1>],\
"""
	text = re.sub(
		s.tabs + s.flagged_comment,
		descriptions,
		text
	)
	text = re.sub(s.no_comment, "", text)

	text = re.sub(
		s.tabs + "},\n" + s.tabs + "{\n",
		"\\g<1>}, {\n",
		text
	)

	# ATUI_DYNARRAY part 2
	text = re.sub(
		"pattern: \\[" + s.tabs + "{",
		"pattern: [{",
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
	s:__regexvar = __regexvar
	text = __atui_regex_prepare(text)

	union_text:str = """{\n\tc_prefix: "\\g<1>", c_type: "\\g<2>",\n"""
	if explicit_attributes:
		union_text = """\
{
	c_prefix: "\\g<1>", c_type: "\\g<2>",
	atomtree: "atui_nullstruct",
"""
	union_text += """\
	__ATUIDESCR\\g<3>
	leaves: [\
"""
	text = re.sub(
		s.c_prefix + s.name + "{" + s.comments,
		union_text,
		text
	)
	tail_cap:str = """\
		],},
	},],
},\
	"""
	text = re.sub(
		"\t};\n};",
		tail_cap,
		text
	)


	# main leaf
	bitfield_leaf:str = """\
\\g<1>{
\\g<1>	access: "bios->\\g<3>",
\\g<1>	name: "\\g<3>",
\\g<1>	display: "ATUI_BIN",
\\g<1>	__ATUIDESCR\\g<4>
\\g<1>	fancy: "ATUI_BITFIELD", fancy_data: { fields: [\
"""
	text = re.sub(
		s.tabs + s.c_ints + s.name + ";" + s.comments,
		bitfield_leaf,
		text
	)

	# eat struct { uint, for non-enum fields
	text = re.sub("\tstruct {( uint[0-9]+_t)?\n", "", text)

	# eat the generic int prefixes if we're doing bitfield enums
	text = re.sub(s.c_ints, "", text)

	# bitfield enries
	bit_child:str = """\
\\g<1>	{
\\g<1>		name: "\\g<4>",
\\g<1>		__ATUIDESCR\\g<8>
\\g<1>		__ATUIBITENUM\\g<3>
\\g<1>	},\
"""
	text = re.sub(
		s.tabs + "(?:" + s.c_enum + s.name + ")?" + s.name + s.space + s.hi_lo
		+ s.comments,
		bit_child,
		text
	)

	enumless:str = ""
	if explicit_attributes:
		enumless = "\\g<1>display: \"ATUI_DEC\",\n"
	text = re.sub(
		s.tabs + "__ATUIBITENUM\n",
		enumless,
		text
	)

	bitenum:str = """\
\\g<1>display: ["ATUI_DEC", "ATUI_ENUM",],
\\g<1>enum: "\\g<2>",
"""
	text = re.sub(
		s.tabs + "__ATUIBITENUM" + s.name + "\n",
		bitenum,
		text
	)

	# descriptions
	descriptions:str = """\
\\g<1>description: [
\\g<1>	{language: "english", text: "\\g<2>",},
\\g<1>],\
"""
	text = re.sub(
		s.tabs + s.flagged_comment,
		descriptions,
		text
	)
	text = re.sub(s.no_comment, "", text)

	text = re.sub(
		s.tabs + "},\n" + s.tabs + "{\n",
		"\\g<1>}, {\n",
		text
	)
	text = re.sub(
		s.tabs + "leaves: \\[\n" + s.tabs + "{\n",
		"\\g<1>leaves: [{\n",
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
	s:__regexvar = __regexvar
	text = __atui_regex_prepare(text)

	# main enum body
	enum_text:str = """\
{name: "\\g<2>",
	__ATUIDESCR\\g<5>
	constants: [\
"""
	text = re.sub(
		s.c_enum + s.name + "(?::\\s*("+s.c_num_types+"))\\s*{" + s.comments,
		enum_text,
		text
	)

	text = re.sub("};","]},", text)

	# enum entries
	var_text:str = """\
		{name: "\\g<2>",
			__ATUIDESCR\\g<4>
		},\
"""
	text = re.sub(
		s.tabs + s.name + s.c_enum_equals + s.comments,
		var_text,
		text
	)

	# descriptions
	descriptions:str = """\
\\g<1>description: [
\\g<1>	{language: "english", text: "\\g<2>",},
\\g<1>],\
"""
	text = re.sub(
		s.tabs + s.flagged_comment,
		descriptions,
		text
	)
	text = re.sub(s.no_comment, "", text)

	# (?<!...) is, matches if not preceeded by ...
	text = re.sub("(?<!\\],)\n" +s.tabs+ "},\n", "},\n", text)

	if print_text:
		pass
		print(text)
	else:
		return text
