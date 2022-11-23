#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <stdio.h>
#include <stdint.h> /* uints */

#define AVATARFN "avatar.bmp"

#define BFTYPE        0x4D42
#define BFOFFBITS     54
#define BISIZE        40
#define BIBITCOUNT    24
#define BICOMPRESSION 0

/* FILE HEADER: 14 bytes */
typedef struct {
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
} __attribute__((__packed__)) bmpFileHdr;

/* INFO HEADER: 40 bytes */
typedef struct {
	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} __attribute__((__packed__)) bmpInfoHdr;

typedef struct {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} rgbpxl;

int compruebaCabeceras_(FILE *);

int compruebaCabeceras(bmpFileHdr *, bmpInfoHdr *);
void procesaCabeceras(bmpFileHdr *, bmpInfoHdr *);

#endif
