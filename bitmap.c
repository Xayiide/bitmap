#include <stdio.h>
#include <stdint.h>

#include "inc/bitmap.h"

int compruebaCabeceras_(FILE *bmp) {
	/* TODO */
	return 0;
}

int compruebaCabeceras(bmpFileHdr *f, bmpInfoHdr *i) {
	int ret = 0;

	if (f->bfType != BFTYPE || f->bfOffBits != BFOFFBITS ||
		i->biSize != BISIZE || i->biBitCount != BIBITCOUNT ||
		i->biCompression != BICOMPRESSION) {
		ret = 1;
	}

	return ret;
}

void procesaCabeceras(bmpFileHdr *f, bmpInfoHdr *i) {
	/* TODO: Dar la vuelta a la endianess */
	printf(" === FILE HEADER ===\n");
	printf("bfType:      0x%04X\n", f->bfType);
	printf("bfSize:      0x%08X\n", f->bfSize);
	printf("bfReserved1: 0x%04X\n", f->bfReserved1);
	printf("bfReserved2: 0x%04X\n", f->bfReserved2);
	printf("bfOffBits:   0x%08X\n", f->bfOffBits);

	printf(" === INFO HEADER ===\n");
}
