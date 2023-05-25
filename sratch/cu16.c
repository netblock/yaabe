#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ATOM_ROM_TABLE_PTR    0x48
#define ATOM_ROM_MAGIC_PTR    4
#define ATOM_ROM_MAGIC        "ATOM"
#define ATOM_ROM_MAGIC_LEN    4

struct atombios {
	uint8_t stuff[0x48];
	uint16_t atomrom_table_ptr;
};
struct atombios_rom_table {
	char magicbytes[12];
};

int main(){
	FILE* tm = fopen("timemod217.rom", "r");
	fseek(tm,0,SEEK_END);
	long size = ftell(tm);
	fseek(tm,0,SEEK_SET);
	void* bios = malloc(size);
	fread(bios,size,1,tm);
	fclose(tm);

	uint16_t* cu16 = bios;
	uint8_t* cu8 = bios;
	char* cstr = bios;
	uint16_t* cu16_2 = bios+1;

	//xxd: 00000000: 55aa 74e9 3303 0000 0000 0000 0000 0000
	printf("%X %X\n", *cu16, *cu8); //AA55 55 
	printf("%X %X\n", cu16[0], cu16[1]); //AA55 E974
	printf("%X %X\n", *(cu16+0), *cu16_2); //AA55 74AA

	// we don't know where it is, but we can find out. Read ptr and use it.
	uint16_t* atom_rom_table = bios + *(uint16_t*)(bios+ATOM_ROM_TABLE_PTR);
	cstr = (char*)(atom_rom_table) + ATOM_ROM_MAGIC_PTR;
	if (strncmp(cstr, ATOM_ROM_MAGIC, ATOM_ROM_MAGIC_LEN) == 0)
		printf("go 1: %c%c%c%c\n", cstr[0],cstr[1],cstr[2],cstr[3]);

	struct atombios* abios = bios;
	struct atombios_rom_table* rt = (void*)abios + abios->atomrom_table_ptr;
	if (strncmp(rt->magicbytes+4, ATOM_ROM_MAGIC, ATOM_ROM_MAGIC_LEN) == 0)
		printf("go 2: %c%c%c%c\n", cstr[0],cstr[1],cstr[2],cstr[3]);

	free(bios);
}
