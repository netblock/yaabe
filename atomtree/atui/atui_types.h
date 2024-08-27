#ifndef ATUI_TYPES_H
#define ATUI_TYPES_H

typedef struct _atui_branch atui_branch;
typedef struct _atui_leaf atui_leaf;

struct atui_funcify_args;
typedef atui_branch* (* atuifunc)(struct atui_funcify_args const*);

// GObject/GTK stuff.
typedef struct _GATUILeaf GATUILeaf;
typedef struct _GATUIBranch GATUIBranch;

#endif
