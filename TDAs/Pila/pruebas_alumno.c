//Pila - 100029 - del Mazo, Federico

#include "pila.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#define PRUEBA_GRANDE 100
#define CAP_INICIAL 10

/*Declaracion de 2 funciones auxiliares. NOTA: Estas funciones deberían estar declaradas en pila.h
 * pero al no entregar ese archivo tuve que dejarlas aca. Arme estas funciones porque
 * para imprimir cantidad y capacidad no debería entrar a los miembros de una estructura directamente*/
size_t pila_ver_cantidad(pila_t *pila);
size_t pila_ver_capacidad(pila_t *pila);

void pruebas_basicas();	
void pruebas_redimension();
void pruebas_borde();
	
void pruebas_pila_alumno() {
	pruebas_basicas();
	pruebas_redimension();
	pruebas_borde();
}
void pruebas_basicas(){
	printf("\n BASICO - CREAR, APILAR, DESAPILAR, DESTRUIR \n"); 
	
	pila_t* ejemplo_1 = pila_crear();
	int elem_int = 1;
	print_test("Creo una pila",true);
	print_test("La pila esta vacia", pila_esta_vacia(ejemplo_1));
	print_test("Apilo un entero ('1')", pila_apilar(ejemplo_1, &elem_int));
	print_test("La pila NO esta vacia", !pila_esta_vacia(ejemplo_1));
	print_test("Ver_Tope devuelve el entero", pila_ver_tope(ejemplo_1) == &elem_int);
	print_test("Desapilar tambien devuelve el entero", pila_desapilar(ejemplo_1) == &elem_int);
	print_test("La pila esta nuevamente vacia", pila_esta_vacia(ejemplo_1));
	pila_destruir(ejemplo_1);
	print_test("Destruyo la pila", true);
}

void pruebas_redimension(){
	printf("\n CAPACIDAD Y REDIMENSIONES \n");
	
	pila_t* ejemplo_2 = pila_crear();
	int elem_int = 1;
	print_test("Creo otra pila",true);
	print_test("Apilo un entero", pila_apilar(ejemplo_2, &elem_int));
	print_test("Capacidad de la pila es COEF_INICIAL", pila_ver_capacidad(ejemplo_2) == CAP_INICIAL);
	print_test("Cantidad de la pila es 1", pila_ver_cantidad(ejemplo_2) == 1);
	printf("Apilo y desapilo 100 elementos para comprobar que no se 'rompa' (Supero la capacidad inicial) \n");
	int vector[PRUEBA_GRANDE];
	for(int i=0; i<PRUEBA_GRANDE; i++)
		pila_apilar(ejemplo_2, &vector[i]);
	for(int i=0; i<PRUEBA_GRANDE; i++)
		pila_desapilar(ejemplo_2);
	pila_destruir(ejemplo_2);
	print_test("Destruyo la pila", true);
}

void pruebas_borde(){	
	printf("\n CASOS BORDE \n");
	
	pila_t* ejemplo_3 = pila_crear();
	int elem_int = 1;
	print_test("Creo una ultima (tercer) pila",true);
	print_test("Ver_tope en una pila vacia devuelve NULL", pila_ver_tope(ejemplo_3) == NULL);
	print_test("Desapilar tambien devuelve NULL", pila_desapilar(ejemplo_3) == NULL);
	printf("Apilo y desapilo para correr las mismas pruebas \n");
	pila_apilar(ejemplo_3, &elem_int);
	pila_desapilar(ejemplo_3);
	print_test("Ver_tope en una pila vacia sigue devolviendo NULL", pila_ver_tope(ejemplo_3) == NULL);
	print_test("Desapilar tambien sigue devolviendo NULL", pila_desapilar(ejemplo_3) == NULL);
	pila_destruir(ejemplo_3);
	print_test("Destruyo la pila", true);
}
