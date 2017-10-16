#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "common.h"

int main (int argc, char *argv[])
{
	/************* DECLARACION DE VARIABLES *************/
	FILE *fentrada, *fsalida;
	status_t st;
	char *linea,c,delimitador,**arreglo;
	int cant_lineas,i;
	size_t longitud; /* aca tambien uso un auxiliar de fechas*/
	juego_t *juego;

	/************* INICIALIZACION DE VARIABLES *************/
	longitud = 0;
	arreglo = NULL;
	delimitador = DELIMITADOR;
	i = 0;
	juego = NULL;
	linea = NULL;

    /******** VALIDACION DE ARGUMENTOS **********/
	if((st = validar_argumentos(argc,argv,&fentrada,&fsalida))!=ST_OK)
	{
		fprintf(stderr, "Error en alguna validacion\n");
		return EXIT_FAILURE;
	}
	/******** PROCESAMIENTO DE DATOS ************/
	cant_lineas = 0;
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
		/*printf("Linea %d) %s\n",cant_lineas,linea);*/

		/************* PARSEO DE UNA LINEA *************/
		if((split(linea,delimitador,&arreglo,&longitud)) != ST_OK)
		{
			fprintf(stderr, "Algo salio mal con split :/\n");
			return EXIT_FAILURE;
		}

		/************* IMPRESION DEL PARSEO *************/
		/*for(i=0; i<longitud;i++)
		{
			printf("%s\n",arreglo[i]);
		}*/
	/************** CARGA DE DATOS EN ESTRUCTURA ***************/
		if((st=cargar_datos(&juego,arreglo,longitud)) != ST_OK)
		{
			printf("ERROR EN LA CARGA DE DATOS EN LA MATRIZ\n");
			destruir_arreglo_cadenas(&arreglo,longitud);
			return EXIT_FAILURE;
		}	
		free(linea);
		linea = NULL;
		destruir_arreglo_cadenas(&arreglo,longitud);
		
		/*printf("Estructura:\nID: %u \nNOMBRE: %s\nDESARROLLADOR: %s\nPLATAFORMA: %s\nFECHA: %u\nPUNTAJE: %f\nRESENIAS: %u\n", juego->id, juego->nombre, juego->desarrollador, juego->plataforma, juego->fecha, juego->puntaje, juego->resenias);*/
		fwrite(juego,sizeof(juego_t),1,fsalida);
		free(juego);
		juego = NULL;
	}while(c != EOF);

	fclose(fentrada);
	fclose(fsalida);

	return EXIT_SUCCESS;
}