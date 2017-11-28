// Lucia Pardo 99999 - Federico del Mazo 100029
// TP2 - HEAP AUXILIAR 
// Corrige Gonzalo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "heap_aux.h"
#include "heap.h"
#include "lista.h"

/* *****************************************************************
                         ESTRUCTURA NODO
 * *****************************************************************/
struct nodo_heap{
	char* clave;
	size_t* dato;
};

nodo_heap_t* nodo_heap_crear(const char* clave, size_t* cant){
	nodo_heap_t* nodo = calloc(1,sizeof(nodo_heap_t));
	nodo->clave = calloc(strlen(clave) +1,sizeof(char)); 
	if(!nodo || !nodo->clave){
		free(nodo->clave);
		free(nodo);
		return NULL;
	}
	strcpy(nodo->clave, clave);
	nodo->dato = cant;
	return nodo;
}

void nodo_heap_destruir(nodo_heap_t* nodo){
	free(nodo->clave);
	free(nodo);
	return;
}

//Wrapper de la funcion nodo_destruir para usar con heap_destruir
void wrapper_nodo_heap_destruir(void* nodo){
	nodo_heap_t* nodo_n = nodo;
	nodo_heap_destruir(nodo_n);
	return;
}

//Funcion de comparacion de nodo de heaps invertida
//La funcion esta invertida, por lo tanto, crea un heap de minimos con la implementacion de heap de maximos
int cmp_nodo_heap_inv(const void *a, const void *b){
	const nodo_heap_t* nodo1 = a;
	const nodo_heap_t* nodo2 = b;
	if(nodo1 && nodo2 && *nodo1->dato > *nodo2->dato) return -1;
	else if(nodo1 && nodo2 && *nodo1->dato < *nodo2->dato) return 1;
	return 0;
}

size_t* nodo_heap_dato(nodo_heap_t* nodo){
	return nodo->dato;
}

char* nodo_heap_clave(nodo_heap_t* nodo){
	return nodo->clave;
}
/* *****************************************************************
                         FUNCIONES AUXILIARES
 * *****************************************************************/
//Imprime los mayores K nodos del arreglo, haciendo uso de un heap de minimos
void arreglo_imprimir_top_k(nodo_heap_t** arreglo, size_t n, size_t k, cmp_func_t cmp){
	if(n<k) k=n;
	heap_t* heap_de_min = heap_crear_arr((void**)arreglo, k, cmp);
	if(!heap_de_min) return;
	for(size_t i = k; i<n;i++){
		nodo_heap_t* nodo = arreglo[i];
		nodo_heap_t* raiz = heap_ver_max(heap_de_min);
		if(cmp(nodo,raiz)<0){
			heap_desencolar(heap_de_min);
			heap_encolar(heap_de_min, nodo);
		}
	}
	
	nodo_heap_t** arreglo_a_sortear= calloc(k, sizeof(nodo_heap_t*));
	for(size_t i = 0; i<k;i++){
		nodo_heap_t* raiz = heap_desencolar(heap_de_min);
		arreglo_a_sortear[i] = raiz;
	}
	
	heap_sort((void**)arreglo_a_sortear, k, cmp);
	for(size_t i = 0; i<k;i++){
		if(arreglo_a_sortear[i])
			printf("#%-20s - %3zd\n", nodo_heap_clave(arreglo_a_sortear[i]), *nodo_heap_dato(arreglo_a_sortear[i]));
	}
		
	free(arreglo_a_sortear);
	heap_destruir(heap_de_min, wrapper_nodo_heap_destruir);
}





