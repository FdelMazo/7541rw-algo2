#include <stdio.h>

int busqueda_binaria(int arreglo[], int inicio, int fin, int numero){
	if (inicio >= fin) return -1;
	int medio = inicio + ( (fin - inicio) / 2 ); //(leer: https://ai.googleblog.com/2006/06/extra-extra-read-all-about-it-nearly.html)
	int posicion;
	if (arreglo[medio] == numero)
			return medio;
	else if (arreglo[medio] < numero)	
		posicion = busqueda_binaria(arreglo, inicio, medio-1, numero);
	else
		posicion = busqueda_binaria(arreglo, medio+1, fin, numero);
	return posicion;
}

int main(){	
	int arreglo[10]= {1,2,4,8,16,22,34,75,89,100};
	printf("Arreglo: ");
	for(int i = 0; i < 10; i++) {
        printf("%d ", arreglo[i]);
    }
	printf("\n");
	
	int numero = 10; // Casos borde a probar: 1, 10, 100, 22 
	int posicion = busqueda_binaria(arreglo,0,9,numero);
	printf("Posicion de %d: %d\n", numero, posicion);
	return 0;
}

