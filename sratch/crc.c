//cc crc.c -lz -lpthread -std=c2x -march=native -O3 -o crcbrute  && ./crcbrute ./6950XT.16384.220310.rom

#include <stdint.h>
#include <uchar.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h> // don't forget to -lz in LDFLAGS
#include <pthread.h>

//#include "../amd/atomfirmware.h"
#pragma pack(push, 1)
struct atombios_image {
	uint16_t atombios_magic; // little endian: 0xAA55
	uint8_t image_size; //0x02
	uint8_t rsvd0[30];
	uint8_t checksum; // 0x21
	uint8_t rsvd1[13];
	uint8_t number_of_strings; // 0x2F
	uint8_t atomati_magic[11]; // 0x30; " 761295520" There is a space.
	uint8_t rsvd2[13];
	uint16_t bios_header; // 0x48
	uint8_t rsvd3[6];
	uint8_t bios_date[15]; // 0x50
	uint8_t rsvd4[15];
	uint16_t atombios_strings_offset; // 0x6E 
	uint8_t rsvd5[16];
	uint8_t part_number_offset; // 0x80 ; only use if number_of_strings == 0
	uint8_t rsvd6[19];
	uint8_t asic_bus_mem_type_offset; // 0x94; I think it's a 20-byte str
};
struct atom_rom_header_v2_2 {
	uint32_t header;
	//struct atom_common_table_header table_header;
	uint8_t  atom_bios_string[4]; // enum atom_string_def atom_bios_string. Signature to distinguish between Atombios and non-atombios,
	uint16_t bios_segment_address;
	uint16_t protectedmodeoffset;
	uint16_t configfilenameoffset;
	uint16_t crc_block_offset;
	uint16_t vbios_bootupmessageoffset;
	uint16_t int10_offset;
	uint16_t pcibusdevinitcode;
	uint16_t iobaseaddress;
	uint16_t subsystem_vendor_id;
	uint16_t subsystem_id;
	uint16_t pci_info_offset;
	uint16_t masterhwfunction_offset; // Offest for SW to get all command function offsets, Don't change the position
	uint16_t masterdatatable_offset;  // Offest for SW to get all data table offsets, Don't change the position
	uint16_t reserved;
	uint32_t pspdirtableoffset;
};
#pragma pack(pop)


inline static int8_t getfile(char8_t* f, void** bios, uint32_t* size){
    FILE* tm = fopen(f, "r");
	if (tm == NULL)
		return 1;
	fseek(tm,0,SEEK_END);
	*size = ftell(tm);
	fseek(tm,0,SEEK_SET);
	*bios = malloc(*size);
	fread(*bios,*size,1,tm);
	fclose(tm);
	return 0;
}
inline static void* bios_fastforward(void* memory, uint32_t size) {
	// The dumped bios probably doesn't start with where atombios actually
	// begins. Go though the allocated memory to find the first magic bytes.
	uint16_t* bios = memory;
	uint16_t* end = memory+size;
	for(; bios < end; bios++) {
		if (*bios == 0xAA55)
			return (void*)bios;
	}
	return NULL;
}

struct job_detail2 {
	void* bios;
	uint32_t oldcrc;
	uint32_t end;

	uint8_t wegood;
	uint32_t good_start;
};

void* crc_cruncher2(void* detail_ptr) {
	struct job_detail2* detail = detail_ptr;
	void* bios = (void*) detail->bios;
	const uint32_t end = detail->end;
	uint32_t newcrc;
	uint32_t i = 0;

	for(; i < end; i++) {
		newcrc = crc32(0, bios+i, end-i);
		if (newcrc == detail->oldcrc) {
			goto wegood;
		}
	}

	//printf("nope %u\n", detail->end);
	
	return NULL;

	wegood:
	detail->wegood = 1;
	detail->good_start = i;
	
	printf("address: +0x%X ~ +0x%X for %u bytes\n", i, end, end-i);
	printf("crc: 0x%X 0x%X\n\n", detail->oldcrc, crc32(0, bios+i, end-i));
	return NULL;
}
int main(int argc, char8_t** argv) {
	void* oldbios = NULL;
	uint32_t oldsize = 0;
	getfile(argv[1], &oldbios, &oldsize);
	void* bios = bios_fastforward(oldbios, oldsize);
	uint32_t size = oldsize - (bios-oldbios);
	printf("ffwd %u bytes.\n", bios-oldbios);
	printf("%u bytes\n", size);

	struct atombios_image* image = bios;
	struct atom_rom_header_v2_2* rom_header = bios + image->bios_header;
	printf("\"ATOM\" magic: %c%c%c%c\n",
		rom_header->atom_bios_string[0],
		rom_header->atom_bios_string[1],
		rom_header->atom_bios_string[2],
		rom_header->atom_bios_string[3]
	);
	uint32_t* romcrc = bios + rom_header->crc_block_offset;
	uint32_t oldcrc = *(romcrc);
	printf("oldcrc: 0x%X\n", oldcrc);
	//*(romcrc) = 0;

	/*
	t 5         . 5
	r 4       . . 4
	a 3     . . . 3
	t 2   . . . . 2
	s 1 . . . . . 1
	    1 2 3 4 5
	    end
	*/

	struct job_detail2* details = malloc(size * sizeof(struct job_detail2));
	pthread_t* threads = malloc(size * sizeof(pthread_t));
	uint32_t i = 0;
	for(; i < size; i++) {
		details[i].bios = bios;
		details[i].oldcrc = oldcrc;
		details[i].end = i;
		details[i].wegood = 0;
		details[i].good_start = 0;
		
	}
	printf("start\n\n");
	for(i=0; i < size; i++) {
		//printf("spawn %u\n",i);
		pthread_create(threads+i, NULL, crc_cruncher2, (void*)(&(details[i])));
	}
	printf("spawn %u\n",i);
	for(i=0; i < size; i++) {
		//printf("collapse %u\n", i);
		pthread_join(threads[i], NULL);
	}
	printf("return %u\n\n\n",i);
	for(i=0; i < size; i++) {
		if (details[i].wegood) {
			
			printf("address: +0x%X ~ +0x%X for %u bytes\n", details[i].good_start, details[i].end, details[i].end - details[i].good_start);
			printf("crc: 0x%X 0x%X\n", oldcrc, crc32(0, bios+details[i].good_start, details[i].end - details[i].good_start));
		}
	}
	printf("endofgood %u\n", i);

	return 0;
}
