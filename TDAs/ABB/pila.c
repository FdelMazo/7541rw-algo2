// Pila - 100029 - del Mazo, Federico
// Corrige Gonzalo

#include "pila.h"
#include <stdlib.h>
#define CAP_INICIAL 10
#define COEF_AGRANDAR 2
#define COEF_ACHICAR 1/4

/*Declaracion de la funcion auxiliar para redimensionar la capacidad*/
bool pila_redimensionar(pila_t* pila, size_t coef);

/* Definición del struct pila proporcionado por la cátedra.*/
struct pila{
	void** datos;
	size_t cantidad;  // Cantidad de elementos almacenados.
	size_t capacidad;  // Capacidad del arreglo 'datos'.
};

pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if (!pila) return NULL;
	pila->datos = malloc(CAP_INICIAL * sizeof(pila->datos));
	if (pila->datos == NULL){
		free(pila);
		return NULL;
	}
	pila->capacidad = CAP_INICIAL;
	pila->cantidad = 0;
	return pila;
}

void pila_destruir(pila_t* pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t* pila){
	return !pila->cantidad;
}

bool pila_apilar(pila_t* pila, void* valor){
	if (pila->cantidad >= pila->capacidad)
		if (!(pila_redimensionar(pila, pila->capacidad * COEF_AGRANDAR))) return false;
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true; 
}

void* pila_ver_tope(const pila_t* pila){
	if (pila_esta_vacia(pila)) return NULL;
	return pila->datos[pila->cantidad -1];
}

void* pila_desapilar(pila_t* pila){
	if (pila_esta_vacia(pila)) return NULL;
	if (pila->cantidad <= pila->capacidad * COEF_ACHICAR)
		if (!(pila_redimensionar(pila, pila->capacidad * COEF_ACHICAR))) return NULL;
	void* tope = pila_ver_tope(pila);
	pila->cantidad--;
	return tope; 
}	
	
bool pila_redimensionar(pila_t* pila, size_t nueva_cap){
	//if (nueva_cap *sizeof(pila->datos) <= pila->capacidad) return false;
	void* temp = realloc(pila->datos, nueva_cap *sizeof(pila->datos));
	if (!temp) return false;
	pila->datos = temp;
	pila->capacidad = nueva_cap;
	return true;
}

size_t pila_ver_cantidad(pila_t* pila){
	return pila->cantidad;
}
size_t pila_ver_capacidad(pila_t* pila){
	return pila->capacidad;
}
