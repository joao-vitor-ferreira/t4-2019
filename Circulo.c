#include <stdio.h>
#include "Circulo.h"
#include <stdlib.h>
#include "Calculos.h"

typedef struct {
	int id;
	char *corPreenchimento;
	char *corContorno;
	double x;
	double y;
	double raio;
	double especura_borda;
} circulo;

Circulo creatCirculo(int id, double raio, double x, double y, char *corPreenchimento, char *corContorno, double sw){
	circulo *newCirculo;
	newCirculo = (circulo*)malloc(sizeof(circulo));
	newCirculo->id = id;
	newCirculo->corPreenchimento = corPreenchimento;
	newCirculo->corContorno = corContorno;
	newCirculo->x = x;
	newCirculo->y = y;
	newCirculo->raio = raio;
	newCirculo->especura_borda = sw;
	return (Circulo) newCirculo;
}

double getCirculoSW(Circulo c){
	circulo *newCirculo = (circulo*)c;
	return newCirculo->especura_borda;
}

double getCirculoX(Circulo c){
	circulo *newCirculo = (circulo*)c;
	return newCirculo->x;
}

double getCirculoY(Circulo c){
	circulo *newCirculo = (circulo*)c;
	return newCirculo->y;
}

double getCirculoRaio(Circulo c){
	circulo *newCirculo = (circulo*)c;
	return newCirculo->raio;
}

int getCirculoId(Circulo c){
	circulo *newCirculo = (circulo*)c;
	return newCirculo->id;
}

char *getCirculoCorPreenchimento(Circulo c){
	circulo *newCirculo = (circulo*)c;
	return newCirculo->corPreenchimento;
}	

char *getCirculoCorContorno(Circulo c){
	circulo *newCirculo = (circulo*)c;
	return newCirculo->corContorno;
}

int cmpCirculoTree(Circulo c1, Circulo c2){
	if (doubleEquals(getCirculoX(c1), getCirculoY(c2))){
		if (getCirculoY(c1) >= getCirculoY(c2)){
			return 1;
		} else {
			return -1;
		}
	} else if (getCirculoY(c1) > getCirculoY(c2)){
		return 1;
	} else {
		return -1;
	}	
}

void freeCirculo(Circulo c){
	circulo *newCirculo = (circulo*)c;
	if (newCirculo->corContorno != NULL){
		free(newCirculo->corContorno);
	}
	if (newCirculo->corPreenchimento != NULL){
		free(newCirculo->corPreenchimento);
	}
	free(c);
}