// Arbol de Busqueda Binario - Lucia Pardo 99999 - Federico del Mazo 100029
// Corrige Gonzalo

#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                        PRUEBAS
 * *****************************************************************/
void pruebas_basicas(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
    printf("\n ~~~ PRUEBAS BASICAS ~~~\n");
    /* Creo este arbol
              10
           /     \
          05      20
					*/	
	char *clave1 = "10", *valor1 = "a";
    char *clave2 = "05", *valor2 = "b";
    char *clave3 = "20", *valor3 = "c";
	
    print_test("Prueba abb guardar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
                          
    print_test("Prueba abb guardar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
                          
    print_test("Prueba abb guardar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
	                      
	print_test("Prueba abb borrar clave2", abb_borrar(abb, clave2) == valor2);
	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb)==2);
    print_test("Prueba abb obtener clave2 es NULL", abb_obtener(abb, clave2) == NULL);
    print_test("Prueba abb pertenece clave2, es false", abb_pertenece(abb, clave2) == false);
  
    abb_destruir(abb);
}	

void pruebas_vacio(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
    printf("\n ~~~ PRUEBAS ARBOL VACIO ~~~\n");
	char *clave1 = "10", *valor1 = "a";


    print_test("Prueba abb vacio la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb vacio obtener un elemento da NULL", abb_obtener(abb,clave1) == NULL);
    print_test("Prueba abb vacio preguntar si pertenece da false", abb_pertenece(abb,clave1) == false);
    print_test("Prueba abb vacio borrar un elemento da NULL", abb_borrar(abb, clave1) == NULL);

	print_test("Inserto y elimino para correr las mismas pruebas", true);
    print_test("Prueba abb guardar clave1", abb_guardar(abb, clave1, valor1));
	print_test("Prueba abb borrar clave1", abb_borrar(abb, clave1) == valor1);

	print_test("Prueba abb vacio la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb vacio obtener un elemento da NULL", abb_obtener(abb,clave1) == NULL);
    print_test("Prueba abb vacio preguntar si pertenece da false", abb_pertenece(abb,clave1) == false);
    print_test("Prueba abb vacio borrar un elemento da NULL", abb_borrar(abb, clave1) == NULL);

    abb_destruir(abb);
}

void pruebas_reemplazar(){
	abb_t* abb = abb_crear(strcmp, NULL);

    printf("\n ~~~ PRUEBAS INSERTAR EN MISMA CLAVE ~~~\n");
	char *clave = "10"; 
	char *valor1 = "a", *valor2 = "b", *valor3 = "c";
	
    print_test("Prueba abb guardar clave, valor1", abb_guardar(abb, clave, valor1));
    print_test("Prueba abb obtener clave es valor1", abb_obtener(abb, clave) == valor1);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
    print_test("Prueba abb guardar clave, valor2", abb_guardar(abb, clave, valor2));
    print_test("Prueba abb obtener clave es valor2", abb_obtener(abb, clave) == valor2);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
    print_test("Prueba abb guardar clave, valor3", abb_guardar(abb, clave, valor3));
    print_test("Prueba abb obtener clave es valor3", abb_obtener(abb, clave) == valor3);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
   
    abb_destruir(abb);
}

void pruebas_reemplazar_destruir(){
	abb_t* abb = abb_crear(strcmp, free);

    printf("\n ~~~ PRUEBAS INSERTAR EN MISMA CLAVE Y DESTRUIR ~~~\n");
	char *clave = "10"; 
	void *valor1 = malloc(10), *valor2 = malloc(10), *valor3 = malloc(10);
	
    print_test("Prueba abb guardar clave, valor1", abb_guardar(abb, clave, valor1));
    print_test("Prueba abb obtener clave es valor1", abb_obtener(abb, clave) == valor1);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
    print_test("Prueba abb guardar clave, valor2", abb_guardar(abb, clave, valor2));
    print_test("Prueba abb obtener clave es valor2", abb_obtener(abb, clave) == valor2);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    
    print_test("Prueba abb guardar clave, valor3", abb_guardar(abb, clave, valor3));
    print_test("Prueba abb obtener clave es valor3", abb_obtener(abb, clave) == valor3);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
   
    abb_destruir(abb);
}

void pruebas_valor_null(){
	abb_t* abb = abb_crear(strcmp, NULL);

    printf("\n ~~~ PRUEBAS VALOR NULL ~~~\n");

    char *clave = "", *valor = NULL;

    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}
	
void pruebas_clave_vacia(){
	abb_t* abb = abb_crear(strcmp, NULL);

    printf("\n ~~~ PRUEBAS CLAVE VACIA ~~~\n");

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


void pruebas_borrar(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
    printf("\n ~~~ PRUEBAS BORRAR ~~~\n");
    /* Creo este arbol
              5
           /     \
          3       7
         /  \    /  \
       2    4   6    8 */
       
	char* valor = "";
    char *clave1 = "5";
    char *clave2 = "3";
    char *clave3 = "2"; 
    char *clave4 = "4"; 
    char *clave5 = "7"; 
    char *clave6 = "6"; 
    char *clave7 = "8"; 
   
	print_test("Prueba abb guardar clave1", abb_guardar(abb, clave1, valor));
	print_test("Prueba abb guardar clave2", abb_guardar(abb, clave2, valor));
	print_test("Prueba abb guardar clave3", abb_guardar(abb, clave3, valor));
	print_test("Prueba abb guardar clave4", abb_guardar(abb, clave4, valor));
	print_test("Prueba abb guardar clave5", abb_guardar(abb, clave5, valor));
	print_test("Prueba abb guardar clave6", abb_guardar(abb, clave6, valor));
	print_test("Prueba abb guardar clave7", abb_guardar(abb, clave7, valor));
	
	print_test("Prueba abb borrar clave3, HOJA", abb_borrar(abb, clave3) == valor);

	print_test("Prueba abb borrar clave2, UN HIJO", abb_borrar(abb, clave2) == valor);

	print_test("Prueba abb borrar clave1, DOS HIJOS", abb_borrar(abb, clave1) == valor);
    
    abb_destruir(abb);
}

void pruebas_destruir(){	
	abb_t* abb = abb_crear(strcmp, free);

    printf("\n ~~~ PRUEBAS DESTRUIR ~~~\n");
    char *clave1 = "5";
   	char* valor = malloc(sizeof(char*));
   
	print_test("Prueba abb guardar clave1, con dato malloc", abb_guardar(abb, clave1, valor));
   
    abb_destruir(abb);
   	print_test("Prueba abb destruir, con free", true);
}

//Modificacion de prueba_hash_volumen de la catedra
void pruebas_volumen(size_t largo){
	abb_t* abb = abb_crear(strcmp, free);
    
    printf("\n ~~~ PRUEBAS VOLUMEN ~~~\n");
    
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    print_test("Prueba abb almacenar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    free(claves);
}



/* ******************************************************************
 *                 PRUEBAS ITERADOR INTERNO
 * *****************************************************************/
//Funcion de prueba para ser llamada por in_order
//Imprime la clave y el valor recibidos
bool imprimir(const char* clave, void* valor, void* extra){
	printf("%s, ", clave);
	return true;
}

void pruebas_iter_interno(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
    printf("\n ~~~ PRUEBAS ITERADOR INTERNO ~~~\n");

	/* Creo este arbol
              14
           /     \
          10       16
         /  \    /  
       5    11  15   */
    char *clave1 = "14", *valor1="a" ;
    char *clave2 = "10", *valor2="b";
    char *clave3 = "05", *valor3="c"; 
    char *clave4 = "11", *valor4="d"; 
    char *clave5 = "16", *valor5="e"; 
    char *clave6 = "15", *valor6="f";

	abb_guardar(abb, clave1, valor1);
	abb_guardar(abb, clave2, valor2);
	abb_guardar(abb, clave3, valor3);
	abb_guardar(abb, clave4, valor4);
	abb_guardar(abb, clave5, valor5);
	abb_guardar(abb, clave6, valor6);

	printf("Imprimo in_order con el iterador \n");
	printf("Respuesta esperada: 5 10 11 14 15 16 \n");
	abb_in_order(abb, imprimir, NULL);
	printf("\n");
	abb_destruir(abb);
}


/* ******************************************************************
 *                 PRUEBAS ITERADOR EXTERNO
 * *****************************************************************/
void pruebas_iter_basicas(){
	abb_t* abb = abb_crear(strcmp, NULL);
	
    printf("\n ~~~ PRUEBAS ITERADOR EXTERNO BASICAS ~~~\n");

	/* Creo este arbol
              14
           /     \
          10       16
         /  \    /  
       5    11  15   */
    char *clave1 = "14", *valor1="a" ;
    char *clave2 = "10", *valor2="b";
    char *clave3 = "05", *valor3="c"; 
    char *clave4 = "11", *valor4="d"; 
    char *clave5 = "16", *valor5="e"; 
    char *clave6 = "15", *valor6="f"; 
         
	abb_guardar(abb, clave1, valor1);
	abb_guardar(abb, clave2, valor2);
	abb_guardar(abb, clave3, valor3);
	abb_guardar(abb, clave4, valor4);
	abb_guardar(abb, clave5, valor5);
	abb_guardar(abb, clave6, valor6);
	
	abb_iter_t* iter = abb_iter_in_crear(abb);
		
	print_test("Prueba abb iter Verifico mi actual", strcmp(abb_iter_in_ver_actual(iter),clave3)==0);
	print_test("Prueba abb iter Avanzo el iterador",abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter Verifico que iterador no esta al final",!abb_iter_in_al_final(iter));
	print_test("Prueba abb iter Verifico mi actual", strcmp(abb_iter_in_ver_actual(iter),clave2)==0);
	print_test("Prueba abb iter Avanzo el iterador",abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter Verifico mi actual", strcmp(abb_iter_in_ver_actual(iter),clave4)==0);
	print_test("Prueba abb iter Avanzo el iterador",abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter Verifico mi actual", strcmp(abb_iter_in_ver_actual(iter),clave1)==0);
	print_test("Prueba abb iter Avanzo el iterador",abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter Verifico mi actual", strcmp(abb_iter_in_ver_actual(iter),clave6)==0);
	print_test("Prueba abb iter Avanzo el iterador",abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter Verifico mi actual", strcmp(abb_iter_in_ver_actual(iter),clave5)==0);
	print_test("Prueba abb iter Avanzo a NULL el iterador",abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter El iterador esta al final",abb_iter_in_al_final(iter));
	
	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

void pruebas_iter_vacio(){
	abb_t* abb = abb_crear(NULL, NULL);
	
    printf("\n ~~~ PRUEBAS ITERADOR EXTERNO ARBOL VACIO ~~~\n");

	abb_iter_t* iter = abb_iter_in_crear(abb);
	
	print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
	print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
	print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

//Modificacion de prueba_hash_iterar_volumen de la catedra
void pruebas_iter_volumen(size_t largo){
    abb_t* abb = abb_crear(strcmp, NULL);

    printf("\n ~~~ PRUEBAS ITERADOR EXTERNO VOLUMEN ~~~\n");


    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}
	
/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_abb_alumno() {
	pruebas_basicas();
	pruebas_vacio();
	pruebas_reemplazar();
	pruebas_reemplazar_destruir();
	pruebas_valor_null();
	pruebas_clave_vacia();
	pruebas_borrar();
	pruebas_destruir();
    pruebas_volumen(1000);
	
	pruebas_iter_interno();

	pruebas_iter_basicas();
	pruebas_iter_vacio();
	pruebas_iter_volumen(1000);
}
