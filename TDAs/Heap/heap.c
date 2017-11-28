// Heap - Lucia Pardo 99999 - Federico del Mazo 100029
// Corrige Gonzalo

#include "heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP_INICIAL 10
#define AGRANDAR 2
#define ACHICAR 2
/* *****************************************************************
                        FUNCIONES AUXILIARES
 * *****************************************************************/

 void swap(void* *nodo1, void* *nodo2){
	void* tmp = *nodo1;
	*nodo1 = *nodo2;
	*nodo2 = tmp;
}

void upheap(void** arreglo, size_t nodo, cmp_func_t comparacion){
	if(nodo==0) return;
	size_t padre = (nodo-1)/2;
	int cmp = comparacion(arreglo[nodo], arreglo[padre]);
	if(cmp>0){
		swap(&arreglo[nodo], &arreglo[padre]);
		upheap(arreglo, padre, comparacion);
	}	
}

void downheap(void** arreglo, size_t largo,  size_t nodo, cmp_func_t cmp){
	if(nodo>=largo) return;
	size_t max = nodo;
	size_t der = 2*nodo+1, izq = 2*nodo+2;
	if (izq < largo && cmp(arreglo[max],arreglo[izq]) < 0){
		max = izq;
	}
	if (der < largo && cmp(arreglo[max],arreglo[der]) < 0){
		max = der;
	}
	if (max != nodo){
		swap(&arreglo[max],&arreglo[nodo]);
		downheap(arreglo, largo, max, cmp);
	}	
}	

void heapify(void ** arreglo, size_t n, cmp_func_t cmp){
	for(int i = (int)n/2;i>=0;i--)
		downheap(arreglo, n, i, cmp);
}

/* *****************************************************************
                              HEAP
 * *****************************************************************/
struct heap{
	void** datos;
	size_t cantidad;
	size_t capacidad;
	cmp_func_t cmp;
};

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	heap->datos = calloc(CAP_INICIAL, sizeof(void*));
	if(!heap || !heap->datos){
		free(heap->datos);
		free(heap);
		return NULL;
	}
	heap->capacidad = CAP_INICIAL;
	heap->cantidad = 0;
	heap->cmp = cmp;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	heap->datos = calloc(CAP_INICIAL*n, sizeof(void*));
	if(!heap || !heap->datos){
		free(heap->datos);
		free(heap);
		return NULL;
	}
	for(size_t i = 0;i<n;i++) //Hay forma mas facil de "dinamizar" un array estatico?
		heap->datos[i] = arreglo[i]; 
	heapify(heap->datos, n, cmp);
	heap->capacidad = CAP_INICIAL*n;
	heap->cantidad = n;
	heap->cmp = cmp;
	return heap;
}

void heap_destruir(heap_t *heap, void dst(void *e)){
	if(dst){
		for(size_t i = 0; i<heap->cantidad; i++)
			dst(heap->datos[i]);
	}
	free(heap->datos);
	free(heap);
}

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo){
	void* temp = realloc(heap->datos, tam_nuevo * sizeof(void*));
		if(!temp) return false;
	heap->datos = temp;
	heap->capacidad = tam_nuevo;
	return true;
} 

size_t heap_cantidad(const heap_t* heap){
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	return !heap->cantidad;
}

void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

bool heap_encolar(heap_t *heap, void *elem){
	if(!elem) return false;
	if((float)(heap->cantidad==heap->capacidad)){ 
		if(!heap_redimensionar(heap, heap->capacidad * AGRANDAR))
			return false;
	}
	heap->datos[heap->cantidad] = elem;
	heap->cantidad++;
	upheap(heap->datos,heap->cantidad-1,heap->cmp);
	return true;
}

void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	if (heap->cantidad < (heap->capacidad / ACHICAR)){
		if(!heap_redimensionar(heap,heap->capacidad / ACHICAR))
			return NULL;
	}
	void* dato = heap->datos[0];
	heap->datos[0] = heap->datos[heap->cantidad-1];
	downheap(heap->datos, heap->cantidad, 0, heap->cmp);
	heap->cantidad--;
	return dato;
}

/* *****************************************************************
                     HEAP SORT - AFUERA DEL TDA
 * *****************************************************************/
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cant, cmp);
	for(int i = (int)cant-1; i>=0;i--){
		swap(&elementos[0], &elementos[i]);
		downheap(elementos, i, 0, cmp);
	}
}

