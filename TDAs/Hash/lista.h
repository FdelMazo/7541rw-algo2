// Lista - 100029 - del Mazo, Federico
// Corrige Gonzalo

#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdio.h>

/* NODO */

/* Los nodos están planteados como un valor y una referencia al siguiente nodo */
struct nodo;
typedef struct nodo nodo_t;

// Crea un nodo.
// Post: Devuelve un nodo con el dato recibido y una referencia a NULL
nodo_t* nodo_crear(void* dato);

// Destruye un nodo
// Post: El nodo fue destruido y ya no es accesible
void nodo_destruir(nodo_t* nodo);

/* LISTA ENLAZADA */

/* La lista está planteada como una lista de nodos enlazados. */
struct lista;
typedef struct lista lista_t;

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t* lista, void (*destruir_dato)(void*));

// Devuelve verdadero o falso, según si la lista tiene o no elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t* lista);

// Agrega un nuevo elemento a la lista, en su primer posicion. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista al principio de esta
bool lista_insertar_primero(lista_t* lista, void* dato);

// Agrega un nuevo elemento a la lista, en su ultima posicion. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista al final de esta
bool lista_insertar_ultimo(lista_t* lista, void* dato);

// Obtiene el valor del primer elemento de la lista. Si la lista está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t* lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t* lista);

// Saca el primer elemento de la lista. Si la está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento, la lista contiene un elemento menos
void* lista_borrar_primero(lista_t* lista);

// Obtiene el largo de la lista
// Pre: la lista fue creada.
// Post: se devolvió el largo
size_t lista_largo(const lista_t* lista);

// Iterador Interno. Aplica la funcion visitar para saber si debe seguir iterando o no
// Pre: La lista fue creada, la funcion visitar devuelve booleano
// Post: Se itero y aplico la funcion
void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra);

/* ITERADOR EXTERNO */

/* El iterador externo esta pensado para solo usar las primitivas de la lista
 * Nunca puede acceder a la estructura interna */
struct lista_iter;
typedef struct lista_iter lista_iter_t;

// Crea el iterador externo de la lista enlazada
// Pre: La lista fue creada
// Post: Devuelve un iterador apuntando a la posicion 0 
lista_iter_t* lista_iter_crear(lista_t* lista);

// Avanza una posicion al iterador
// Pre: El iterador esta creado
// Post: El iterador avanzo una posicion, si no puede, devuelve false
bool lista_iter_avanzar(lista_iter_t* iter);

// Devuelve el dato en el que esta el iterador
// Pre: El iter fue creado
void* lista_iter_ver_actual(const lista_iter_t* iter);

// Devuelve si el iter esta en la ultima posicion o no
// Pre: El iter fue creado
bool lista_iter_al_final(const lista_iter_t* iter);

// Destruye el iterador
// Pre: El iter fue creado
// Post: El iterador fue destruido
void lista_iter_destruir(lista_iter_t* iter);

// Inserta un elemento en la posicion donde esta el iterador
// Pre: El iter fue creado
bool lista_iter_insertar(lista_iter_t* iter, void* dato);

// Borra el elemento en el que esta el iterador
// Pre: El iter fue creado
void* lista_iter_borrar(lista_iter_t* iter);

/* PRUEBAS */

// Realiza pruebas sobre la implementación del alumno.
// Las pruebas no pueden acceder a los miembros del struct lista.
void pruebas_lista_alumno(void);

#endif // LISTA_H
