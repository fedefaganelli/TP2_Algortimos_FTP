#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "common.h"

status_t validar_argumentos(int argc, char *argv[], FILE **fentrada, FILE **fsalida)
{
	if( !argv )
	{
		printf("entre a ST_ERROR_PUNTERO_NULO\n");
		return ST_ERROR_PUNTERO_NULO;
	}
	if(argc != MAX_ARGC_CREAR_BASE)
	{
		printf("entre a ST_ERROR_CANT_ARG\n");
		return ST_ERROR_CANT_ARG;
	}
	if((*fentrada = fopen(argv[1],"rt"))==NULL)
	{
		printf("entre a ST_ERROR_APERTURA_ARCHIVO\n");
		return ST_ERROR_APERTURA_ARCHIVO;
	}
	if((*fsalida = fopen(argv[2],"wb"))==NULL)
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
	(*cant_lineas)++;
	free(lineaBuffer);
	lineaBuffer = NULL;
	return ST_OK;
}


status_t strdup(const char *sc, char **p)
{
	size_t l;
	/*char * s;*/
	if(sc==NULL)
	{
		return ST_ERROR_PUNTERO_NULO;
	}
	l=strlen(sc)+1;
	if(((*p)=(char*)malloc(sizeof(char)*l))==NULL)
	{
		return ST_ERROR_NO_MEM;
	}
	memcpy(*p,sc,l);
	return ST_OK;
}

status_t split(const char * cadena, char delimitador, char *** arreglo, size_t *l)
{
	char ** campos;
	size_t n, i;
	char * aux, * q, * linea, delim[2];

	if(cadena == NULL || l == NULL)
		return ST_ERROR_PUNTERO_NULO;

	for(i=0, n=1; cadena[i]; i++) /* cuenta la cantidad de tokens que hay en la cadena */
	{
		if(cadena[i]== delimitador)
		{
			n++;
		}
	} 

	if((campos = (char **) malloc(sizeof(char*)*n)) == NULL) /* crea tantos campos como tokens haya*/
	{
		*arreglo=NULL;
		*l=0;
		return ST_ERROR_NO_MEM;
	}

	if((strdup(cadena,&linea))!=ST_OK)
	{
		free(campos);
		*arreglo= NULL;
		*l=0;
		return ST_ERROR_NO_MEM;
	}
	delim[0]= delimitador;
	delim[1]='\0';

	for(i=0, q=linea; (aux= strtok(q, delim))!=NULL;i++,q=NULL)
	{
		if((strdup(aux,&(campos[i]))) != ST_OK)
		{
			destruir_arreglo_cadenas(&campos, i);
			*arreglo=NULL;
			*l=0;
			return ST_ERROR_NO_MEM;
		}
	}

	free(linea);
	*l=i;
	*arreglo=campos;

	return ST_OK;
}

status_t destruir_arreglo_cadenas(char *** campos, size_t n)
{
	size_t i;

	for(i=0; i<n; i++)
	{
		free((*campos)[i]);
		(*campos)[i]=NULL;
	}
	free(*campos);
	*campos=NULL;

	return ST_OK;
}

status_t cargar_datos(juego_t **ptr_juego,char **arreglo, size_t l)
{
	double puntaje_aux;
	size_t id_aux, fecha_aux, resenias_aux;
	char *temp;

	/************* CREAR ESTRUCTURA DINAMINCA ************/
	if((*ptr_juego = (juego_t *)malloc(sizeof(juego_t))) == NULL)
		return ST_ERROR_NO_MEM;

	/************* CARGAR INFORMACION EN ESTRUCTURAS *************/
	/************* ID **********/
	id_aux = strtol((arreglo[0]), &temp,BASE);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar el id en la estructura\n");
			return ST_ERROR_CARGAR_ID;  
		}
	(*ptr_juego)->id = id_aux;

	/********** NOMBRE **************/
	strcpy((*ptr_juego)->nombre,(arreglo[1]));

	/******** DESARROLLADOR ************/
	strcpy((*ptr_juego)->desarrollador,(arreglo[2]));

	/*********** PLATAFORMA **********/
	strcpy((*ptr_juego)->plataforma,(arreglo[3]));

	/******** FECHA ************/
	fecha_aux = strtol((arreglo[4]), &temp,BASE);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar la fecha en la estructura\n");
			return ST_ERROR_CARGAR_FECHA;  
		}
	(*ptr_juego)->fecha = fecha_aux;

	/*********** PUNTAJE **********/
	puntaje_aux = strtod((arreglo[5]), &temp);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar el puntaje en la estructura\n");
			return ST_ERROR_CARGAR_PUNTAJE;  
		}
	(*ptr_juego)->puntaje = puntaje_aux;
	/******** RESENIAS ************/
	resenias_aux = strtol((arreglo[6]), &temp,BASE);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar la resenia en la estructura\n");
			return ST_ERROR_CARGAR_RESENIAS;  
		}
	(*ptr_juego)->resenias = resenias_aux;

	return ST_OK;
}