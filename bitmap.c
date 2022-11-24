#include <stdio.h>
#include <stdint.h>
#include <byteswap.h> /* __bswap_XX  */
#include <stdlib.h>   /* rand, srand */
#include <time.h>     /* time        */

#include "inc/bitmap.h"


static int  creaCabeceras(FILE *, uint16_t);
static void simetriaHor(FILE*, uint16_t, rgbpxl *, rgbpxl *);

int leeCabeceras(FILE *bmp) {
	int ret = 0;
	bmpFileHdr filehdr;
	bmpInfoHdr infohdr;

	fread(&filehdr, sizeof(bmpFileHdr), 1, bmp);
	fread(&infohdr, sizeof(bmpInfoHdr), 1, bmp);

	if (compruebaCabeceras(&filehdr, &infohdr) != 0) {
		ret = 1;
	}
	else {
		imprimeCabeceras(&filehdr, &infohdr);
	}

	return ret;
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

void imprimeCabeceras(bmpFileHdr *f, bmpInfoHdr *i) {
	printf(" === FILE HEADER ===\n");
	printf("bfType:      0x%04X\n", __bswap_16(f->bfType));
	printf("bfSize:      0x%08X ", f->bfSize);
		printf("[%d]\n", f->bfSize);
	printf("bfReserved1: 0x%04X\n", f->bfReserved1);
	printf("bfReserved2: 0x%04X\n", f->bfReserved2);
	printf("bfOffBits:   0x%08X ", f->bfOffBits);
		printf("[%d]\n", f->bfOffBits);

	printf(" === INFO HEADER ===\n");
	printf("biSize:          0x%08X ", i->biSize);
		printf("[%d]\n", i->biSize);
	printf("biWidth:         0x%08X ", i->biWidth);
		printf("[%d]\n", i->biWidth);
	printf("biHeight:        0x%08X ", i->biHeight);
		printf("[%d]\n", i->biHeight);
	printf("biPlanes:        0x%04X ", i->biPlanes);
		printf("[%d]\n", i->biPlanes);
	printf("biBitCount:      0x%04X ", i->biBitCount);
		printf("[%d]\n", i->biBitCount);
	printf("biCompression:   0x%08X\n", i->biCompression);
	printf("biSizeImage:     0x%08X ", i->biSizeImage);
		printf("[%d]\n", i->biSizeImage);
	printf("biXPelsPerMeter: 0x%08X ", i->biXPelsPerMeter);
		printf("[%d]\n", i->biXPelsPerMeter);
	printf("biYPelsPerMeter: 0x%08X ", i->biYPelsPerMeter);
		printf("[%d]\n", i->biYPelsPerMeter);
	printf("biClrUsed:       0x%08X\n", i->biClrUsed);
	printf("biClrImportant:  0x%08X\n", i->biClrImportant);
}

int creaAvatar(uint16_t lado, simetria sim) {
	int ret = 0;
	FILE *bmp;
	/* ancho y alto por ahora van a ser siempre 8 así que por ahora no hago
	 * comprobaciones sobre la validez de las dimensiones introducidas */
	rgbpxl fondo = {0x00, 0xFF, 0x00};
	rgbpxl linea = {0xFF, 0x00, 0x00};


	bmp = fopen(AVATARFN, "w");
	if (bmp == NULL) {
		perror("Error creando la imagen:");
		return -1;
	}

	if (creaCabeceras(bmp, lado) != 0) {
		return -1;
	}

	switch (sim) {
	case HORIZONTAL:
		simetriaHor(bmp, lado, &fondo, &linea);
		break;
	case VERTICAL:
		break;
	case CUARTOS:
		break;
	default:
		break;
	}

	fclose(bmp);

	return ret;
}

int creaCabeceras(FILE *bmp, uint16_t lado) {
	int ret = 0;
	bmpFileHdr filehdr;
	bmpInfoHdr infohdr;
	int tammapapixel;

	tammapapixel = ((BIBITCOUNT/8) * lado * lado);

	filehdr.bfType      = BFTYPE;
	filehdr.bfSize      = BFSIZE + BISIZE + tammapapixel;
	filehdr.bfReserved1 = BFRESERVED1;
	filehdr.bfReserved2 = BFRESERVED2;
	filehdr.bfOffBits   = BFOFFBITS;

	infohdr.biSize          = BISIZE;
	infohdr.biWidth         = lado;
	infohdr.biHeight        = -lado;
	infohdr.biPlanes        = BIPLANES;
	infohdr.biBitCount      = BIBITCOUNT;
	infohdr.biCompression   = BICOMPRESSION;
	infohdr.biSizeImage     = tammapapixel;
	infohdr.biXPelsPerMeter = BIXPELSPM;
	infohdr.biYPelsPerMeter = BIYPELSPM;
	infohdr.biClrUsed       = BICLRUSED;
	infohdr.biClrImportant  = BICLRIMPORTANT;

	if (fwrite(&filehdr, sizeof(bmpFileHdr), 1, bmp) == 0) {
		printf("Error escribiendo cabecera FILE.\n");
		ret = -1;
	}
	else if (fwrite(&infohdr, sizeof(bmpInfoHdr), 1, bmp) == 0) {
		printf("Error escribiendo cabecera INFO.\n");
		ret = -2;
	}

	return ret;
}

void simetriaHor(FILE* bmp, uint16_t lado, rgbpxl *fondo, rgbpxl *linea) {
	uint16_t ancho = lado; /* por claridad */
	uint16_t alto  = lado / 2;
	int i, j;
	uint8_t aux[alto][ancho];

	srand(time(NULL));

	/* Paso 1: recorrer la mitad superior de la imagen */
	for (i = 0; i < alto; i++) {
		for (j = 0; j < ancho; j++) {
			if (rand() % 4 == 0) {
				aux[i][j] = 1;
				fwrite(linea, sizeof(rgbpxl), 1, bmp);
			}
			else {
				aux[i][j] = 0;
				fwrite(fondo, sizeof(rgbpxl), 1, bmp);
			}
		}
	}

	/* Paso 2: recorrer la mitad inferior de la imagen */
	for (i = alto -1; i >= 0; i--) {
		for (j = 0; j < ancho; j++) {
			if (aux[i][j]) {
				fwrite(linea, sizeof(rgbpxl), 1, bmp);
			}
			else {
				fwrite(fondo, sizeof(rgbpxl), 1, bmp);
			}
		}
	}
}
