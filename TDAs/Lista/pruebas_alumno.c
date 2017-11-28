// Lista - 100029 - del Mazo, Federico
// Corrige Gonzalo

#include "lista.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#define PRUEBA_GRANDE 100
#define CAP_PRUEBA 30

//Declaraciones de pruebas
void pruebas_basicas();
void pruebas_borde();
void pruebas_limite();
void pruebas_destruir();
void pruebas_iterador_int();
void pruebas_iterador_ext_vacia();
void pruebas_iterador_ext_lista();

/* Declaracion y definicion de la funcion que usaran las pruebas de iterador */
bool imprimir_items(void* elemento, void* extra);
bool imprimir_primer_item(void* elemento, void* extra);

bool imprimir_items(void* elemento, void* extra){
	int *contador = extra;
    printf("%d. %d\n", ++(*contador), *(int*) elemento);
		return true;
}
bool imprimir_primer_item(void* elemento, void* extra){
	printf("Primer Item: %d \n", *(int*) elemento);
		return false;
}

void pruebas_lista_alumno() {
	pruebas_basicas();
	pruebas_borde();
	pruebas_limite();
	pruebas_destruir();
	pruebas_iterador_int();
	pruebas_iterador_ext_vacia();
	pruebas_iterador_ext_lista();
}

void pruebas_basicas(){
	printf("\n BASICO - CREAR, INSERTAR, ELIMINAR, DESTRUIR \n"); 
	int elem_int1 = 1;
	int elem_int2 = 2;
	lista_t* lista = lista_crear();
	print_test("Creo una lista",true);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("El largo es 0", lista_largo(lista) == 0);
	print_test("Inserto un entero al principio ('1')", lista_insertar_primero(lista, &elem_int1));
	print_test("Inserto un entero al final ('2')", lista_insertar_ultimo(lista, &elem_int2));
	print_test("La lista NO esta vacia", !lista_esta_vacia(lista));
	print_test("El largo es 2", lista_largo(lista) == 2);
	print_test("Ver primero devuelve el 1", lista_ver_primero(lista) == &elem_int1);
	print_test("Ver ultimo devuelve el 2", lista_ver_ultimo(lista) == &elem_int2);
	print_test("Borrar primero devuelve el 1", lista_borrar_primero(lista) == &elem_int1);
	print_test("Ver primero devuelve el 2", lista_ver_primero(lista) == &elem_int2);
	print_test("Borrar primero devuelve el 2", lista_borrar_primero(lista) == &elem_int2);
	print_test("La lista nuevamente esta vacia", lista_esta_vacia(lista));
	print_test("El largo es nuevamente 0", lista_largo(lista) == 0);
	lista_destruir(lista,NULL);
	print_test("Destruyo la lista (normalmente)",true);
}	

void pruebas_borde(){
	printf("\n CASOS BORDE \n"); 
	lista_t* lista = lista_crear();
	int elem_int1 = 1;
	print_test("Creo una lista",true);
	print_test("Ver primero es invalida", !(lista_ver_primero(lista)));
	print_test("Ver ultimo es invalida", !(lista_ver_ultimo(lista)));
	print_test("Borrar tambien es invalida", !(lista_borrar_primero(lista)));
	lista_insertar_primero(lista, &elem_int1);
	lista_borrar_primero(lista);
	print_test("Inserto y elimino para correr las mismas pruebas", true);
	print_test("(Nuevamente) Ver primero es invalida", !(lista_ver_primero(lista)));
	print_test("(Nuevamente) Ver ultimo es invalida", !(lista_ver_ultimo(lista)));
	print_test("(Nuevamente) Borrar tambien es invalida", !(lista_borrar_primero(lista)));
	lista_destruir(lista,NULL);
	print_test("Destruyo la lista (normalmente)",true);
}

void pruebas_limite(){
	printf("\n PRUEBAS LIMITE \n");
	lista_t* lista = lista_crear();
	print_test("Creo una lista",true);
	printf("Inserto y elimino 100 elementos para comprobar que no se 'rompa' \n");
	int vector[PRUEBA_GRANDE];
	for(int i=0; i<PRUEBA_GRANDE; i++)
		lista_insertar_primero(lista, &vector[i]);
	print_test("El largo es 100", lista_largo(lista) == PRUEBA_GRANDE);
	for(int i=0; i<PRUEBA_GRANDE; i++)
		lista_borrar_primero(lista);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	lista_destruir(lista,NULL);
	print_test("Destruyo la lista (normalmente)",true);
}

void pruebas_destruir(){	
	printf("\n FUNCION DESTRUIR \n");
	lista_t* lista = lista_crear();
	print_test("Creo una lista",true);
	for(int i=0; i<PRUEBA_GRANDE; i++){
		void* malloqueado = malloc(CAP_PRUEBA);
		lista_insertar_primero(lista,malloqueado);
	}
	print_test("Anido: Inserto varios 'malloqueados' a la lista normal", true);
	print_test("Uso typedef para un puntero a funcion con la huella de free",true);
	typedef void (*puntero_a_funcion)(void*); 
	print_test("Defino el puntero a funcion free_p que apunta a la funcion free",true);
	puntero_a_funcion free_p = &free;
	print_test("Destruyo la lista pasando el puntero a funcion para destruir todos los 'malloqueados' internos",true);
	lista_destruir(lista, free_p);
}

void pruebas_iterador_int(){
	printf("\n PRUEBAS ITERADOR INTERNO \n");
	lista_t* lista = lista_crear();
	int elem_1 = 1;
	int elem_2 = 2;
	int elem_3 = 3;
	lista_insertar_ultimo(lista, &elem_1);
	lista_insertar_ultimo(lista, &elem_2);
	lista_insertar_ultimo(lista, &elem_3);
	print_test("Inserto 3 elementos",true);
	printf("Imprimo el primer elemento \n");
    lista_iterar(lista, imprimir_primer_item, NULL);
	printf("Imprimo los 3 elementos, con el contador extra \n");
	int cont = 0;
	lista_iterar(lista, imprimir_items, &cont);
	print_test("Destruyo la lista (normalmente)",true);
	lista_destruir(lista,NULL);
}

void pruebas_iterador_ext_vacia(){
	printf("\n PRUEBAS ITERADOR EXTERNO CREANDO UNA LISTA VACIA\n");
	lista_t* lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	int elem_1 = 1;
	int elem_medio = 9;
	int elem_2 = 2;
	int elem_3 = 3;
	int elem_4 = 4;
	print_test("Creo una lista y un iterador externo", true);
	print_test("Inserto un 3 al principio", lista_iter_insertar(iter, &elem_3));
	print_test("El primer elemento de mi lista es el 3", lista_ver_primero(lista) == &elem_3);
	print_test("Inserto un 2 al principio", lista_iter_insertar(iter, &elem_2));
	print_test("Inserto un 1 al principio", lista_iter_insertar(iter, &elem_1));
	print_test("Avanzo uno el iterador", lista_iter_avanzar(iter));
	print_test("El iter esta en el 2", lista_iter_ver_actual(iter) == &elem_2);
	print_test("Inserto un elem intermedio entre el 1 y el 2", lista_iter_insertar(iter, &elem_medio));
	print_test("El primer elemento de mi lista es el 1", lista_ver_primero(lista) == &elem_1);
	print_test("Avanzo uno el iterador (desde mi intermedio a 2)", lista_iter_avanzar(iter));
	print_test("Elimino el 2, dejo el actual en 3", lista_iter_borrar(iter) == &elem_2);
	print_test("Avanzo uno el iterador (de 3 a NULL)", lista_iter_avanzar(iter));
	print_test("Estoy en el final", lista_iter_al_final(iter));
	print_test("Inserto un 4 al final", lista_iter_insertar(iter, &elem_4));
	lista_destruir(lista,NULL);
	lista_iter_destruir(iter);
	print_test("Destruyo mi iter y mi lista", true);
}

void pruebas_iterador_ext_lista(){
	printf("\n PRUEBAS ITERADOR EXTERNO CON UNA LISTA CREADA\n");
	int elem_1 = 1;
	int elem_2 = 2;
	int elem_3 = 3;
	lista_t* lista = lista_crear();
	lista_insertar_primero(lista, &elem_1);
	lista_insertar_ultimo(lista, &elem_2);
	lista_insertar_ultimo(lista, &elem_3);
	print_test("Creo una lista y le inserto tres elementos",true);
	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Creo un iterador externo", true);
	print_test("Elimino el primer elemento", lista_iter_borrar(iter) == &elem_1);
	print_test("El primer elemento de mi lista es el 2", lista_ver_primero(lista) == &elem_2);
	lista_iter_avanzar(iter);
	print_test("Avanzo el iterador y elimino el ultimo elemento", lista_iter_borrar(iter) == &elem_3);
	print_test("El ultimo elemento de mi lista es el 2", lista_ver_ultimo(lista) == &elem_2);
	lista_destruir(lista,NULL);
	lista_iter_destruir(iter);
	print_test("Destruyo mi iter y mi lista", true);
}
