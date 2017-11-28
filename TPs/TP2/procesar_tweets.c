// Lucia Pardo 99999 - Federico del Mazo 100029
// TP2 - PROCESAR TWEETS
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

//Funcion que recibe un hash y devuelve un arreglo de nodos (clave, valor)
nodo_heap_t** arr_nodo_heap_crear(hash_t* hash, size_t cant){
	nodo_heap_t** arr_hashtag = calloc(cant,sizeof(nodo_heap_t*));
	if(!arr_hashtag) return NULL;
	hash_iter_t* hash_iter = hash_iter_crear(hash);
	if(!hash_iter) return NULL;
	
	for(size_t act = 0; !hash_iter_al_final(hash_iter);act++){
		const char* act_clave = hash_iter_ver_actual(hash_iter);
		size_t* act_cant = hash_obtener(hash, act_clave);
		nodo_heap_t* ht = nodo_heap_crear(act_clave, act_cant);
		arr_hashtag[act] = ht;
		hash_iter_avanzar(hash_iter);
	}
	
	hash_iter_destruir(hash_iter);
	return arr_hashtag;
}

int main (int argc, char* argv[]){
	if(!stdin) return -1;
	if(argc != 3) return -1;
	size_t cant_lineas = atoi(argv[1]); //n
	size_t trending_topics = atoi(argv[2]); //k

	count_min_sketch_t* count = count_min_sketch_crear(); //El filter no se reinicia en todo el programa
	if(!count) return -1;
		
	for(size_t veces = 0; !feof(stdin); veces++){
		printf("\n\nDe las lineas %zd a %zd \n ", veces*cant_lineas, (veces+1)*cant_lineas);
		printf("Los %zd Trending Topic son: \n\n", trending_topics);
		hash_t* hash = hash_crear(free);
		if(!hash) return -1;
		size_t cant_hashtags = 0;
		for(size_t i = 0; i<cant_lineas ;i++){
			char* linea = NULL;
			size_t tam = 0;
			ssize_t cant_linea = getline(&linea, &tam, stdin);
			
			if(cant_linea == -1){
				free(linea);
				break;
			}
			
			char* linea_dup = calloc(strlen(linea) +1,sizeof(char)); 
			for(size_t k = 0;k<strlen(linea);k++)
				linea_dup[k] = linea[k]; 
			char** hashtags = split(linea, ',');
						
			//Guardar todo en el count
			for(size_t j = 1; hashtags[j];j++){
				cant_hashtags++;
				count_min_sketch_guardar(count, hashtags[j]);
			}
						
			//Pasar del count al hash
			for(size_t j = 1; hashtags[j];j++){
				size_t* cant = calloc(1,sizeof(size_t));
				*cant = count_min_sketch_obtener(count, hashtags[j]);
				hash_guardar(hash, hashtags[j], cant);
			}

			free_strv(hashtags);
			free(linea);
			free(linea_dup);
		}
		
		//Pasar del hash a un arreglo de nodos
		nodo_heap_t** arr_hashtag = arr_nodo_heap_crear(hash, cant_hashtags);
		
		//Imprimir de ese arreglo de nodos usando heap de minimos
		arreglo_imprimir_top_k(arr_hashtag, cant_hashtags, trending_topics, cmp_nodo_heap_inv);
		
		for(size_t i = 0; i<cant_hashtags;i++)
			if(arr_hashtag[i]) nodo_heap_destruir(arr_hashtag[i]);
		free(arr_hashtag);

		hash_destruir(hash);
	}
	
	count_min_sketch_destruir(count);
	return 0;
}
