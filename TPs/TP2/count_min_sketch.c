// Lucia Pardo 99999 - Federico del Mazo 100029
// TP2 - TDA COUNT MIN SKETCH
// Corrige Gonzalo

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#include "count_min_sketch.h"

#define TAM_INICIAL 2017 //Primo grande
#define ARRAY_DE_MULTS 7,11,31 //Primos

/* *****************************************************************
                         FUNCIONES AUXILIARES
 * *****************************************************************/

//Funcion de hashing modificada para recibir un multiplicador primo
//La idea es usar siempre la misma iterando sobre un array de multiplicadores
size_t fhashing(const char* clave, size_t tam, size_t mult){
   size_t clave_hash = 0;
   for(size_t i = 0; clave[i] !='\0'; i++)
      clave_hash = mult * clave_hash + clave[i];
   return clave_hash % tam;
} 

/* *****************************************************************
                         COUNT MIN SKETCH
 * *****************************************************************/
struct count_min_sketch{
	size_t** tabla; //Arreglo de k arreglos
	size_t tam;
	size_t* array_multiplicadores;
	size_t k; //Cantidad de arreglos == Cantidad de fhashings
};

//Se puede modificar para recibir tam_inicial y array de mults por parametro
count_min_sketch_t* count_min_sketch_crear(){
	count_min_sketch_t* count = malloc(sizeof(count_min_sketch_t));
	if(!count) return NULL;
	
	size_t tmp[] = {ARRAY_DE_MULTS};
	count->k = sizeof(tmp)/sizeof(size_t);
	count->tam = TAM_INICIAL;
	
	count->array_multiplicadores = calloc(count->k,sizeof(size_t));
	if(!count->array_multiplicadores) return NULL;
	for(size_t i = 0;i<count->k;i++)
		count->array_multiplicadores[i] = tmp[i]; 
	
	count->tabla = calloc(count->k,sizeof(size_t));
	if(!count->tabla) return NULL;
	for(size_t i = 0; i<count->k; i++){
		count->tabla[i] = calloc(count->tam,sizeof(size_t));
		if(!count->tabla[i]) return NULL;
	}
	return count;
}

void count_min_sketch_destruir(count_min_sketch_t* count){
	for(size_t i = 0; i<count->k; i++)
		free(count->tabla[i]);
	free(count->array_multiplicadores);
	free(count->tabla);
	free(count);
}

void count_min_sketch_guardar(count_min_sketch_t* count, char* clave){
	for(size_t i = 0; i<count->k; i++){
		size_t pos = fhashing(clave, count->tam, count->array_multiplicadores[i]);
		count->tabla[i][pos]++;
	}
}

size_t count_min_sketch_obtener(count_min_sketch_t* count, char* clave){
	size_t min = INT_MAX;
	for(size_t i = 0; i<count->k; i++){
		size_t pos = fhashing(clave, count->tam, count->array_multiplicadores[i]);
		if(count->tabla[i][pos] < min) min = count->tabla[i][pos];
	}
	return min;
}




	
