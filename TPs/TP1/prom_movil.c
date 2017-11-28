// Federico del Mazo - 100029
// TP1 - PROM MOVIL CON PRUEBAS
// Corrige Gonzalo

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* *****************************************************************
                         FUNCIONES AUXILIARES
 * *****************************************************************/
//Funcion que imprime arreglo de doubles
void imprimir_arreglo(double* pm){
	printf("ARREGLO: ");
	for(size_t i=0;pm[i];i++)
		printf("%.2f ", pm[i]);
	printf("\n");
}

//Funcion auxiliar llamada por la solucion trivial
//Recibe el arreglo y las posiciones desde donde calcular el promedio
//Devuelve el promedio de la sumatoria de arreglos
double promedio_arreglo(int* arreglo, size_t ini, size_t fin){
	double sum = 0;
	size_t largo = fin-ini+1;
	for(size_t i = ini; i<=fin;i++)
		sum += arreglo[i];
	return sum / (double) largo;
}

/* *****************************************************************
                         PROMEDIO MOVIL
 * *****************************************************************/
double* obtener_promedio_movil_trivial(int* arreglo, size_t n, size_t k){
	double* pm = malloc(sizeof(long double) * n);
	if(!pm) return NULL;
	for(size_t i=0; i<n;i++){
		if(k>i)//Primeros
			if(i+k>=n)
				pm[i] = promedio_arreglo(arreglo, 0, n-1);
			else
				pm[i] = promedio_arreglo(arreglo, 0, i+k);
		else if(i+k>=n)//Ultimos
			pm[i] = promedio_arreglo(arreglo, i-k, n-1);
		else//Medio
			pm[i] = promedio_arreglo(arreglo, i-k, i+k);
	}
	return pm;
}		
		
double* obtener_promedio_movil_efectivo(int* arreglo, size_t n, size_t k){
	double* pm = malloc(sizeof(long double) * n);
	if(!pm) return NULL;
	double sumatoria = 0;
	double ultimo = 0;
	lista_t* lista = lista_crear();
	if(k>=n) k = n-1;
	for(size_t i=0, j=0; i<n+k+1;i++){
		if(!lista_esta_vacia(lista)) ultimo = *(int*)lista_ver_ultimo(lista);		
		if(ultimo == arreglo[j+k]){
			if(lista_largo(lista) > (2*k+1)){
				sumatoria-= *(int*)lista_borrar_primero(lista);
			}
			pm[j] = sumatoria / (int) lista_largo(lista);
			j++;
		}
		if(ultimo == arreglo[n-1]){
			if(k!=n-1)
				sumatoria-= *(int*)lista_borrar_primero(lista);
			pm[j] = sumatoria / (int) lista_largo(lista);
			j++;
		}
		else{
			lista_insertar_ultimo(lista, &arreglo[i]);
			sumatoria+=  *(int*)lista_ver_ultimo(lista);
		}
	}
	if(pm[n]) pm[n] = 0;
	lista_destruir(lista, NULL);
	return pm;
}

/* *****************************************************************
                         PRUEBAS Y MAIN
 * *****************************************************************/
//Pruebas basicas
//El boleano determina la solucion a aplicar (true = efectiva, false = trivial)
void pruebas_basicas(bool tipo){
	int arreglo[6] = {1,3,12,6,17,9};
	printf("EL ARREGLO DE PRUEBAS ES 1, 3, 12, 6, 17, 9\n");
	double* pm1;
	double* pm2;
	
	printf("\n K = 1 - ESTO DEBERIA SER: 2, 5.3, 7, 11.6, 10.6, 13 \n");
	if(tipo == false)
		pm1 = obtener_promedio_movil_trivial(arreglo, 6,1);
	else
		pm1 = obtener_promedio_movil_efectivo(arreglo, 6,1);
	imprimir_arreglo(pm1);
	free(pm1);
	
	printf("\n K = 2 - ESTO DEBERIA SER: 5.3, 5.5, 7.8, 9.4, 11, 10.6 \n");
	if(tipo == false)
		pm2 = obtener_promedio_movil_trivial(arreglo, 6,2);
	else
		pm2 = obtener_promedio_movil_efectivo(arreglo, 6,2);
	imprimir_arreglo(pm2);
	free(pm2);
}

//Pruebas borde: K = 0 y K > Largo
//El boleano determina la solucion a aplicar (true = efectiva, false = trivial)
void pruebas_borde(bool tipo){
	int arreglo[6] = {1,3,12,6,17,9};
	printf("\n EL ARREGLO DE PRUEBAS ES 1, 3, 12, 6, 17, 9\n");
	double* pm1;
	double* pm2;
	
	printf("\n K = 0 - ESTO DEBERIA SER: 1, 3, 12, 6, 17, 9 \n");
	if(tipo == false)
		pm1 = obtener_promedio_movil_trivial(arreglo, 6,0);
	else
		pm1 = obtener_promedio_movil_efectivo(arreglo, 6,0);
	imprimir_arreglo(pm1);
	free(pm1);
	
	printf("\n K > Largo - ESTO DEBERIA SER: TODO 8 \n");
	if(tipo == false)
		pm2 = obtener_promedio_movil_trivial(arreglo, 6,10);
	else
		pm2 = obtener_promedio_movil_efectivo(arreglo, 6,10);
	imprimir_arreglo(pm2);
	free(pm2);
}

int main(){
	printf("\n ~~~ PRUEBAS SOLUCION TRIVIAL ~~~ \n");
	pruebas_basicas(false);
	pruebas_borde(false);
	printf("\n ~~~ PRUEBAS SOLUCION EFECTIVA ~~~ \n");
	pruebas_basicas(true);
	pruebas_borde(true);
	return 0;
}
