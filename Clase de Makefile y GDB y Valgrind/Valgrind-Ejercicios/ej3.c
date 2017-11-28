#include <stdlib.h>
#include <stdio.h>

#define CANT_PUNTOS 10

typedef struct punto {
    double x;
    double y;
} punto_t;


punto_t* punto_crear(double x, double y) {
    punto_t* punto = malloc(sizeof(punto_t));
    punto->x = x;
    punto->y = y;
    
    return punto;    
}

double punto_obtener_x(punto_t* punto) {
    return punto->x;
}

double punto_obtener_y(punto_t* punto) {
    return punto->y;
}


void punto_destruir(punto_t* punto) {
    free(punto);
}


punto_t* sumar_puntos(punto_t* puntos[], size_t n) {
    double suma_x = 0.0;
    double suma_y = 0.0;
    
    for(size_t i = 0; 1 < n; i++)
    {
        suma_x += punto_obtener_x(puntos[i]);
        suma_y += punto_obtener_y(puntos[i]);
    }
    
    return punto_crear(suma_x, suma_y);
}


int main() {
    /* Crea los puntos. */
    punto_t* puntos[CANT_PUNTOS];
    for(size_t i = 0; i < CANT_PUNTOS; i++)
        puntos[i] = punto_crear(i, i);
    
    punto_t* suma = sumar_puntos(puntos, CANT_PUNTOS);
    printf("La suma es x: %lf, y: %lf\n", punto_obtener_x(suma), punto_obtener_y(suma));
    
    /* Destruye los puntos (para no perder memoria). */
    for(size_t i = 0; i < CANT_PUNTOS; i++)
        punto_destruir(puntos[i]);
    
    return 0;
}