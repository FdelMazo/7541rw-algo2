#include "testing.h"
#include <stdio.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_alumno();
void pruebas_catedra();

int main(void) {
    /* Ejecuta todas las pruebas unitarias. */
    printf("\n~~~ PRUEBAS CÁTEDRA ~~~\n");
	pruebas_catedra();

    return failure_count() > 0;
}
