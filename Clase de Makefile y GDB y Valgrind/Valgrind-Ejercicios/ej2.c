#include <stdlib.h>
#include <stdio.h>

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

punto_t* punto_sumar(punto_t* p1, punto_t* p2) {
    punto_t* suma = punto_crear(p1->x + p2->x, p1->y + p2->y);
    punto_destruir(p1);
    punto_destruir(p2);
    
    return suma;
}


int main() {
    punto_t* p1 = punto_crear(3.2, 4.1);
    punto_t* p2 = punto_crear(2.1, 0.4);
    printf("Punto 1 es x: %lf, y: %lf\n", punto_obtener_x(p1), punto_obtener_y(p1));
    printf("Punto 2 es x: %lf, y: %lf\n", punto_obtener_x(p2), punto_obtener_y(p2));
    
    punto_t* suma = punto_sumar(p1, p2);
    printf("La suma es x: %lf, y: %lf\n", punto_obtener_x(suma), punto_obtener_y(suma));
    
    punto_destruir(suma);
    punto_destruir(p1);
    punto_destruir(p2);
}
