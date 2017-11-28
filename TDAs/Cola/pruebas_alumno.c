// Cola - 100029 - del Mazo, Federico
// Corrige Gonzalo

#include "cola.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#define PRUEBA_GRANDE 100
#define CAP_PRUEBA 30

//Declaraciones de pruebas. Deberian estar en un .h
void pruebas_basicas();
void pruebas_borde();
void pruebas_caso_grande();
void pruebas_destruir();

void pruebas_cola_alumno() {
	pruebas_basicas();
	pruebas_borde();
	pruebas_caso_grande();
	pruebas_destruir();
}

void pruebas_basicas(){
	printf("\n EJEMPLO_1: BASICO - CREAR, ENCOLAR, DESENCOLAR, DESTRUIR \n"); 
	
	int elem_int1 = 1;
	int elem_int2 = 2;
	cola_t* ejemplo_1 = cola_crear();
	print_test("Creo una cola",true);
	print_test("La cola esta vacia", cola_esta_vacia(ejemplo_1));
	print_test("Encolo un entero ('1')", cola_encolar(ejemplo_1, &elem_int1));
	print_test("Encolo un entero ('2')", cola_encolar(ejemplo_1, &elem_int2));
	print_test("La cola NO esta vacia", !cola_esta_vacia(ejemplo_1));
	print_test("Ver primero devuelve el 1", cola_ver_primero(ejemplo_1) == &elem_int1);
	print_test("Desencolar devuelve el 1", cola_desencolar(ejemplo_1) == &elem_int1);
	print_test("Desencolar devuelve el 2", cola_desencolar(ejemplo_1) == &elem_int2);
	print_test("La cola nuevamente esta vacia", cola_esta_vacia(ejemplo_1));
	cola_destruir(ejemplo_1,NULL);
	print_test("Destruyo la cola (normalmente)",true);
}	

void pruebas_borde(){
	printf("\n EJEMPLO_2: CASOS BORDE \n"); 
	cola_t* ejemplo_2 = cola_crear();
	int elem_int1 = 1;
	print_test("Creo una cola",true);
	print_test("Ver tope es invalida", !(cola_ver_primero(ejemplo_2)));
	print_test("Desencolar tambien es invalida", !(cola_desencolar(ejemplo_2)));
	cola_encolar(ejemplo_2, &elem_int1);
	cola_desencolar(ejemplo_2);
	print_test("Encolo y desencolo para correr las mismas pruebas", true);
	print_test("(Nuevamente) Ver tope es invalida", !(cola_ver_primero(ejemplo_2)));
	print_test("(Nuevamente) Desencolar tambien es invalida", !(cola_desencolar(ejemplo_2)));
	cola_destruir(ejemplo_2,NULL);
	print_test("Destruyo la cola (normalmente)",true);
}

void pruebas_caso_grande(){
	printf("\n EJEMPLO_3: PRUEBAS GRANDES \n");
	cola_t* ejemplo_3 = cola_crear();
	print_test("Creo una cola",true);
	printf("Encolo y desencolo 100 elementos para comprobar que no se 'rompa' \n");
	int vector[PRUEBA_GRANDE];
	for(int i=0; i<PRUEBA_GRANDE; i++)
		cola_encolar(ejemplo_3, &vector[i]);
	for(int i=0; i<PRUEBA_GRANDE; i++)
		cola_desencolar(ejemplo_3);
	cola_destruir(ejemplo_3,NULL);
	print_test("Destruyo la cola (normalmente)",true);
}
	
void pruebas_destruir(){	
	printf("\n EJEMPLO_4: FUNCION DESTRUIR \n");
	cola_t* ejemplo_4 = cola_crear();
	void* malloqueado = malloc(CAP_PRUEBA); 
	print_test("Creo una cola y un puntero generico con malloc",true);
	print_test("Anido: Encolo el malloqueado a la cola normal",cola_encolar(ejemplo_4,malloqueado));
	print_test("Uso typedef para un puntero a funcion con la huella de free",true);
	typedef void (*puntero_a_funcion)(void*); 
	print_test("Defino el puntero a funcion free_p que apunta a la funcion free",true);
	puntero_a_funcion free_p = &free;
	print_test("Destruyo la cola pasando el puntero a funcion para destruir el malloqueado interno",true);
	cola_destruir(ejemplo_4, free_p);
}

