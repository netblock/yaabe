/*
gatui is a GObject-based wrapper to atui. Start at gatui_trunk.
Since it's GObject, there is thread-safe reference counting.
However bios-data IO is not thread-safe (spinlock? mode-based lock?).
*/

#ifndef GATUI_H
#define GATUI_H
G_BEGIN_DECLS

#include "atui.h"

typedef struct _GATUINode GATUINode;
typedef struct _GATUILeaf GATUILeaf;
typedef struct _GATUIBranch GATUIBranch;
typedef struct _GATUITree GATUITree;
typedef struct _GATUIRegexNode GATUIRegexNode;
typedef struct _GATUIRegexTree GATUIRegexTree;

#include "gatui_node.h"
#include "gatui_branch.h"
#include "gatui_leaf.h"
#include "gatui_regex.h"
#include "gatui_tree.h"

G_END_DECLS
#endif
