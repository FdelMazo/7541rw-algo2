// Federico del Mazo - 100029
// TP1 - FILESPLIT
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
	size_t i=1;
	while(!feof(archivo)){ 
		char* n_nuevo = nombrar_archivo(n_archivo, i);
		FILE* nuevo = fopen(n_nuevo, "w");
		if(!nuevo) return -1;
		char* linea = malloc(bytes);
		if(!linea) return -1;
		size_t leidos = fread(linea, sizeof(char), bytes,archivo);
		fwrite(linea, sizeof(char),leidos, nuevo);
		free(n_nuevo);
		free(linea);
		fclose(nuevo);
		i++;
	}
	fclose(archivo);
	return 0;
}
