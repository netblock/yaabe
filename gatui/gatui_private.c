#include "standard.h"
#include <zlib.h> 
#include "gatui_private.h"

union b64_header_raw {
	void* raw;
	struct b64_header* header;
};

char*
b64_packet_encode(
		struct b64_header const* const config,
		void const* const payload
		) {
	size_t const packet_size = sizeof(struct b64_header) + config->num_bytes;
	union b64_header_raw const h = {.header = cralloc(packet_size)};

	memcpy(h.header, config, sizeof_flex(config, bytes, 0));
	memcpy(h.header->bytes, payload, config->num_bytes);
	h.header->crc = crc32(
		0,
		(h.raw + sizeof(h.header->crc)), // exclude crc
		(packet_size - sizeof(h.header->crc))
	);

	gchar* const b64_text = g_base64_encode(h.raw, packet_size);
	free(h.header);
	return b64_text;
}

struct b64_header*
b64_packet_decode(
		char const* const b64_text
		) {
	size_t b64_num_bytes = 0;
	union b64_header_raw const h = {
		.raw = g_base64_decode(b64_text, &b64_num_bytes)
	};

	if (0 == b64_num_bytes) {
		goto error_exit;
	}
	if (b64_num_bytes < sizeof(*h.header)) {
		goto error_exit;
	}
	if (b64_num_bytes < (h.header->num_bytes + sizeof(*h.header))) {
		goto error_exit;
	}
	uint32_t const crc = crc32(
		0,
		(h.raw + sizeof(h.header->crc)),
		(sizeof(*h.header)-sizeof(h.header->crc)  +  h.header->num_bytes)
	);
	if (crc != h.header->crc) {
		goto error_exit;
	}

	if (B64_HEADER_VER_CURRENT != h.header->version) {
		goto error_exit;
	}

	if (GATUI_TYPESTR_LEN <= strnlen(h.header->typestr, GATUI_TYPESTR_LEN)) {
		goto error_exit;
	}

	// strict compliance
	if ((B64_BRANCH_CONTIGUOUS == h.header->target)
			&& (1 != h.header->num_segments)
			) {
		goto error_exit;
	}
	if ((B64_LEAF==h.header->target) && (1!=h.header->num_segments)) {
		goto error_exit;
	}

	return h.header;

	error_exit:
	free(h.header);
	return NULL;
}
