#ifndef FILELIB_H
#define FILELIB_H

#include <stdio.h>
#include <stdlib.h>

long int tamano_archivo(FILE* archivo);

char* nombrar_archivo(char* nombre, size_t n);

#endif // FILELIB_H
