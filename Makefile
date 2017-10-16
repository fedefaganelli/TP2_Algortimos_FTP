CC=gcc
CFLAGS=-Wall -ansi -pedantic -O3 -c -lm
LFLAGS=-Wall
DEBUG=-g

all: crear_base

crear_base: crear_base.o funciones.o 
	$(CC) $(LFLAGS) $(DEBUG) -o crear_base crear_base.o funciones.o
crear_base.o: crear_base.c idioma.h funciones.h
	$(CC) $(CFLAGS) $(DEBUG) -o crear_base.o crear_base.c

function.o: funciones.c funciones.h idioma.h
	$(CC) $(CFLAGS) $(DEBUG) -o funciones.o funciones.c


funciones.h: common.h

clean:
	rm *.o
