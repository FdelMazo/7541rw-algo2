// Heap - Lucia Pardo 99999 - Federico del Mazo 100029
// Corrige Gonzalo

#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Funcion auxiliar comparar cadenas (llama a strcmp pero casteado)
int cmp_cadenas(const void *a, const void *b){
	return(strcmp((char*)a,(char*)b));
}

//Funcion auxiliar para comparar malloc
//Como va a ser usada solo para la prueba de destruir, devuelve solo -1 para encolar sin problemas
int cmp_malloc(const void *a, const void *b){
	return -1;
}

/* ******************************************************************
 *                        PRUEBAS
 * *****************************************************************/

void pruebas_basicas(){
	heap_t* heap = heap_crear(cmp_cadenas);
	
    printf("\n ~~~ PRUEBAS BASICAS ~~~\n");

	char *clave1 = "10";
    char *clave2 = "15";
    char *clave3 = "20";
	
	print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1); 	
    print_test("Prueba heap ver max devuelve clave1", heap_ver_max(heap) == clave1);
    
    print_test("Prueba heap encolar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
                  
    print_test("Prueba heap encolar clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
	print_test("Prueba heap ver max devuelve clave3", heap_ver_max(heap) == clave3);

	print_test("Prueba heap desencolar clave3", heap_desencolar(heap) == clave3);
	print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap)==2);
    print_test("Prueba heap ver max devuelve clave2", heap_ver_max(heap) == clave2);
    
    heap_destruir(heap, NULL);
}	

void pruebas_vacio(){
	heap_t* heap = heap_crear(cmp_cadenas);
	
    printf("\n ~~~ PRUEBAS VACIO ~~~\n");
	char *clave1 = "10";

    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    print_test("Prueba heap vacio la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap vacio desencolar un elemento da NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba heap vacio ver max da NULL", heap_ver_max(heap) == NULL);

	print_test("Inserto y elimino para correr las mismas pruebas", true);
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));
	print_test("Prueba heap desencolar clave1", heap_desencolar(heap) == clave1);

    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
	print_test("Prueba heap vacio la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap vacio desencolar un elemento da NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba heap vacio ver max un da NULL", heap_ver_max(heap) == NULL);

    heap_destruir(heap, NULL);
}
	
void pruebas_destruir(){	
	heap_t* heap = heap_crear(cmp_malloc);

    printf("\n ~~~ PRUEBAS DESTRUIR ~~~\n");
   	void** clave = malloc(sizeof(char*));
   
	print_test("Prueba heap encolar clave, con dato malloc", heap_encolar(heap, clave));
   
    heap_destruir(heap, free);
   	print_test("Prueba heap destruir, con free", true);
}

void pruebas_volumen(size_t largo){
	heap_t* heap = heap_crear(cmp_cadenas);
    //Modificacion de prueba_hash_volumen de la catedra
    printf("\n ~~~ PRUEBAS VOLUMEN ~~~\n");
    
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        ok = heap_encolar(heap, claves[i]);
        if (!ok) break;
    }

	print_test("Prueba heap ver max es el elemento mas grande", heap_ver_max(heap)==claves[largo-1]);
    print_test("Prueba heap almacenar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);

    for (size_t i = largo; i > 0; i--){
		heap_desencolar(heap);
    }

    print_test("Prueba heap borrar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
    free(claves);
}

void pruebas_heap_crear_arr(size_t largo){
   printf("\n ~~~ PRUEBAS CREAR HEAP DE ARREGLO ~~~\n");   

    char** arreglo = malloc(sizeof(char*)*largo);

    for (unsigned i = 0; i < largo; i++) {
        char arreglito[10];
        sprintf(arreglito, "%08d", i);
        arreglo[i] = arreglito;
    }

	heap_t* heap = heap_crear_arr((void*)arreglo, largo, cmp_cadenas);

	print_test("Prueba heap ver max es el elemento mas grande", heap_ver_max(heap)==arreglo[largo-1]);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    print_test("Prueba heap desencolo todo", true);
	
	for (size_t i = largo; i > 0; i--){
		heap_desencolar(heap);
    }

    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
    free(arreglo);
}

void pruebas_heap_sort(){
	printf("\n ~~~ PRUEBAS CREAR HEAP DE ARREGLO ~~~\n");
	
	char* cad1 = "a";
    char* cad2 = "d";
    char* cad3 = "b";
    char* cad4 = "c";
    
    void* arreglo[] = {cad1,cad2,cad3,cad4};
    heap_sort(arreglo,4,cmp_cadenas);
    
    for (int i=0;i<4;i++)
		printf("%s, ",(char*)arreglo[i]);
		
	print_test("Prueba heap heap_sort",true);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_heap_alumno() {
	pruebas_basicas();
	pruebas_vacio();
	pruebas_destruir();
    pruebas_volumen(1000);
    pruebas_heap_crear_arr(1000);
	pruebas_heap_sort();
}
