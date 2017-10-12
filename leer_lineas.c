#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGC 2

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

status_t validar_argumentos(int argc, char *argv[], FILE **fentrada)
{
	if( !argv || !fentrada)
	{
		printf("entre a ST_ERROR_PUNTERO_NULO\n");
		return ST_ERROR_PUNTERO_NULO;
	}
	if(argc != MAX_ARGC)
	{
		printf("entre a ST_ERROR_CANT_ARG\n");
		return ST_ERROR_CANT_ARG;
	}
	if((*fentrada = fopen(argv[1],"rt"))==NULL)
	{
		printf("entre a ST_ERROR_APERTURA_ARCHIVO\n");
		return ST_ERROR_APERTURA_ARCHIVO;
	}
	return ST_OK;
}

status_t leer_linea(FILE *fentrada, int *cant_lineas, char **linea,char *c)
{
	char *lineaBuffer;
	int maximumLineLength;
	int count;

	count = 0;
	maximumLineLength = 256;

	if (!fentrada)
		return ST_ERROR_PUNTERO_NULO;

	if((lineaBuffer = (char *)malloc(sizeof(char)*maximumLineLength)) == NULL)
		return ST_ERROR_NO_MEM;

	*c = fgetc(fentrada);
	while ((*c != '\n') && (*c != EOF))
	{
		lineaBuffer[count] = *c;
		count++;
		*c = fgetc(fentrada);
	}
	lineaBuffer[count] = '\0';

	if((*linea = (char *)malloc(sizeof(char)*count + 1)) == NULL)
	{
		free(lineaBuffer);
		lineaBuffer = NULL;
		return ST_ERROR_NO_MEM;
	}
	strncpy(*linea, lineaBuffer, (count + 1));
	free(lineaBuffer);
	lineaBuffer = NULL;
	return ST_OK;
}

int main (int argc, char *argv[])
{
	FILE *fentrada;
	status_t st;
	char *linea,c;
	int cant_lineas;

	linea = NULL;
	if((st = validar_argumentos(argc,argv,&fentrada))!=ST_OK)
	{
		fprintf(stderr, "Error en alguna validacion\n");
		return EXIT_FAILURE;
	}

	do
	{
		if((st=leer_linea(fentrada,&cant_lineas,&linea,&c)) != ST_OK)
		{
			if(linea != NULL)
			{
				free(linea);
				linea = NULL;
			}
			return EXIT_FAILURE;
		}
		printf("Linea %d) %s\n",cant_lineas +1,linea);
		free(linea);
		linea = NULL;
	}while(c != EOF);
	free(linea);
	linea = NULL;

	return EXIT_SUCCESS;
}