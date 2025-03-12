/*
gatui is a GObject-based wrapper to atui. Start at gatui_trunk.
Since it's GObject, there is thread-safe reference counting.
However bios-data IO is not thread-safe (spinlock? mode-based lock?).
*/

#ifndef GATUI_H
#define GATUI_H

#include "atui.h"

typedef struct _GATUILeaf GATUILeaf;
typedef struct _GATUIBranch GATUIBranch;
typedef struct _GATUITree GATUITree;

#include "gatui_branch.h"
#include "gatui_leaf.h"
#include "gatui_tree.h"

#endif
