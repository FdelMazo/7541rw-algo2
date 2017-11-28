// Federico del Mazo - 100029
// TP1 - FIXCOL
// Corrige Gonzalo

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filelib.h"

int main (int argc, char* argv[]){
	if(argc != 3) return -1;
	char* n_archivo = argv[1];
	int bytes = atoi(argv[2]);
	FILE* archivo = fopen(n_archivo, "r");
	if(!archivo) return -1;
	long int tamano = tamano_archivo(archivo);
	while(!feof(archivo)){
		char* linea = malloc(tamano);
		if(!linea) return -1;
		size_t leidos = fread(linea, sizeof(char), bytes,archivo);
		fwrite(linea, sizeof(char),leidos, stdout);
		fputc('\n',stdout);
		free(linea);
	}
	fclose(archivo);
	return 0;
}
