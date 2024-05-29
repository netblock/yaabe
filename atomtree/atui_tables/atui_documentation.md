# Format

ATUI's metaprogramming is represented in JSON5, and what kind of data it holds
is determined with the `class` attribute.

the top-level as follows
``` json5
{class: "branch",
global_default: {
	...
}, branches: [
	...
], }
```

The `branch` class type is for describing C structs and their elements as
branch-leaf complexes; 'branch' is a struct, and 'leaf' is an element of that
struct.

The `enum` class type is for building a read-only structure of value-string
pairs regarding a named constant.

The `array` class type works much the same way, but for a simple read-only
array[].

The `searchfield` is for `asic_reg_tools.h`, and is about  building an
`enum`-esque val-name pair array of register IDs and their names.

<br>

# global\_default

`global_default` is currently only for the `branch` class. It holds branch and
leaf data that will be used to infer missing fields.

For `leaf_defaults`, the `generic` is for all leaves, except for bitfield
children and dynarray patterns, which are what `bitchild` and `dynpattern` are
for respectively.

``` json5
global_default: {
	branch_defaults: {
		c_prefix: "struct",
		atomtree: "atui_nullstruct", // nullstruct is an empty struct
		table_start: "bios",
		table_size: "sizeof(*bios)",
	},
	leaf_defaults: {
		generic: {
			display: "ATUI_DEC",
			fancy: "ATUI_NOFANCY",
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
},
```

<br>

# Basic Usage and Namespaces

There are two namespaces available, `bios` and `atomtree`.

`bios` is the struct that the branch represents, straightforward; for example
the structs defined in the headers in the `atom/` directory.

`atomtree` is an optional atomtree association that could be useful to pull in
computed data; or even represent atomtree-computed data as leaves.

declaration pseudo example:

``` json5
{
	c_prefix: "struct", // union or struct
	c_type: "bios_struct", // if name is unset, name will be this
	atomtree: "relevant_atomtree_struct",
	name: "alternative_name", // optional; affects display name and call name

	// pointer and the size of the contiguous memory the branch represents
	table_start: "bios",
	table_size: "sizeof(*bios)",

	description: [
		{language: "english", text "..."},
	],
	leaves: [
		{
			access: "bios->bios_element", // will automatically reference
			name: "bios element", // can have spaces
			display: "ATUI_HEX",  // radix
			fancy: "ATUI_NOFANCY",
			description: [ // optional
				{language: "english", text "..."},
			],
		}, {
			access: "bios->bios_subtable",
			name: "subtable",
			display: "ATUI_NAN",
			fancy: "ATUI_GRAFT", fancy_data: "bios_subtable_v1",
			description: [
				{language: "english", text "..."},
			],
		},
	],
},
```

instantiation pseudo example:

``` C
atui_branch* foba = ATUI_MAKE_BRANCH(alternative_name,
	"optional UI rename",
	atomtree_pointer, bios_pointer,
	number_of_child_branches, child_branches_array
)
```
`child_branches_array` can be `NULL`; but if it is not, it must be
`number_of_child_branches` long. 

To add a branch as a child to another branch,

``` C
ATUI_ADD_BRANCH(parent_branch, child_branch);
```

<br>


# Display / Fancy

The display and fancy will appropriately set `atui_type` within the leaf.

`union atui_type.signed_num` and `union atui_type.fraction` are usually set
automatically based on the C data type.

## Display / Radix

If the table element should be viewed as a number, set the `display` to a radix:
`ATUI_DEC`, `ATUI_HEX`, `ATUI_OCT`, `ATUI_BIN`.

If a leaf should be signed with Two's Complement despite the underlying
C data type, set the leaf's `display` property to be a list that includes
`ATUI_SIGNED` and its main radix.

If the leaf should exist as a visual entry but shouldn't display a value, set
the `display` to `ATUI_NAN`.

If the leaf should be omitted from UI display entirely, set the `display` to
`ATUI_NODISPLAY`. Note that this will prevent display its children if it has
any. If the leaf's children should be viewed anyway, set the `display` to
`ATUI_SUBONLY`. All other cases imply `ATUI_DISPLAY`.

<br>

## Fancy Types

Fancy types allow a leaf to present extra information beyond a value from the
bios straightforward.

<br>

### ATUI\_BITFIELD

Classic bitfield representation. 

The child leaves will assume missing fields from the `bitchild` section in
`global_defaults`. 

The children will be automatically marked with `_ATUI_BITCHILD` as its
fancy type; as a result, the children can't have a fancy type.

If the leaf should be viewed in base 2, but also has bitfields for children:

``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_HEX",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_BITFIELD", fancy_data: [
		{
			name: "bitfield entry name 0",
			hi: 7, lo: 0,
			display: "ATUI_DEC",
			description: [
				{language: "english", text "..."},
			],
		}, {
			name: "bitfield entry name 1",
			hi: 31, lo: 8,
			display: ["ATUI_DEC", "ATUI_SIGNED"], // order doesn't matter
		},
	],
},
```

<br>

### ATUI\_ENUM

If the element should have a list of text-val pairs, an enum, assocated with it,
first populate the atui enum in `atui_enums.json5`:

``` json5
{name: "enum_struct_name"
	{name: "ENUM_ENTRY1",},
	{name: "ENUM_ENTRY2",},
	{name: "ENUM_ENTRY3",},
]},
```

And then for the atui leaf,

``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_HEX",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_ENUM", fancy_data: "enum_struct_name"
},
```

<br>

### ATUI\_GRAFT

If the element should embed a `atui_branch` to take/graft their leaves,

``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_NAN",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_GRAFT", fancy_data: "table_to_inline"
},
```

If you want to import just the leaves of the table, as if it was the leaves of
the branch you're constructing, set the `display` to `ATUI_SUBONLY`.

Also make sure the branch/table is defined elsewhere in ATUI.

<br>

### ATUI\_SHOOT

Working much the same way as `ATUI_GRAFT`, if the element should reference a
`atui_branch` to automatically integrate as a child branch,

``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_HEX",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_SHOOT", fancy_data: "table_to_inline"
},
```

Since it isn't a leaf but a reference to another branch, `display` is ignored,
and the leaf won't exist in the instantiation.

The name of the branch object will copy the UI display name of the leaf.

<br>

### ATUI\_STRING / ATUI\_ARRAY

If the element is a dynamically-sized NUL-terminated string, set the `fancy` to
`ATUI_STRING`. 

If it's an array, data will be represented in the radix of your choosing, with
the exception of fractions. If the array is text but has a static size, set the
fancy to `ATUI_ARRAY` and radix to `ATUI_NAN`.

``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_NAN",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_STRING"
},
{
	access: "bios->bios_element2",
	name: "bios element2",
	display: "ATUI_HEX",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_ARRAY"
},
```

<br>

### ATUI\_DYNARRAY
``` json5
{
	access: "bios->array_start_pointer",
	name: "bios tables",
	display: "ATUI_NAN",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_DYNARRAY", fancy_data: {
		deferred: "source->deferred_pointers",
		count: "source->dynarray_number_of_elements"
		enum: "enum_name",
		pattern: [
			{
				name: "bios element",
				display: "ATUI_HEX",
				fancy: "ATUI_NOFANCY",
				description: [
					{language: "english", text "..."},
				],
			},
		],
	},
},
```

`ATUI_DYNARRAY` is essentially a loop type. If there is an array of structs,
or number of elements needs a runtime computation, `ATUI_DYNARRY` can pull in
the boundaries.

The leaf pattern follows regular syntax and takes assumptions from the 
`dynpattern` section in `global_defaults`. Nested `ATUI_DYNARRAY` should be
possible but is untested.

<br>

`dynarray_start_pointer` is a direct pointer that is treated as the beginning of
the array, such that access would be effectively, 

``` C
datatype* dataptr = &(source->array_start_pointer[i]);
```

`deferred_pointers` is an array of pointers, each of which points an element,
such that access would be effectively,
``` C
datatype* dataptr = source->deferred_pointers[i];
```

`array_start_pointer` takes precedence over `deferred pointers`; to use
`deferred_pointers`, `array_start_pointer` must be `NULL`.

`dynarray_number_of_elements` counts how long the array goes on for. The element
size will be automatically determined based on the C type.

<br>

If an enum should tag along for UI/naming purposes, state an enum; otherwise
state the enum name as `ATUI_NULL` . The enum will be walked through
sequentially in the order as it is defined with `PPATUI_ENUMER()`.
Furthermore, make sure the enum has an associated `PPATUI_ENUMER()` definition.

The dynarray leaf can follow `ATUI_SUBONLY` and `ATUI_NODISPLAY`.
