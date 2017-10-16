#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTIDAD_DE_ARGUMENTOS_PUNTAJE 8
#define NOMBRE_ARCHIVO_BASE_DE_DATOS "entrada.txt"
#define NOMBRE_ARCHIVO_A_MODIFICAR "salida.txt"
#define NOMBRE_ARCHIVO_PARA_MSJS_DE_ERRORES "errores.txt"
/*************** NUMERO DE POSICIONES PARA ARGUMENTOS ******************/
#define ARG_CMD_NUMERO_DE_POSICION_OPERACION 1
#define ARG_CMD_NUMERO_DE_POSICION_BAMDERA_ARCHIVO_BASE_DE_DATOS 2
#define ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_BASE_DE_DATOS 3
#define ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_A_MODIFICAR 4
#define ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_A_MODIFICAR 5
#define ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_MSJS_ERROR 6
#define ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_MSJS_ERROR 7
/***********************************************************************/
typedef enum {

				ST_OK,
				ST_ERROR_NO_MEM,
				ST_ERROR_PUNTERO_NULO,
				ST_ERROR_CARGAR_ID,
				ST_ERROR_CARGAR_FECHA,
				ST_ERROR_CARGAR_PUNTAJE,
				ST_ERROR_CARGAR_RESENIAS,
				ST_ERROR_CANT_ARG,
				ST_ERROR_APERTURA_ARCHIVO,
				ST_ERROR_CANTIDAD_INVALIDA_DE_ARGUMENTOS,
	/**************** ERRORES PARA APP PUNTAJE ***********************/
				ST_ERROR_CMD_ARG_OPERACION,
				ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_BASE_DE_DATOS,
				ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_BASE_DATOS_INVALIDO,
				ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_A_MODIFICAR,
				ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_A_MODIFICAR_INVALIDO,
				ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_MSJS_DE_ERRORES,
				ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_MSJ_DE_ERRORES_INVALIDO,
				ST_ERROR_APERTURA_ARCHIVO_DE_ENTRADA,
				ST_ERROR_APERTURA_ARCHIVO_DE_SALIDA

	/*****************************************************************/			
			} status_t;

status_t validar_argumentos_puntaje (int argc, char * argv[], FILE **fentrada, FILE ** fsalida);


int main (int argc, char *argv[])
{
	FILE *fentrada;
	FILE *fsalida;
	status_t st;

		if((st = validar_argumentos_puntaje(argc, argv, &fentrada, &fsalida))!=ST_OK)
	{
		fprintf(stderr, "Error en alguna validacion\n");
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}




status_t validar_argumentos_puntaje (int argc, char * argv[], FILE **fentrada, FILE ** fsalida)
{

	if (argv == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
/************ Se valida la cantidad de argumentos **************************/
	if  ( argc != CANTIDAD_DE_ARGUMENTOS_PUNTAJE )
		return ST_ERROR_CANTIDAD_INVALIDA_DE_ARGUMENTOS; 
	
/********************** Se validan las banderas ****************************/	
	if(	strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_OPERACION], "A") && strcmp(argv[1], "B") &&	strcmp(argv[1], "M") )
		return ST_ERROR_CMD_ARG_OPERACION;


	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_BAMDERA_ARCHIVO_BASE_DE_DATOS], "-if"))
		return ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_BASE_DE_DATOS;
	
	if ( strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_BASE_DE_DATOS], NOMBRE_ARCHIVO_BASE_DE_DATOS) )
		return ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_BASE_DATOS_INVALIDO;
	
	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_A_MODIFICAR], "-f"))
		return ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_A_MODIFICAR;

	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_A_MODIFICAR], NOMBRE_ARCHIVO_A_MODIFICAR))
		return ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_A_MODIFICAR_INVALIDO;

	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_BANDERA_ARCHIVO_MSJS_ERROR], "-log"))
		return ST_ERROR_CMD_ARG_BANDERA_PARA_ARCHIVO_MSJS_DE_ERRORES;

	if (strcmp(argv[ARG_CMD_NUMERO_DE_POSICION_NOMBRE_ARCHIVO_MSJS_ERROR], NOMBRE_ARCHIVO_PARA_MSJS_DE_ERRORES))
		return ST_ERROR_CMD_ARG_NOMBRE_ARCHIVO_MSJ_DE_ERRORES_INVALIDO;

		if((*fentrada = fopen(argv[3],"rt"))==NULL)
	{
		printf("entre a ST_ERROR_APERTURA_ARCHIVO_ENTRADA\n");
		return ST_ERROR_APERTURA_ARCHIVO_DE_ENTRADA;
	}
			if((*fsalida = fopen(argv[5],"rt"))==NULL)
	{
		printf("entre a ST_ERROR_APERTURA_ARCHIVO_SALIDA\n");
		return ST_ERROR_APERTURA_ARCHIVO_DE_SALIDA;
	}

/********************* Fin de validacion de banderas ***********************/
		
	return ST_OK;
}