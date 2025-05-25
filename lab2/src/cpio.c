#include "cpio.h"
#include "mini_uart.h"
#include "shell.h"
#include "utils.h"
#include <stdint.h>

// CPIO file
// [header][pathname][pathname padding][file][file padding]


unsigned int hex2int(char *s, int len) {
	unsigned int ret = 0;
	for(int i = 0; i < len; i++) {
		char c = s[i];
		ret <<= 4; // hexadecimal
		if(c >= '0' && c <= '9') ret += c -'0';
		else if(c >= 'a' && c <= 'z') ret += c - 'a' + 10;
		else if(c >= 'A' && c <= 'Z') ret += c - 'A' + 10;
	}
	return ret;
}

void cpio_ls() {
	uint8_t *addr = (uint8_t *) CPIO_BASE; // start from 0x20000000
	while(1) {
		cpio_header *hdr = (cpio_header *) addr; // cast into cpio_header type
		if(strncmp((char *) hdr->c_magic, "070701", 6) != 0)
			break; // check magic number correct or not
		

		// claculate next file offset
		unsigned int namesize = hex2int(hdr->c_namesize, 8); 
		unsigned int filesize = hex2int(hdr->c_filesize, 8); 
		char *name = (char*)(addr + HEADER_SIZE);
		
		if(strncmp(name, "TRAILER!!!", 10) == 0)
			break; // end of CPIO

		// output filename
		for(int i = 0; i < namesize - 1; i++) {
			uart_send(name[i]);
		}
		uart_sendstr("\n");
	
		// file_start = header + namesize
		uint8_t *file_start = (uint8_t *) ALIGN4((uintptr_t)(name + namesize));
		addr = (uint8_t *) ALIGN4((uintptr_t) (file_start + filesize));
	}
}

void cpio_cat() {
	// read file name
	uart_sendstr("Filename: ");
	char buffer[256];
	read_command(buffer);

	// cheack file
	uint8_t *addr = (uint8_t *) CPIO_BASE; // start from 0x20000000
	while(1) {
		cpio_header *hdr = (cpio_header *) addr;
		if(strncmp((char *) hdr->c_magic, "070701", 6) != 0)
			break;

		unsigned int namesize = hex2int(hdr->c_namesize, 8); 
		unsigned int filesize = hex2int(hdr->c_filesize, 8); 
		char *name = (char*)(addr + HEADER_SIZE);
		
		if(strncmp(name, "TRAILER!!!", 10) == 0)
			break; // end of CPIO
		
		// output file content
		if(strncmp(name, buffer, namesize) == 0) {
			char *file_start = (char *)ALIGN4((uintptr_t)(name + namesize));
			for(int i = 0; i < filesize - 1; i++) {
				uart_send(file_start[i]);
			}
			uart_sendstr("\n");
			return;
		}

		// file_start = header + namesize
		uint8_t *file_start = (uint8_t *) ALIGN4((uintptr_t)(name + namesize));
		addr = (uint8_t *) ALIGN4((uintptr_t) (file_start + filesize));
	}
	// file not found
	uart_sendstr("file not find : (\n");
}

