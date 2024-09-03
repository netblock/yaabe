#ifndef GATUI_TREE_H
#define GATUI_TREE_H

G_BEGIN_DECLS

#define GATUI_TYPE_TREE gatui_tree_get_type()
G_DECLARE_FINAL_TYPE(GATUITree, gatui_tree, GATUI, TREE, GObject)


GATUITree*
gatui_tree_new_from_path(
		char const* path,
		GError** ferror_out
		);
GATUITree*
gatui_tree_new_from_gfile(
		GFile* biosfile,
		GError** ferror_out
		);
void
gatui_tree_save(
		GATUITree* self,
		GError** ferror_out
		);
void
gatui_tree_saveas(
		GATUITree* self,
		GFile* biosfile,
		GError** ferror_out
		);
GFile*
gatui_tree_get_bios_file(
		GATUITree* self
		);


GATUIBranch*
gatui_tree_get_trunk(
		GATUITree* self
		);


// creates a new tree based off of the raw bios data buffer, and GFile.
// useful when a new atomtree crawl is wanted.
GATUITree*
gatui_tree_copy_core(
		GATUITree* src
		);


struct atom_tree*
gatui_tree_get_atom_tree(
		GATUITree* self
		);

G_END_DECLS
#endif
