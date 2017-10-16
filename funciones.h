#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/********************* PROTOTIPOS *************************************************/

status_t split(const char * cadena, char delimitador, char *** arreglo, size_t *l);
status_t strdup(const char*sc, char **p);
status_t destruir_arreglo_cadenas(char *** campos, size_t n);
status_t cargar_datos(juego_t **ptr_juego,char **arreglo, size_t l);


status_t validar_argumentos(int argc, char *argv[], FILE **fentrada, FILE **fsalida);
status_t leer_linea(FILE *fentrada, int *cant_lineas, char **linea,char *c);
/**********************************************************************************/