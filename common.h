#ifndef COMMON_H
#define COMMON_H

typedef enum {

				ST_OK,
				ST_ERROR_NO_MEM,
				ST_ERROR_PUNTERO_NULO,
				ST_ERROR_CARGAR_ID,
				ST_ERROR_CARGAR_FECHA,
				ST_ERROR_CARGAR_PUNTAJE,
				ST_ERROR_CARGAR_RESENIAS,
				ST_ERROR_CANT_ARG,
				ST_ERROR_APERTURA_ARCHIVO

			} status_t;


typedef struct {
				size_t id;
				char nombre[100];
				char desarrollador[100];
				char plataforma[50];
				size_t fecha; /* lo cambie temporalmente, despues vuelve a ser time_t */
				double puntaje;
				size_t resenias;
				} juego_t;
#endif

#define MAX_ARGC_CREAR_BASE 3
#define BASE 10
#define DELIMITADOR ','


