#include "yaabe_gtk_internal.h"

constexpr char basic_config_file[] = {
#embed "yaabe.conf"
};

struct yaabe_config {
	GFile* file;
	GKeyFile* conf;
};
inline static void
free_yaabe_config(
		struct yaabe_config* const conf
		) {
	g_key_file_unref(conf->conf);
	g_object_unref(conf->file);
}


GFile*
get_yaabe_config_dir(
		GError** const ferror_out
		) {
	char const* const yaabe_dir_path[] = { // $XDG_CONFIG_HOME/yaabe/
		g_get_user_config_dir(), "yaabe",
		NULL
	};

	GFile* const yaabe_dir = g_file_new_build_filenamev(yaabe_dir_path);
	GFileType const ftype = g_file_query_file_type(
		yaabe_dir, G_FILE_QUERY_INFO_NONE, NULL
	);
	if (G_FILE_TYPE_DIRECTORY != ftype) {
		g_file_make_directory_with_parents(yaabe_dir, NULL, ferror_out);
	}

	return yaabe_dir;
}

static GFile*
get_yaabe_config_file(
		GError** const ferror_out
		) {
	GError* err = NULL;
	GFile* conffile = NULL;

	GFile* const yaabe_dir = get_yaabe_config_dir(&err);
	if (err) {
		goto yaabe_dir_err;
	}

	char const* const yaabe_conf_path[] = { // $XDG_CONFIG_HOME/yaabe/yaabe.conf
		g_file_peek_path(yaabe_dir), "yaabe.conf",
		NULL
	};
	conffile = g_file_new_build_filenamev(yaabe_conf_path);

	yaabe_dir_err:
	g_object_unref(yaabe_dir);

	*ferror_out = err;
	return conffile;
}

static void
get_yaabe_config(
		struct yaabe_config* const conf,
		GError** const ferror_out
		) {
	// gf_out, kf_out, ferror_out are all required.
	// gf_out and kf_out may be set with bogus data if there's an error.

	GError* err = NULL;

	conf->file = get_yaabe_config_file(&err);
	if (err) {
		goto exit;
	}
	conf->conf = g_key_file_new();

	bool const kf_success = g_key_file_load_from_file(
		conf->conf, g_file_peek_path(conf->file),
		(G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS),
		NULL // not necessary
	);
	if (kf_success) {
		goto exit;
	}

	GFileType const ftype = g_file_query_file_type(
		conf->file, G_FILE_QUERY_INFO_NONE, NULL
	);
	if ((G_FILE_TYPE_UNKNOWN != ftype) && (G_FILE_TYPE_REGULAR != ftype)) {
		goto exit;
	}
	// file does not exist, or fails parse. Create a new config.

	g_key_file_load_from_data(
		conf->conf, basic_config_file, lengthof(basic_config_file)-1,
		(G_KEY_FILE_KEEP_COMMENTS|G_KEY_FILE_KEEP_TRANSLATIONS),
		&err
	);

	exit:
	*ferror_out = err;
}
static void
write_config_file(
		struct yaabe_config* const conf,
		GError** const ferror_out
		) {
	size_t num_bytes;
	char* const conf_data = g_key_file_to_data(conf->conf, &num_bytes, NULL);
	g_file_replace_contents(
		conf->file, conf_data, num_bytes,
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

	GError* err = NULL;
	struct yaabe_config conf = {};
	get_yaabe_config(&conf, &err);
	if (err) {
		g_error_free(err);
		return working_dir;
	}

	char* dir_path;
	if (working_dir) { // merge old history into conf
		dir_path = g_file_get_path(working_dir);
		g_key_file_set_string(conf.conf, "history", "cwd", dir_path);
		write_config_file(&conf, NULL);
	} else {
		dir_path = g_key_file_get_string(conf.conf, "history", "cwd", NULL);
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
	free_yaabe_config(&conf);
	return working_dir;
}
void
set_cached_working_dir(
		GFile* const biosfile
		) {
	GError* err = NULL;
	struct yaabe_config conf = {};
	get_yaabe_config(&conf, &err);
	if (err) {
		g_error_free(err);
		return;
	}
	GFile* const parent_dir = g_file_get_parent(biosfile);
	char* const parent_dir_path = g_file_get_path(parent_dir);
	g_object_unref(parent_dir);
	if (NULL == parent_dir_path) {
		return;
	}

	g_key_file_set_string(conf.conf, "history", "cwd", parent_dir_path);
	write_config_file(&conf, NULL);

	free(parent_dir_path);
	free_yaabe_config(&conf);
}


void
set_cached_scroll_path(
		char const* path
		) {
	GError* err = NULL;
	struct yaabe_config conf = {};
	get_yaabe_config(&conf, &err);
	if (err) {
		g_error_free(err);
		return;
	}

	g_key_file_set_string(conf.conf, "history", "path", path);
	write_config_file(&conf, NULL);

	free_yaabe_config(&conf);
}

char*
get_cached_scroll_path(
		) {
	GError* err = NULL;
	struct yaabe_config conf = {};
	get_yaabe_config(&conf, &err);
	if (err) {
		g_error_free(err);
		return NULL;
	}

	char* const path = g_key_file_get_string(conf.conf, "history","path", NULL);
	free_yaabe_config(&conf);
	return path;
}

bool
get_big_endianness(
		) {
	GError* err = NULL;
	struct yaabe_config conf = {};
	get_yaabe_config(&conf, &err);
	if (err) {
		g_error_free(err);
		return NULL;
	}

	bool big_endian;
	big_endian = g_key_file_get_boolean(conf.conf, "main", "big_endian", &err);

	if (err) { // does not exist
		g_error_free(err);
		big_endian = false;
		g_key_file_set_boolean(conf.conf, "main", "big_endian", big_endian);
		write_config_file(&conf, NULL);
	}

	free_yaabe_config(&conf);
	return big_endian;
}
