// opaque definitions

#ifndef ATUI_TYPES_H
#define ATUI_TYPES_H

struct atom_tree;

typedef struct _atui_node atui_node;

typedef struct atui_func_args atuiargs;
typedef typeof(atui_node* (*)(atuiargs const*)) atuifunc;

// purely to satisfy the args of the atui branch generation functions if no
// atomtree struct is relevant for that branch:
typedef struct atui_nullstruct {} atui_nullstruct;

// GObject/GTK stuff.
typedef struct _GATUINode GATUINode;
typedef struct _GATUILeaf GATUILeaf;
typedef struct _GATUIBranch GATUIBranch;
typedef struct _GATUITree GATUITree;

#endif
