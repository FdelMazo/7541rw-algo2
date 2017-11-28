#ifndef count_min_sketch_H
#define count_min_sketch_H

#include <stddef.h>
#include <stdbool.h>

struct count_min_sketch;
typedef struct count_min_sketch count_min_sketch_t;

count_min_sketch_t* count_min_sketch_crear();
void count_min_sketch_destruir(count_min_sketch_t* count);
void count_min_sketch_guardar(count_min_sketch_t* count, char* clave);
size_t count_min_sketch_obtener(count_min_sketch_t* count, char* clave);

#endif // count_min_sketch_H
