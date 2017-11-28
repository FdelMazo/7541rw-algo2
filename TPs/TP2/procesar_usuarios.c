// Lucia Pardo 99999 - Federico del Mazo 100029
// TP2 - PROCESAR USUARIOS
// Corrige Gonzalo

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "heap_aux.h"
#include "count_min_sketch.h"
#include "heap.h"
#include "hash.h"
#include "strutil.h"

void imprimir_usuarios(nodo_heap_t** arreglo, int largo, cmp_func_t cmp){
	heap_sort((void**)arreglo, largo, cmp);
	size_t cant = 0;
	for(int i = largo-1; i>=0;i--){
		if(*nodo_heap_dato(arreglo[i]) != cant){
			printf("\n\n %3zd: ", *nodo_heap_dato(arreglo[i]));
			cant = *nodo_heap_dato(arreglo[i]);
		}
		printf("@%s ",nodo_heap_clave(arreglo[i]));
		nodo_heap_destruir(arreglo[i]);
	}
	printf("\n");
}

int main (int argc, char* argv[]){
	if(argc != 2) return -1;
	char* n_archivo = argv[1];
	FILE* archivo = fopen(n_archivo, "r");
	if(!archivo) return -1;
	
	hash_t* hash = hash_crear(free);
	
	while(!feof(archivo)){
		if(!hash) return -1;
		
		char* linea = NULL;
		size_t tam = 0;
		getline(&linea, &tam, archivo);
		if(feof(archivo)){
			free(linea);
			break;
		}
		
		char** tweet = split(linea, ',');
		char* usuario = tweet[0];
	
		for(size_t j = 1; tweet[j];j++){
			size_t* cant = calloc(1,sizeof(size_t));
			if(hash_pertenece(hash, usuario)){ 
				*cant += *(size_t*)hash_obtener(hash,usuario);
			}
			*cant+=1;
			hash_guardar(hash, usuario, cant);
		}
		free(linea);
		free_strv(tweet);
	}
	
	nodo_heap_t** arr_nodos = calloc(hash_cantidad(hash),sizeof(nodo_heap_t*));
	if(!arr_nodos) return -1;
	hash_iter_t* hash_iter = hash_iter_crear(hash);
	if(!hash_iter) return -1;
	for(size_t act = 0; !hash_iter_al_final(hash_iter);act++){
		const char* usuario = hash_iter_ver_actual(hash_iter);
		size_t* cant = hash_obtener(hash, usuario);
		nodo_heap_t* nodo = nodo_heap_crear(usuario, cant);
		arr_nodos[act] = nodo;
		hash_iter_avanzar(hash_iter);
	}
	
	imprimir_usuarios(arr_nodos, (int)hash_cantidad(hash), cmp_nodo_heap_inv);

	hash_iter_destruir(hash_iter);
	free(arr_nodos);
	hash_destruir(hash);
	fclose(archivo);
	return 0;
}

