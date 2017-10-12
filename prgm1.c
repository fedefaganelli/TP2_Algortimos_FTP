/* 
	valgrind
 	valgrind ./aplicacion 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE 10

typedef enum {

				ST_OK,
				ST_ERROR_NO_MEM,
				ST_ERROR_PUNTERO_NULO,
				ST_ERROR_CARGAR_ID,
				ST_ERROR_CARGAR_FECHA,
				ST_ERROR_CARGAR_PUNTAJE,
				ST_ERROR_CARGAR_RESENIAS
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

/********************* PROTOTIPOS *************************************************/
status_t split(const char * cadena, char delimitador, char *** arreglo, size_t *l);
status_t strdup(const char*sc, char **p);
status_t destruir_arreglo_cadenas(char *** campos, size_t n);
status_t cargar_datos(juego_t *ptr_juego,char **arreglo, size_t l);
/**********************************************************************************/

int main(void)
{
	/************* DECLARACION DE VARIABLES *************/
	char *cadena[] = {"12658,Persona 5,Atlus,PS4,20170404,94,73",
					  "68536,Zelda: Breath of the Wild,Nintendo,Switch,20170303,97,10"}; /* todavia no creo el campo time_t, simplemente meto otro size_t*/
	char ** arreglo;
	char delimitador;
	size_t longitud; /* aca tambien uso un auxiliar de fechas*/
	int i;
	juego_t juego; /*ptr_juego;*/
	status_t st;

	/************* INICIALIZACION DE VARIABLES *************/
	longitud = 0;
	arreglo = NULL;
	delimitador = ',';
	i = 0;
	/*ptr_juego = &juego;*/

	/************* PARSEO DE UNA LINEA *************/
	if((split(cadena[1],delimitador,&arreglo,&longitud)) != ST_OK)
	{
		fprintf(stderr, "Algo salio mal :/\n");
		return EXIT_FAILURE;
	}

	/************* IMPRESION DEL PARSEO *************/ /* esto esta solo para mostrar que se pudo parsear, despues no va*/ 
	for(i=0; i<longitud;i++)
	{
		printf("%s\n",arreglo[i]);
	}

	if((st=cargar_datos(&juego,arreglo,longitud)) != ST_OK)
	{
		printf("ERROR EN LA CARGA DE DATOS EN LA MATRIZ\n");
		destruir_arreglo_cadenas(&arreglo,longitud);
		return EXIT_FAILURE;
	}

	/*********************** IMPRIMIR ESTRUCTURA **********************/
	printf("Estructura:\nID: %u\nNOMBRE: %s\nDESARROLLADOR: %s\nPLATAFORMA: %s\nFECHA: %u\nPUNTAJE: %f\nRESENIAS: %u\n",juego.id,juego.nombre,juego.desarrollador,juego.plataforma,juego.fecha,juego.puntaje,juego.resenias);
	destruir_arreglo_cadenas(&arreglo,longitud);
	return EXIT_SUCCESS;
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

status_t cargar_datos(juego_t *ptr_juego,char **arreglo, size_t l)
{
	double puntaje_aux;
	size_t id_aux, fecha_aux, resenias_aux;
	char *temp;

	/************* CARGAR INFORMACION EN ESTRUCTURAS *************/
	/************* ID **********/
	id_aux = strtol((arreglo[0]), &temp,BASE);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar el id en la estructura\n");
			return ST_ERROR_CARGAR_ID;  
		}
	(ptr_juego)->id = id_aux;

	/********** NOMBRE **************/
	strcpy((ptr_juego)->nombre,(arreglo[1]));

	/******** DESARROLLADOR ************/
	strcpy((ptr_juego)->desarrollador,(arreglo[2]));

	/*********** PLATAFORMA **********/
	strcpy((ptr_juego)->plataforma,(arreglo[3]));

	/******** FECHA ************/
	fecha_aux = strtol((arreglo[4]), &temp,BASE);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar la fecha en la estructura\n");
			return ST_ERROR_CARGAR_FECHA;  
		}
	(ptr_juego)->fecha = fecha_aux;

	/*********** PUNTAJE **********/
	puntaje_aux = strtod((arreglo[5]), &temp);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar el puntaje en la estructura\n");
			return ST_ERROR_CARGAR_PUNTAJE;  
		}
	(ptr_juego)->puntaje = puntaje_aux;
	/******** RESENIAS ************/
	resenias_aux = strtol((arreglo[6]), &temp,BASE);
	if(*temp && *temp != '\n') 
		{
			printf("Error: no se pudo cargar la resenia en la estructura\n");
			return ST_ERROR_CARGAR_RESENIAS;  
		}
	(ptr_juego)->resenias = resenias_aux;

	return ST_OK;
}