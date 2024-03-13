# Basic Usage and Namespaces

There are two namespaces available, `bios` and `atomtree`.
`bios` is the struct that the branch represents, straightforward,
`atomtree` is an optional atomtree association that could be useful to pull in
computed data; or even represent atomtree-computed data as leaves.

declaration pseudo example:

``` json5
{
	c_prefix: "struct", // union or struct
	c_type: "bios_struct",
	name: "alternative_name", // affects display name and call name
	atomtree: "relevant_atomtree_struct",
	description: [
		{language: "english", text "..."},
	],
	leaves: [
		{
			access: "bios->bios_element",
			name: "bios element",
			display: "ATUI_HEX", // radix
			fancy: "ATUI_NOFANCY",
			description: [
				{language: "english", text "..."},
			],
		}, {
			access: "bios->bios_subtable",
			name: "subtable",
			display: "ATUI_NAN",
			fancy: "ATUI_INLINE", fancy_data: "bios_subtable_v1",
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

After instantiation, to add a branch as a child to another branch,

``` C
ATUI_ADD_BRANCH(parent_branch, child_branch);
```



# Display / Fancy

The display and fancy will appropriately set `atui_type` within the leaf.

`ATUI_FRAC` and `ATUI_SIGNED` are automatically detected and set based on the C
data type.

`ATUI_FRAC` can signify if it should be viewed as a decimal fraction number.

`ATUI_SIGNED` can signify if it's a signed number. It can be useful manually
setting this if an element within a bitfield is signed.


## Display / Radix

If the table element should be viewed as a number, set the `display` to a radix:
`ATUI_DEC`, `ATUI_HEX`, `ATUI_OCT`, `ATUI_BIN`.

If the leaf should exist as a visual entry but shouldn't display a value, set
the `display` to `ATUI_NAN`.

If the leaf should be omitted from UI display entirely, set the `display` to
`ATUI_NODISPLAY`. Note that this will still display its children if it has any.


## Fancy Types

Fancy types allow a leaf to present extra information beyond a value from the
bios straightforward.

### ATUI\_BITFIELD

If the leaf should be viewed in base 2, but also has bitfields for children:

``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_HEX", // radix
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
			display: "(ATUI_DEC | ATUI_SIGNED)",
		},
	],
},
```

The child leaves will be marked with `_ATUI_BITCHILD` in its type to aid UI
layout.

If a child is should be signed with Two's Complement, set `ATUI_SIGNED` in its
radix alongside its main radix.


### ATUI\_ENUM

If the element should have a list of text-val pairs, an enum,
First populate the atui enum in `atui_enums.h`:

```
PPATUI_ENUMER(enum_struct_name,
	ENUM_ENTRY1,
	ENUM_ENTRY2,
	ENUM_ENTRY3,
)
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

### ATUI\_INLINE

If the element should reference a table, a `atui_branch` to inline as a
collection of leaves,
``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_NAN",
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_INLINE", fancy_data: "table_to_inline"
},
```

If you want to import just the leaves of the table, as if it was the leaves of
the branch you're constructing, set the `display` to `ATUI_NODISPLAY`.

While not practically useful, the name of the branch object will copy the UI
display name of the leaf.

Also make sure the table is defined elsewhere in ATUI.

### ATUI\_PETIOLE

If the element should reference a table, a atui\_branch to integrate as a child
branch,

``` json5
{
	access: "bios->bios_element",
	name: "bios element",
	display: "ATUI_HEX", // radix
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_PETIOLE", fancy_data: "table_to_inline"
},
```

Since it isn't a leaf but a reference to another branch, `display` is ignored.
The name of the branch object will copy the UI display name of the leaf.

Also make sure the table is populated with an ATUI\_FUNCIFY().

### ATUI\_STRING / ATUI\_ARRAY

If the element is a dynanmically-sized 0-terminated string, set the `fancy` to
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
	display: "ATUI_HEX", // radix
	description: [
		{language: "english", text "..."},
	],
	fancy: "ATUI_ARRAY"
},
```

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

If there is an array or number of leaves that is dynamically sized, especially
if it has a dynamic allocation, `ATUI_DYNARRY` can pull in the boundaries from
atomtree.

The leaf pattern follows regular syntax, and can be a bitfield.

`dynarray_start_pointer` is a direct pointer that is treated as the beginning of
the array, such that access would be effectively, `datatype* dataptr = &(source->array_start_pointer[i]);`

`deferred_pointers` is an array of pointers, each of which points an element,
such that access would be effectively, `datatype* dataptr = source->deferred_pointers[i];`

`dynarray_start_pointer` is for contiguous isometric arrays; `deferred_pointers`is for arrays whose elements are not necessarily contiguous, and/or not
necessarily equally-sized (eg strings, for `ATUI_STRING`).
`array_start_pointer` takes precedence over deferred pointers; to use
`deferred_pointers`, `array_start_pointer` must be `NULL`.

`dynarray_number_of_elements` counts how long the array goes on for.

If an enum should tag along for UI/naming purposes, state an enum; otherwise
state the enum name as `ATUI_NULL` . The enum will be walked through
sequentually in the order as it is defined with `PPATUI_ENUMER()`.
Futhermore, make sure the enum has an associated `PPATUI_ENUMER()` definition.

Leaf top UI name won't get displayed if `ATUI_NODISPLAY` is set for the radix,
