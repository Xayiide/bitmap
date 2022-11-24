#include <stdio.h>
#include <stdint.h>
//#include <errno.h>   /* errno    */
#include <string.h>  /* strerror */

#include "inc/bitmap.h"

#define TAM_MAX 256
#define OPC_MEN 2
#define OPC_AVT 3


void menu(void);
void menuavatar(void);
int  leeIntRango(int *, int, int);
int  leenombre(char *);
int  escogeopc(int, int);
void creacionAvatar(void);
void analizaCabeceras(void);


void menu() {
	printf("\n\n");
	printf(" === Menú principal ===\n");
	printf(" 1. Muestra información sobre las cabeceras de un .bmp.\n");
	printf(" 2. Crea un avatar.\n");
	/* recuerda actualizar NUM_OPC si cambias las opciones */
	printf("    0. Salir.\n");
}

void menuavatar() {
	printf(" 1. Simetría horizontal.\n");
	printf(" 2. Simetría vertical.\n");
	printf(" 3. Simetría a cuartos.\n");

	printf("    0. Cancelar.\n");
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

void creacionAvatar(void) {
	int seleccion = 0;

	do {
		menuavatar();
		seleccion = escogeopc(0, 3);
		switch (seleccion) {
		case 1:
			printf("Creando un avatar de 8x8 con simetría horizontal.\n");
			creaAvatar(8, HORIZONTAL);
			break;
		case 2:
			printf("Creando un avatar de 8x8 con simetría vertical.\n");
			creaAvatar(8, HORIZONTAL);
			break;
		case 3:
			printf("Creando un avatar de 8x8 a cuartos.\n");
			creaAvatar(8, HORIZONTAL);
			break;
		default:
			printf("Volviendo al menú principal.\n");
			break;
		}
	} while (seleccion == 0);
}




void analizaCabeceras(void) {
	int valido = 0;
	char nombrefichero[TAM_MAX];
	FILE *bmp;

	do {
		valido = leenombre(nombrefichero);
	} while (valido == 0);

	bmp = fopen(nombrefichero, "r");
	if (bmp == NULL) {
		printf("Error abriendo el fichero %s:", nombrefichero);
		perror("");
		return;
	}


	if (leeCabeceras(bmp) != 0) {
		printf("No se reconoce la imagen bmp. Cabeceras corruptas.\n");
	}

	fclose(bmp);

}

int main(void) {
	printf("¡Hola, mundo!\n");

	int seleccion = 0;

	do {
		menu();
		seleccion = escogeopc(0, OPC_MEN);
		switch (seleccion) {
		case 1:
			analizaCabeceras();
			break;
		case 2:
			creacionAvatar();
			break;
		default:
			printf("Saliendo...\n");
		}
	} while(seleccion != 0);

	return 0;
}

