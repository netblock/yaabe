#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re

# In the python shell,
# from scripts.atui_tools import *

def struct_to_atui(
		text,
		explicit_attributes=False,
		print_text=True
		):

	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("[ \t]+\n", "\n", text)

	white = "\s*"
	tabs = "(\t+)"
	nums = "(\d+)"
	c_prefix = "(struct|union)" + white
	c_enum = "(enum)" + white
	c_num_types = "((?:u?int|char|float|uq\d+_)\d+_t)" + white
	c_ints = "((?:u?int|char)[0-9]+_t)" + white
	name = "([a-zA-Z_]\w*)" + white
	array_alnum = "\["+white +"(\w*)"+ white+"\]" + white
	array_var = "\["+white +name+ white+"\]" + white
	array_num = "\["+white +"(\d*)"+ white+"\]" + white
	comments = "(?:" + white + "(//\s*(.*)))?"
	flagged_comment = "__ATUIDESCR//\s*(.*)"
	no_comment = tabs + "__ATUIDESCR\n"

	atui_dec = "\g<1>\t\tdisplay: \"ATUI_DEC\",\n"

	text = re.sub("\"","\\\"",text) # for comments

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
		c_prefix + name + "{" + comments,
		branch_text,
		text
	)
	text = re.sub("};","\t],\n},", text)

	# ATUI_DYNARRAY
	dynarray = """
		{
			access: "bios->\g<3>",
			name: "\g<3>",
			__ATUIDESCR\g<5>
			display: "ATUI_NAN",
			fancy: "ATUI_DYNARRAY", fancy_data: {
				deferred: "NULL",
				count: "\g<4>",
				enum: "ATUI_NULL",
				pattern: [
				\g<1> \g<2> \g<3>;
				],
			},
		},\
"""
	text = re.sub(
		"\s*" + c_prefix + name + name + array_alnum + ";" + comments,
		dynarray,
		text
	)
	text = re.sub(
		"\s*" + c_num_types + "()" + name + array_var + ";" + comments,
		dynarray,
		text
	)

	# ATUI_GRAFT
	inline = """\
\g<1>	{
\g<1>		access: "bios->\g<4>",
\g<1>		name: "\g<4>",
\g<1>		display: "ATUI_NAN",
\g<1>		fancy: "ATUI_GRAFT", fancy_data: "\g<3>",
\g<1>		__ATUIDESCR\g<7>
\g<1>	},\
"""
	text = re.sub(
		tabs + c_prefix + name + name + "("+array_num+")?;" + comments,
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
		tabs + c_enum + name + name + "("+array_num+")?;" + comments,
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
		tabs + c_num_types + name + ";" + comments,
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
		tabs + c_num_types + name + array_num + ";" + comments,
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
		tabs + flagged_comment,
		descriptions,
		text
	)
	text = re.sub(no_comment, "", text)

	text = re.sub(
		tabs + "},\n" + tabs + "{\n",
		"\g<1>}, {\n",
		text
	)

	if print_text:
		print(text)
	else:
		return text


def bitfield_to_atui(
		text,
		explicit_attributes=False,
		print_text=True
		):
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("[ \t]+\n", "\n", text)

	white = "\s*"
	tabs = "(\t+)"
	space = "( +)"
	nums = "(\d+)"
	c_prefix = "(struct|union)" + white
	c_ints = "((?:u?int|char)[0-9]+_t)" + white
	name = "([a-zA-Z_]\w*)" + white
	hi_lo = ":" + nums + "-" + nums + " \+1[,;]"
	comments = "(?:" + white + "(//\s*(.*)))?"
	flagged_comment = "__ATUIDESCR//\s*(.*)"
	no_comment = tabs + "__ATUIDESCR\n"

	text = re.sub("\"","\\\"",text) # for comments

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
		c_prefix + name + "{" + comments,
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
		tabs + c_ints + name + ";" + comments,
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
		tabs + name + space + hi_lo + comments,
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
		tabs + flagged_comment,
		descriptions,
		text
	)
	text = re.sub(no_comment, "", text)

	text = re.sub(
		tabs + "},\n" + tabs + "{\n",
		"\g<1>}, {\n",
		text
	)

	if print_text:
		print(text)
	else:
		return text


def enum_to_atui(
		text,
		explicit_attributes=False,
		print_text=True
		):
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("(\n\t*)    ","\g<1>\t", text)
	text = re.sub("[ \t]+\n", "\n", text)

	white = "\s*"
	tabs = "(\t+)"
	space = "( +)"
	spacetab = "[ \t]*"
	c_num_types = "((?:u?int|char|float|uq\d+_)\d+_t)" + white
	c_ints = "((?:u?int|char)[0-9]+_t)" + white
	c_enum = "(enum)" + white
	c_enum_type = ":" + white + c_num_types
	c_enum_equals = "=" + white + "([^,]+)," + spacetab
	name = "([a-zA-Z_]\w*)" + white
	comments = "(?:" + white + "(//\s*(.*)))?"
	flagged_comment = "__ATUIDESCR//\s*(.*)"

	no_comment = tabs + "__ATUIDESCR\n"

	text = re.sub("\"","\\\"",text) # for comments

	# main enum body
	enum_text = """\
{name: "\g<2>",
	__ATUIDESCR\g<5>
	constants: [\
"""
	text = re.sub(
		c_enum + name + "("+c_enum_type+")?"+ "{" + comments,
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
		tabs + name + c_enum_equals + comments,
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
		tabs + flagged_comment,
		descriptions,
		text
	)
	text = re.sub(no_comment, "", text)
	text = re.sub("(?<!\],)\n" +tabs+ "},\n", "},\n", text)

	if print_text:
		pass
		print(text)
	else:
		return text
