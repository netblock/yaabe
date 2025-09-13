#include "yaabe_gtk_internal.h"

// TODO do the #embed thing when GCC 15 comes out
static constexpr char basic_config_file[] = (
"# syntax is described in:\n"
"# https://freedesktop.org/wiki/Specifications/desktop-entry-spec/\n"
"# https://docs.gtk.org/glib/struct.KeyFile.html\n"
"\n"
"[main]\n"
"config_version=1\n"
"\n"
"[history]\n"
"# cwd is the last saved-to directory\n"
"cwd=\n"
"# path is about restoring the scroll position,"
" based on the last selected structure path\n"
"path=\n"
);

static void
get_config_file(
		GFile** const gf_out,
		GKeyFile** const kf_out,
		GError** const ferror_out
		) {
	// gf_out, kf_out, ferror_out are all required.
	// gf_out and kf_out may be set with bogus data if there's an error.

	const char* const xdg_home = g_get_user_config_dir(); // XDG_CONFIG_HOME
	GFileType ftype;
	GError* err = NULL;

	// $XDG_CONFIG_HOME/yaabe/
	GPathBuf yaabe_dir_builder;
	g_path_buf_init_from_path(&yaabe_dir_builder, xdg_home);
	g_path_buf_push(&yaabe_dir_builder, "yaabe");
	char* yaabe_dir_path = g_path_buf_to_path(&yaabe_dir_builder);

	GFile* const yaabe_dir = g_file_new_for_path(yaabe_dir_path);
	ftype = g_file_query_file_type(yaabe_dir, G_FILE_QUERY_INFO_NONE, NULL);
	if (G_FILE_TYPE_DIRECTORY != ftype) {
		g_file_make_directory_with_parents(yaabe_dir, NULL, &err);
		if (err) {
			goto yaabe_dir_err;
		}
	}

	// $XDG_CONFIG_HOME/yaabe/yaabe.conf
	GPathBuf config_file_builder;
	g_path_buf_init_from_path(&config_file_builder, xdg_home);
	g_path_buf_push(&config_file_builder, "yaabe/yaabe.conf");
	char* const config_file_path = g_path_buf_to_path(&config_file_builder);

	GFile* const conffile = g_file_new_for_path(config_file_path);
	GKeyFile* const conf = g_key_file_new();
	*gf_out = conffile;
	*kf_out = conf;

	bool const kf_success = g_key_file_load_from_file(
		conf, config_file_path,
		(G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS),
		NULL // not necessary
	);
	if (kf_success) {
		goto all_success;
	}

	ftype = g_file_query_file_type(conffile, G_FILE_QUERY_INFO_NONE, NULL);
	if ((G_FILE_TYPE_UNKNOWN != ftype) && (G_FILE_TYPE_REGULAR != ftype)) {
		goto conffile_err;
	}
	// file does not exist, or fails parse. Create a new config.

	g_key_file_load_from_data(
		conf, basic_config_file, lengthof(basic_config_file)-1,
		(G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS),
		&err
	);
	if (NULL == err) {
		goto all_success;
	}

	conffile_err:
	g_key_file_unref(conf);
	g_object_unref(conffile);

	all_success:
	free(config_file_path);
	g_path_buf_clear(&config_file_builder);

	yaabe_dir_err:
	g_object_unref(yaabe_dir);
	free(yaabe_dir_path);
	g_path_buf_clear(&yaabe_dir_builder);

	*ferror_out = err;
}
static void
write_config_file(
		GFile* const conffile,
		GKeyFile* const conf,
		GError** const ferror_out
		) {
	size_t num_bytes;
	char* const conf_data = g_key_file_to_data(conf, &num_bytes, NULL);
	g_file_replace_contents(
		conffile, conf_data, num_bytes,
		NULL, false, G_FILE_CREATE_NONE, NULL,NULL, ferror_out
	);
	free(conf_data);
}

static inline GFile*
get_cached_working_dir_old( // TODO delete eventually
		) {
	const char* const xdg_home = g_get_user_config_dir(); // XDG_CONFIG_HOME
	GFile* cached_history_path = NULL;
	GFileType ftype;

	// $XDG_CONFIG_HOME/yaabe/history
	GPathBuf history_file_builder;
	g_path_buf_init_from_path(&history_file_builder, xdg_home);
	g_path_buf_push(&history_file_builder, "yaabe/history");
	char* history_file_path = g_path_buf_to_path(&history_file_builder);
	GFile* const history_file = g_file_new_for_path(history_file_path);
	ftype = g_file_query_file_type(history_file, G_FILE_QUERY_INFO_NONE, NULL);
	if (G_FILE_TYPE_REGULAR != ftype) {
		goto history_file_err;
	}

	// read
	char* history_contents;
	size_t filesize;
	bool const read_success = g_file_load_contents(
		history_file,   NULL,
		&history_contents,  &filesize,
		NULL, NULL
	);
	if (!read_success) {
		goto history_file_err;
	}
	g_file_delete(history_file, NULL, NULL); // !!! XXX !!!

	// chop off trailing \n and check if contents points to a dir
	char* save;
	cached_history_path = g_file_new_for_path(
		strtok_r(history_contents, "\n\r", &save)
	);
	ftype = g_file_query_file_type(
		cached_history_path, G_FILE_QUERY_INFO_NONE, NULL
	);
	if (G_FILE_TYPE_DIRECTORY != ftype) {
		g_object_unref(cached_history_path);
		cached_history_path = NULL;
	}

	free(history_contents);

	history_file_err:
	g_object_unref(history_file);
	free(history_file_path);
	g_path_buf_clear(&history_file_builder);

	return cached_history_path;
}
GFile*
get_cached_working_dir(
		) {
	GFile* working_dir = get_cached_working_dir_old();

	GFile* conffile;
	GKeyFile* conf;
	GError* error = NULL;
	get_config_file(&conffile, &conf, &error);
	if (error) {
		g_error_free(error);
		return working_dir;
	}

	char* dir_path;
	if (working_dir) { // merge old history into config
		dir_path = g_file_get_path(working_dir);
		g_key_file_set_string(conf, "history", "cwd", dir_path);
		write_config_file(conffile, conf, NULL);
	} else {
		dir_path = g_key_file_get_string(conf, "history", "cwd", NULL);
		if (dir_path) {
			working_dir = g_file_new_for_path(dir_path);
			GFileType const ftype = g_file_query_file_type(
				working_dir, G_FILE_QUERY_INFO_NONE, NULL
			);
			if (G_FILE_TYPE_DIRECTORY != ftype) {
				g_object_unref(working_dir);
				working_dir = NULL;
			}
		}
	}

	free(dir_path);
	g_key_file_unref(conf);
	g_object_unref(conffile);
	return working_dir;
}
void
set_cached_working_dir(
		GFile* const biosfile
		) {
	GFile* conffile;
	GKeyFile* conf;
	GError* error = NULL;
	get_config_file(&conffile, &conf, &error);
	if (error) {
		g_error_free(error);
		return;
	}
	GFile* const parent_dir = g_file_get_parent(biosfile);
	char* const parent_dir_path = g_file_get_path(parent_dir);
	g_object_unref(parent_dir);
	if (NULL == parent_dir_path) {
		return;
	}

	g_key_file_set_string(conf, "history", "cwd", parent_dir_path);
	write_config_file(conffile, conf, NULL);

	free(parent_dir_path);
	g_key_file_unref(conf);
	g_object_unref(conffile);
}


void
set_cached_scroll_path(
		char const* path
		) {
	GFile* conffile;
	GKeyFile* conf;
	GError* error = NULL;
	get_config_file(&conffile, &conf, &error);
	if (error) {
		g_error_free(error);
		return;
	}

	g_key_file_set_string(conf, "history", "path", path);
	write_config_file(conffile, conf, NULL);

	g_key_file_unref(conf);
	g_object_unref(conffile);
}

char*
get_cached_scroll_path(
		) {
	GFile* conffile;
	GKeyFile* conf;
	GError* error = NULL;
	get_config_file(&conffile, &conf, &error);
	if (error) {
		g_error_free(error);
		return NULL;
	}

	char* const path = g_key_file_get_string(conf, "history", "path", NULL);

	g_key_file_unref(conf);
	g_object_unref(conffile);

	return path;
}
