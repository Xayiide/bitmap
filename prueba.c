#include <stdio.h>
#include <stdint.h>
//#include <errno.h>   /* errno    */
#include <string.h>  /* strerror */

#include "inc/bitmap.h"

#define TAM_MAX 256
#define NUM_OPC 2


void menu(void);
int  leeIntRango(int *, int, int);
int  leenombre(char *);
int  escogeopc(int, int);
void creaAvatar(uint16_t, uint16_t);
void analizaCabeceras(void);


void menu() {
	printf("\n\n");
	printf(" === Menú principal ===\n");
	printf(" 1. Muestra información sobre las cabeceras de un .bmp.\n");
	printf(" 2. Crea un avatar 16x16.\n");
	/* recuerda actualizar NUM_OPC si cambias las opciones */
	printf("    0. Salir.\n");
}

int leeIntRango(int *v, int bajo, int alto) {
	int valido = 0;
	char buf[TAM_MAX];

	printf("> ");
	if (fgets(buf, TAM_MAX, stdin) != NULL) {
		if (sscanf(buf, "%d", v) == 1) {
			if (bajo <= *v && *v <= alto) {
				valido = 1;
			}
			else {
				printf("Sólo enteros en el rango ");
				printf("[%d, %d]\n", bajo, alto);
			}
		}
		else {
			printf("Sólo enteros en el rango ");
			printf("[%d, %d]\n", bajo, alto);
		}
	}
	else {
		printf("Error fgets.\n");
	}

	return valido;
}

int leenombre(char *nombre) {
	int valido = 0;
	char buf[TAM_MAX];
	printf("Nombre del fichero .bmp: ");
	if (fgets(buf, TAM_MAX, stdin) != NULL) {
		if (sscanf(buf, "%s", nombre) == 1) {
			valido = 1;
		}
		else {
			printf("Formato incorrecto.\n");
		}
	}
	else {
		printf("Error fgets.\n");
	}

	return valido;
}

int escogeopc(int bajo, int alto) {
	int valido = 0;
	int valor  = 0;

	do {
		valido = leeIntRango(&valor, bajo, alto);
	} while (valido == 0);

	return valor;
}

void creaAvatar(uint16_t ancho, uint16_t alto) {
	FILE *avatarbmp;
	avatarbmp = fopen(AVATARFN, "w");
	if (avatarbmp == NULL) {
		printf("Error while opening file %s\n", AVATARFN);
		return;
	}
}

void analizaCabeceras(void) {
	int valido = 0;
	char nombrefichero[TAM_MAX];
	FILE *bmp;

	bmpFileHdr filehdr;
	bmpInfoHdr infohdr;

	do {
		valido = leenombre(nombrefichero);
	} while (valido == 0);

	bmp = fopen(nombrefichero, "r");
	if (bmp == NULL) {
		printf("Error abriendo el fichero %s:", nombrefichero);
		perror("");
		return;
	}

	/* TODO: meter toda esta parte en compruebaCabeceras(bmp) para que
	 * en main no se haga mención a nada que sea propio de bitmap */

	/* lee las cabeceras */
	fread(&filehdr, sizeof(bmpFileHdr), 1, bmp);
	fread(&infohdr, sizeof(bmpInfoHdr), 1, bmp);

	if (compruebaCabeceras(&filehdr, &infohdr) == 0) {
		printf("Imagen bmp reconocida.\n");
		procesaCabeceras(&filehdr, &infohdr);
	}
	else {
		printf("Error con la imagen %s.\n", nombrefichero);
	}

	fclose(bmp);

}

int main(void) {
	printf("¡Hola, mundo!\n");

	int seleccion = 0;

	do {
		menu();
		seleccion = escogeopc(0, NUM_OPC);
		switch (seleccion) {
		case 1:
			analizaCabeceras();
			break;
		case 2:
			printf("Creando avatar 16x16.\n");
			creaAvatar(16, 16);
			break;
		default:
			printf("Saliendo...\n");
		}
	} while(seleccion != 0);

	return 0;
}

