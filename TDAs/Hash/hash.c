// Hash Abierto - Lucia Pardo 99999 - Federico del Mazo 100029

#include "lista.h"
#include "hash.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CAP_INICIAL 53
#define AGRANDAR 3 //Cuando se llama a redimensionar se triplica la capacidad
#define MULT 33 //Usado por la funcion de Hashing

/* *****************************************************************
                         NODO HASH ABIERTO
 * *****************************************************************/
 
typedef struct nodo_hash nodo_hash_t;

struct nodo_hash{
	char* clave;
	void* dato;
};

//Es importante notar que en la creacion del nodo esta el copiado de la clave
nodo_hash_t* nodo_hash_crear(const char* clave, void* dato){
	nodo_hash_t* nodo = malloc(sizeof(nodo_hash_t));
	nodo->clave = malloc(strlen(clave) +1); 
	if(!nodo || !nodo->clave){
		free(nodo->clave);
		free(nodo);
		return NULL;
	}
	strcpy(nodo->clave, clave);
	nodo->dato = dato;
	return nodo;
}

void nodo_hash_destruir(nodo_hash_t* nodo){
	free(nodo->clave);
	free(nodo);
	return;
}

void wrapper_nodo_hash_destruir(void* nodo){
	nodo_hash_t* nodo_n = nodo;
	nodo_hash_destruir(nodo_n);
	return;
}

/* *****************************************************************
               FUNCION DE LISTA ENLAZADA DE NODOS DE HASH
 * *****************************************************************/
//Devuelve el nodo si este pertenece a la lista, si no, NULL
nodo_hash_t* lista_pertenece_nodo(lista_t* lista, const char* clave){
	if(lista_esta_vacia(lista)) return false;
	lista_iter_t* lista_iter = lista_iter_crear(lista);
	if(!lista_iter) return false;
	while (!lista_iter_al_final(lista_iter)) {
		nodo_hash_t* nodo = lista_iter_ver_actual(lista_iter);
		if(strcmp(nodo->clave,clave)==0){
			lista_iter_destruir(lista_iter);
			return nodo;
		}
		lista_iter_avanzar(lista_iter);
	}
	lista_iter_destruir(lista_iter);
	return NULL;
}

/* *****************************************************************
                         ESTRUCTURA HASH ABIERTO
 * *****************************************************************/

struct hash{
	size_t capacidad;
	size_t cantidad;
	lista_t** tabla;
	hash_destruir_dato_t func_destr;
};

//Sacado de www.strchr.com. Devuelve una clave entre 0 y capacidad
size_t hashing(const char* clave, size_t capacidad){
   size_t clave_hash = 0;
   for(size_t i = 0; clave[i] !='\0'; i++)
      clave_hash = MULT * clave_hash + clave[i];
   return clave_hash % capacidad;
}
	
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	hash->tabla = malloc(sizeof(lista_t*) * CAP_INICIAL);
	if(!hash || !hash->tabla){
		free(hash->tabla);
		free(hash);
		return NULL;
	}
	hash->capacidad = CAP_INICIAL;
	hash->cantidad = 0;
	hash->func_destr = destruir_dato;
	for(size_t i = 0; i<hash->capacidad; i++)
		hash->tabla[i] = lista_crear();
	return hash;
}

bool hash_redimensionar(hash_t* hash_viejo){ 
	hash_t* hash_nuevo = malloc(sizeof(hash_t));
	hash_nuevo->tabla = malloc(sizeof(lista_t*) * hash_viejo->capacidad * AGRANDAR);
	if(!hash_nuevo || !hash_nuevo->tabla){
		free(hash_nuevo->tabla);
		free(hash_nuevo);
		return false;
	}
	hash_nuevo->capacidad = hash_viejo->capacidad * AGRANDAR;
	hash_nuevo->cantidad = 0;
	hash_nuevo->func_destr = hash_viejo->func_destr;
	for(size_t i = 0; i<hash_nuevo->capacidad; i++)
		hash_nuevo->tabla[i] = lista_crear();
	for(size_t i = 0; i<hash_viejo->capacidad; i++){
		lista_t* lista_vieja = hash_viejo->tabla[i];
		if(!lista_esta_vacia(lista_vieja)){
			lista_iter_t* lista_iter = lista_iter_crear(lista_vieja);
			while (!lista_iter_al_final(lista_iter)) {
				nodo_hash_t* act = lista_iter_ver_actual(lista_iter);
				hash_guardar(hash_nuevo, act->clave, act->dato);
				lista_iter_avanzar(lista_iter);
			}
			lista_iter_destruir(lista_iter);
		}
		lista_destruir(lista_vieja, wrapper_nodo_hash_destruir);
	}
	free(hash_viejo->tabla);
	hash_viejo->tabla = hash_nuevo->tabla;
	*hash_viejo = *hash_nuevo;
	free(hash_nuevo);
	return true;
}

//PRE: El nodo pertenece al hash. Esto no hay que corrobarlo
void hash_reemplazar(hash_t* hash, const char* clave, void* dato){
	size_t clave_hash = hashing(clave, hash->capacidad);
	lista_t* lista = hash->tabla[clave_hash];
	nodo_hash_t* act = lista_pertenece_nodo(lista, clave);
	if(hash->func_destr) hash->func_destr(act->dato);
	act->dato = dato;
	return;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){		
	float factor_carga  = (float) (hash->cantidad / hash->capacidad);
	if(factor_carga >= 0.7){
		bool redimension = hash_redimensionar(hash);
		if(!redimension) return false;
	}
	if(hash_pertenece(hash, clave)){
		hash_reemplazar(hash, clave, dato);
		return true;
	}
	nodo_hash_t* nodo = nodo_hash_crear(clave, dato);
	if(!nodo) return false;
	size_t clave_hash = hashing(clave, hash->capacidad);
	lista_insertar_primero(hash->tabla[clave_hash], nodo);
	hash->cantidad++;
	return true;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	size_t clave_hash = hashing(clave, hash->capacidad);
	lista_t* lista = hash->tabla[clave_hash];
	nodo_hash_t* nodo = lista_pertenece_nodo(lista, clave);
	if(nodo) return nodo->dato;
	return NULL;
}

void *hash_borrar(hash_t *hash, const char *clave){
	if(!hash_pertenece(hash, clave)) return NULL;
	size_t clave_hash = hashing(clave, hash->capacidad);
	lista_t* lista = hash->tabla[clave_hash];
	lista_iter_t* lista_iter = lista_iter_crear(lista);
	void* dato = hash_obtener(hash, clave);
	while (!lista_iter_al_final(lista_iter)) {
		nodo_hash_t* act = lista_iter_ver_actual(lista_iter);
		if(strcmp(clave, act->clave)==0){
			nodo_hash_destruir(act);
			lista_iter_borrar(lista_iter);
			break;
		}
		lista_iter_avanzar(lista_iter);
	}
	lista_iter_destruir(lista_iter);
	hash->cantidad--;
	return dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	size_t clave_hash = hashing(clave, hash->capacidad);
	lista_t* lista = hash->tabla[clave_hash];
	nodo_hash_t* nodo = lista_pertenece_nodo(lista, clave);
	if(nodo) return true;
	return false;
}

size_t hash_cantidad(const hash_t *hash){
	return hash->cantidad;
}

void hash_destruir(hash_t *hash){
	for(size_t i = 0; i<hash->capacidad;i++){
		lista_t* lista = hash->tabla[i];
		lista_iter_t* lista_iter = lista_iter_crear(lista);
		while (!lista_iter_al_final(lista_iter)) {
			nodo_hash_t* act = lista_iter_ver_actual(lista_iter);
			if(hash->func_destr) hash->func_destr(act->dato);
			lista_iter_avanzar(lista_iter);
		}
		lista_iter_destruir(lista_iter);
		lista_destruir(lista, wrapper_nodo_hash_destruir);
	}
	free(hash->tabla);
	free(hash);
}



/* *****************************************************************
                         ITERADOR EXTERNO DE HASH
 * *****************************************************************/
struct hash_iter{
	const hash_t* hash;
	lista_iter_t*  iter_lista;
	size_t pos_actual;
};

hash_iter_t *hash_iter_crear(const hash_t *hash){
	if(!hash) return NULL;
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if(!iter) return NULL;
	iter->hash = hash;
	iter->iter_lista = NULL;
	for(size_t i = 0; i < iter->hash->capacidad;i++){
		if(!lista_esta_vacia(iter->hash->tabla[i])){
			iter->pos_actual = i;
			iter->iter_lista = lista_iter_crear(iter->hash->tabla[i]);
			break;
		}
	}
	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
	if(hash_iter_al_final(iter)) return false;
	lista_iter_avanzar(iter->iter_lista);
	if(!lista_iter_al_final(iter->iter_lista)){
		return true;
	}
	lista_iter_destruir(iter->iter_lista);
	iter->iter_lista = NULL;
	for(size_t i = iter->pos_actual +1; i<iter->hash->capacidad;i++){
		if(!lista_esta_vacia(iter->hash->tabla[i])){
			iter->pos_actual = i;
			iter->iter_lista = lista_iter_crear(iter->hash->tabla[i]);
			return true;
		}
	}
	return false;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){ 
	if(hash_iter_al_final(iter)) return NULL;
	nodo_hash_t* nodo_hash = lista_iter_ver_actual(iter->iter_lista);
	return nodo_hash->clave;
}


bool hash_iter_al_final(const hash_iter_t *iter){
	if(!iter->iter_lista) return true;
	for(size_t i = iter->pos_actual; i<iter->hash->capacidad;i++){
		if(!lista_esta_vacia(iter->hash->tabla[i])) return false;
	}
	return true;
}

void hash_iter_destruir(hash_iter_t* iter){
	lista_iter_destruir(iter->iter_lista);
	free(iter);
}
