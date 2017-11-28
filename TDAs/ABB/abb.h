// Arbol de Busqueda Binario - Lucia Pardo 99999 - Federico del Mazo 100029
// Corrige Gonzalo

#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);


/* *****************************************************************
                         NODO DE ARBOL BINARIO
 * *****************************************************************/
struct nodo_abb;
typedef struct nodo_abb nodo_abb_t;

nodo_abb_t* nodo_abb_crear(const char* clave, void* dato);

void* nodo_abb_destruir(nodo_abb_t* nodo, abb_destruir_dato_t dst, bool dato);

/* *****************************************************************
                         ARBOL BINARIO DE BUSQUEDA
 * *****************************************************************/
struct abb;
typedef struct abb abb_t;

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

void abb_destruir(abb_t *arbol);

bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* *****************************************************************
        ITERADOR IN ORDER EXTERNO DE ARBOL BINARIO DE BUSQUEDA
 * *****************************************************************/
struct abb_iter;
typedef struct abb_iter abb_iter_t;

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

void abb_iter_in_destruir(abb_iter_t* iter);

const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

bool abb_iter_in_avanzar(abb_iter_t *iter);

bool abb_iter_in_al_final(const abb_iter_t *iter);

#endif // ABB_H
