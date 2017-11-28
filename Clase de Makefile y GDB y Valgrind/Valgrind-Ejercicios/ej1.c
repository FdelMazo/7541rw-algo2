#include <stdlib.h>
#include <stdio.h>

typedef struct punto {
    double x;
    double y;
} punto_t;


punto_t* punto_crear(double x, double y) {
    punto_t* punto = malloc(sizeof(punto));
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

int main() {
    punto_t* p = punto_crear(3.2, 4.1);
    
    printf("La coordenada x del punto es: %lf\n", punto_obtener_x(p));
    printf("La coordenada y del punto es: %lf\n", punto_obtener_y(p));
    
    punto_destruir(p);
}
