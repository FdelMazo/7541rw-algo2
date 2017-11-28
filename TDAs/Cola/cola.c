// Cola - 100029 - del Mazo, Federico
// Corrige Gonzalo

#include "cola.h"
#include <stdlib.h>

/* NODO
 * Structure privada para que use la cola. 
 * Nota: Deberia estar declarado en un hipotetico "nodo.h"*/
struct nodo;
typedef struct nodo nodo_t;
nodo_t* nodo_crear(void* dato);

struct nodo{
	void* dato;
	nodo_t* prox;
};

//Crea un nodo con referencia al siguiente nula
nodo_t* nodo_crear(void* dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}

/* COLA */

struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
};

cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));
	if (!cola) return NULL;
	cola->primero = NULL;
	cola->ultimo = NULL;
	return cola;
}

void cola_destruir(cola_t* cola, void destruir_dato(void*)){
	while(!(cola_esta_vacia(cola))){
		if (destruir_dato)
			destruir_dato(cola->primero->dato);
		cola_desencolar(cola);
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return (!(cola->primero) && !(cola->ultimo));
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nodo = nodo_crear(valor);
	if (!nodo) return false;
	if (cola_esta_vacia(cola)){
		cola->primero = nodo;
		cola->ultimo = nodo;
		return true;
	}
	cola->ultimo->prox = nodo;
	cola->ultimo = nodo;
	return true; 
}

void* cola_ver_primero(const cola_t *cola){
	if (cola_esta_vacia(cola)) return NULL;
	return (cola->primero->dato);
}

void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola)) return NULL;
	void* dato_primero = cola_ver_primero(cola);
	nodo_t* nodo_desencolado = cola->primero;
	if (cola->primero == cola->ultimo){
		cola->primero = NULL;
		cola->ultimo = NULL;
		free(nodo_desencolado);
		return dato_primero;
	}
	cola->primero = cola->primero->prox;
	free(nodo_desencolado);
	return dato_primero; 
}
