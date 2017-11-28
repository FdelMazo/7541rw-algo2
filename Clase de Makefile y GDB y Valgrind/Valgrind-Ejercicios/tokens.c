#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define CANT_ARGS 4
#define SEPARADOR " "


// http://queue.acm.org/detail.cfm?id=2010365

char** parsear_comando(char* comando) {
    char** argumentos = malloc(CANT_ARGS * sizeof(char*));
    if(!argumentos)
        return NULL;
        
    size_t cant = 0;
    
    argumentos[cant] = strtok(comando, SEPARADOR);
    while(argumentos[cant] != NULL)
    {
        cant++;
        argumentos[cant] = strtok(NULL, SEPARADOR);
    }
    
    return argumentos;
}


int main() {
    char* comando = "abrir productos.csv nros_serie.csv ventas.csv";
    char* comando_c = malloc(sizeof(char) * strlen(comando));
    if(!comando_c)
        return -1;
    strcpy(comando_c, comando);
    
    char** argumentos = parsear_comando(comando_c);
    if(!argumentos)
        return -1;
    
    for(size_t i = 0; i < CANT_ARGS; i++)
        printf("Argumento %zu: %s\n", i, argumentos[i]);
    
    free(comando_c);
    return 0;
}
