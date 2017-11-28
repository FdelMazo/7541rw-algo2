// Federico del Mazo - 100029
// TP1 - FILELIB (Aux de Fixcol y Filesplit)
// Corrige Gonzalo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filelib.h"
#define EXTENSION "txt"
#define MAX_FILENAME 255 //Linux

//Calcula el tamano de un archivo
long int tamano_archivo(FILE* archivo){
	fseek(archivo, 0, SEEK_END);
	long int tamano = ftell(archivo);
	rewind(archivo);
	return tamano;
}

//Nombra archivo.txt a archivo_nnnn.txt
char* nombrar_archivo(char* nombre, size_t n){
	char* n_nuevo = malloc(MAX_FILENAME);
	char *token = strtok(nombre, ".");
	strncpy(n_nuevo, token, strlen(token));
	sprintf(n_nuevo,"%s_%04zd.%s", token, n, EXTENSION);
	return n_nuevo;
}
