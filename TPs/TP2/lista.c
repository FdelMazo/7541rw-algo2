// Lista - 100029 - del Mazo, Federico
// Corrige Gonzalo

#include "lista.h"
#include <stdlib.h>

/* NODO */
typedef struct nodo nodo_t;
struct nodo{
	void* dato;
	nodo_t* prox;
};

nodo_t* nodo_crear(void* dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}

void nodo_destruir(nodo_t* nodo){
	free(nodo);
}

/* LISTA ENLAZADA */
typedef struct lista lista_t;
struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if (!lista) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

void lista_destruir(lista_t* lista, void (*destruir_dato)(void *)){
	while(!(lista_esta_vacia(lista))){
		if(destruir_dato)
			destruir_dato(lista->prim->dato);
		lista_borrar_primero(lista);
	}
	free(lista);
}

bool lista_esta_vacia(const lista_t* lista){
	return (!lista->largo);
}

bool lista_insertar_primero(lista_t* lista, void* dato){
	nodo_t* nodo = nodo_crear(dato);
	if (!nodo) return false;
	if (lista_esta_vacia(lista))
		lista->ult = nodo;
	else
		nodo->prox = lista->prim;
	lista->prim = nodo;
	lista->largo++; 
	return true; 
}

bool lista_insertar_ultimo(lista_t* lista, void* dato){
	nodo_t* nodo = nodo_crear(dato);
	if (!nodo) return false;
	if (lista_esta_vacia(lista))
		lista->prim = nodo;
	else
		lista->ult->prox = nodo;
	lista->ult = nodo;
	lista->largo++;
	return true;
}

void* lista_ver_primero(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return (lista->prim->dato);
}

void* lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	return (lista->ult->dato);
}

void* lista_borrar_primero(lista_t* lista){
	if (lista_esta_vacia(lista)) return NULL;
	void* dato_primero = lista_ver_primero(lista);
	nodo_t* nodo_borrado = lista->prim;
	lista->prim = lista->prim->prox;
	nodo_destruir(nodo_borrado);
	lista->largo--;
	return dato_primero;
}
 
size_t lista_largo(const lista_t* lista){
	return lista->largo;
}

void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra){
	nodo_t* n_act = lista->prim;
	while(n_act){
		if(!visitar(n_act->dato, extra)) return;
		n_act = n_act->prox;
	}
}

/* ITERADOR EXTERNO */
typedef struct lista_iter lista_liter_t;
struct lista_iter{
	lista_t* lista;
	nodo_t* ant;
	nodo_t* act;
};

lista_iter_t* lista_iter_crear(lista_t* lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if(!iter) return NULL;
	iter->lista = lista;
	iter->ant = NULL;
	iter->act = lista->prim;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t* iter){
	if(lista_iter_al_final(iter))
		return false;
	iter->ant = iter->act;
	iter->act = iter->act->prox;
	return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
	if(lista_iter_al_final(iter)) return NULL;
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t* iter){
	return (!iter->act);
}

void lista_iter_destruir(lista_iter_t* iter){
	free(iter);
}
	
bool lista_iter_insertar(lista_iter_t* iter, void* dato){
	nodo_t* nodo = nodo_crear(dato);
	if (!nodo) return false;
	if(iter->lista->largo == 0 || !iter->ant)
		iter->lista->prim = nodo;
	if(lista_iter_al_final(iter))
		iter->lista->ult = nodo;
	if(iter->ant)
		iter->ant->prox = nodo;
	nodo->prox = iter->act;
	iter->act = nodo;
	iter->lista->largo++;
	return true;
}

void* lista_iter_borrar(lista_iter_t* iter){
	if(lista_iter_al_final(iter)) return NULL;
	nodo_t* nodo_borrado = iter->act;
	void* dato_borrado = nodo_borrado->dato;
	if(iter->act == iter->lista->prim)
		iter->lista->prim = iter->act->prox;
	else if(iter->act == iter->lista->ult)
		iter->lista->ult = iter->ant;
	iter->act = iter->act->prox;
	if (iter->ant)
		iter->ant->prox = iter->act;
	nodo_destruir(nodo_borrado);
	iter->lista->largo--;
	return dato_borrado;
}
