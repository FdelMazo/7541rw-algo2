#ifndef NODO_HEAP
#define NODO_HEAP

#include <stddef.h>
#include <stdbool.h>

struct nodo_heap;
typedef struct nodo_heap nodo_heap_t;

nodo_heap_t* nodo_heap_crear(const char* clave, size_t* cant);
void nodo_heap_destruir(nodo_heap_t* ht);
void wrapper_nodo_heap_destruir(void* ht);

typedef int (*cmp_func_t) (const void *a, const void *b);
void arreglo_imprimir_top_k(nodo_heap_t** arreglo, size_t n, size_t k, cmp_func_t cmp);
int cmp_nodo_heap(const void *a, const void *b);
int cmp_nodo_heap_inv(const void *a, const void *b);
int cmp_listas(const void *a, const void *b);

size_t* nodo_heap_dato(nodo_heap_t* nodo);
char* nodo_heap_clave(nodo_heap_t* nodo);

#endif // NODO_HEAP
