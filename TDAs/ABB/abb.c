// Arbol de Busqueda Binario - Lucia Pardo 99999 - Federico del Mazo 100029
// Corrige Gonzalo
#include "abb.h"
#include "pila.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *****************************************************************
                         NODO DE ARBOL BINARIO
 * *****************************************************************/
typedef struct nodo_abb nodo_abb_t;
struct nodo_abb{
	char* clave;
	void* dato;
	nodo_abb_t* izq;
	nodo_abb_t* der;
};

nodo_abb_t* nodo_abb_crear(const char* clave, void* dato){
	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
		if(!nodo) return NULL;
	nodo->clave = strcpy(malloc(strlen(clave) + 1), clave);
		if(!nodo->clave) return NULL;
	nodo->dato = dato;
	nodo->izq = NULL;
	nodo->der = NULL;
	return nodo;
}

//Nota: Recibe un booleano que indica si destruye clave y dato (true) o solo clave
void* nodo_abb_destruir(nodo_abb_t* nodo, abb_destruir_dato_t dst, bool dato){
	if(dato && dst) dst(nodo->dato);
	free(nodo->clave);
	free(nodo);
	return NULL;
}

//Funcion auxiliar de abb_borrar
//Encuentra el sucesor inorder de un nodo, y para esto debe recibir la rama derecha de ese nodo
nodo_abb_t* nodo_abb_sucesor(nodo_abb_t *raiz) {
	nodo_abb_t* sucesor = raiz;
	while(sucesor->izq) {
		sucesor = sucesor->izq;
	}
	return sucesor;
}

//Funcion auxiliar de abb_borrar y de abb_guardar
//Reemplaza tanto la clave como los datos del primer nodo con los del segundo 
void nodo_abb_pisar_datos(nodo_abb_t* nodo_a_pisar, nodo_abb_t* nodo_que_pisa, abb_destruir_dato_t dst){
	free(nodo_a_pisar->clave);
	nodo_a_pisar->clave = malloc(strlen(nodo_que_pisa->clave) + 1);
	strcpy(nodo_a_pisar->clave, nodo_que_pisa->clave);
	
	if(dst) dst(nodo_a_pisar->dato);
	nodo_a_pisar->dato = nodo_que_pisa->dato;
}

/* *****************************************************************
                         ARBOL BINARIO DE BUSQUEDA
 * *****************************************************************/
struct abb{
	nodo_abb_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t dst;
	size_t cant;
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
		if (!abb) return NULL;
	abb->raiz = NULL;
	abb->cant = 0;
	abb->cmp = cmp;
	abb->dst = destruir_dato;
	return abb;
}

void abb_destruir_rec(nodo_abb_t** raiz, abb_destruir_dato_t dst){
	if(! *raiz) return;
	abb_destruir_rec(&(*raiz)->izq, dst);
	abb_destruir_rec(&(*raiz)->der, dst);
	nodo_abb_destruir(*raiz, dst, true);
}

void abb_destruir(abb_t *abb){
	abb_destruir_rec(&abb->raiz, abb->dst);
	free(abb);
}

bool abb_guardar_rec(nodo_abb_t** raiz, nodo_abb_t* nodo, abb_comparar_clave_t comparar, abb_destruir_dato_t dst){
	if(! *raiz){
		*raiz = nodo;
		return true;
	}
	int cmp = comparar((*raiz)->clave, nodo->clave);
	if(cmp == 0){ //Reemplazar dato
		nodo_abb_pisar_datos(*raiz, nodo, dst);
		nodo_abb_destruir(nodo, dst, false);
		return false;
	}
	else if(cmp>0) return abb_guardar_rec(&(*raiz)->izq, nodo, comparar, dst);
	else if(cmp<0) return abb_guardar_rec(&(*raiz)->der, nodo, comparar, dst);
	return true;
}

bool abb_guardar(abb_t *abb, const char *clave, void *dato){
	nodo_abb_t* nodo = nodo_abb_crear(clave, dato);
	if(!nodo) return false;
	bool res = abb_guardar_rec(&abb->raiz, nodo, abb->cmp, abb->dst);
	if(res) abb->cant++;
	return true;
}

//Nota: Funcion que obtiene el nodo 
nodo_abb_t* abb_obtener_nodo(nodo_abb_t* raiz, const char *clave, abb_comparar_clave_t comparar){
	if(! raiz) return NULL;
	int cmp = comparar(raiz->clave, clave);
	if(cmp==0) return raiz;
	else if(cmp>0) return abb_obtener_nodo(raiz->izq, clave, comparar);
	else if(cmp<0) return abb_obtener_nodo(raiz->der, clave, comparar);
	return NULL;
}

//Nota: Funcion que obtiene la clave, llamando a la funcion que obtiene el nodo
void* abb_obtener(const abb_t *abb, const char *clave){
	nodo_abb_t* nodo = abb_obtener_nodo(abb->raiz, clave, abb->cmp);
	return nodo ? nodo->dato : NULL;
}

//Nota: solo comprueba si obtener encontro	
bool abb_pertenece(const abb_t *abb, const char *clave){
	nodo_abb_t* nodo = abb_obtener_nodo(abb->raiz, clave, abb->cmp);
	return nodo ? true : false;
}

void abb_in_order_rec(nodo_abb_t** raiz, bool visitar(const char *, void *, void *), void *extra){
	if(! *raiz) return;
	if(! (*raiz)->clave) return;
	abb_in_order_rec(&(*raiz)->izq, visitar, extra);
	if(!visitar((*raiz)->clave, (*raiz)->dato, extra)) return;
	abb_in_order_rec(&(*raiz)->der, visitar, extra);
}

void abb_in_order(abb_t *abb, bool visitar(const char *, void *, void *), void *extra){
	abb_in_order_rec(&abb->raiz, visitar, extra);	
}

//Funcion auxiliar de abb_borrar
//Reestructura la raiz del arbol. Siempre mantiene la invariante del ABB
nodo_abb_t* abb_borrar_rec(nodo_abb_t *raiz, nodo_abb_t* nodo, abb_comparar_clave_t comparar, abb_destruir_dato_t dst){
	if (!raiz) return NULL;
	int cmp = comparar(nodo->clave, raiz->clave);
	nodo_abb_t* act;
	if(cmp<0)
		raiz->izq = abb_borrar_rec(raiz->izq, nodo, comparar, dst);
	else if(cmp>0)
		raiz->der = abb_borrar_rec(raiz->der, nodo, comparar, dst);
	else if(cmp == 0){
		if(!raiz->izq || !raiz->der){
			if(!raiz->izq)
				act = raiz->der;
			else if(!raiz->der)
				act = raiz->izq;
			nodo_abb_destruir(raiz, dst, true);
			return act;
		}
		act = nodo_abb_sucesor(raiz->der);
		nodo_abb_pisar_datos(raiz, act, dst);
		raiz->der = abb_borrar_rec(raiz->der, act, comparar, dst);
	}
	return raiz;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
   	nodo_abb_t* nodo = abb_obtener_nodo(arbol->raiz, clave, arbol->cmp);
	if (!nodo) return NULL;
	void* dato = nodo->dato;
	arbol->raiz = abb_borrar_rec(arbol->raiz, nodo, arbol->cmp, arbol->dst);
	arbol->cant--;
	return dato;
}

size_t abb_cantidad(abb_t *abb){
	return abb->cant;
}

/* *****************************************************************
        ITERADOR IN ORDER EXTERNO DE ARBOL BINARIO DE BUSQUEDA
 * *****************************************************************/
 struct abb_iter{
	 pila_t* pila;
	 const abb_t* abb;
};

//Funcion auxiliar de abb_iter_in_crear y de abb_iter_in_avanzar
//Apila todos los izquierdos de un nodo
void pila_apilar_izquierdos(pila_t* pila, nodo_abb_t* nodo){
	if(!nodo) return;
	while(nodo){
		pila_apilar(pila, nodo);
		nodo = nodo->izq;
	}
	return;
}


abb_iter_t *abb_iter_in_crear(const abb_t *abb){
	if(!abb) return NULL;
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if(!iter) return NULL;
	iter->abb = abb;
	iter->pila = pila_crear();
	nodo_abb_t* nodo = iter->abb->raiz;
	pila_apilar_izquierdos(iter->pila, nodo);
	return iter;
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	nodo_abb_t* act = pila_ver_tope(iter->pila);
	return act ? act->clave : NULL;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)) return false;
	nodo_abb_t* desapilado = pila_desapilar(iter->pila);
	if(desapilado) 
		pila_apilar_izquierdos(iter->pila, desapilado->der);
	return true;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}


/* Imprimir un ABB recorriendolo por Niveles.
O(n^2) 
Menor complejidad se puede lograr con BFS*/
size_t _abb_altura(nodo_abb_t** raiz){
	if (! *raiz) return 0;
	size_t altura_izq = _abb_altura(&(*raiz)->izq);
	size_t altura_der = _abb_altura(&(*raiz)->der);
	if (altura_der > altura_izq){
		return altura_der+1;
	}
	else {
		return altura_izq+1;
	}
}

size_t abb_altura(abb_t* abb){
	size_t altura = _abb_altura(&abb->raiz);
	return altura;
}

void _abb_imprimir(nodo_abb_t** raiz, size_t altura){
	if (! *raiz) return;
	if (altura == 1){
		printf("%s ", (*raiz)->clave);
	}
	else {
		_abb_imprimir(&(*raiz)->izq, altura-1);
		_abb_imprimir(&(*raiz)->der, altura-1);
	}
}

void abb_imprimir(abb_t* abb){
	size_t altura = abb_altura(abb);
	for (size_t i = 1; i<=altura; i++){
		_abb_imprimir(&abb->raiz, i);
		printf("\n");
	}
}
