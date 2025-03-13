// opaque definitions

#ifndef ATUI_TYPES_H
#define ATUI_TYPES_H

struct atom_tree;

typedef struct _atui_branch atui_branch;
typedef struct _atui_leaf atui_leaf;

typedef struct atui_func_args atuiargs;
typedef typeof(atui_branch* (*)(atuiargs const* atui_args)) atuifunc;

// purely to satisfy the args of the atui branch generation functions if no
// atomtree struct is relevant for that branch:
typedef struct atui_nullstruct {} atui_nullstruct;

// GObject/GTK stuff.
typedef struct _GATUILeaf GATUILeaf;
typedef struct _GATUIBranch GATUIBranch;

#endif
