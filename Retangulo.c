#include <stdio.h>
#include "Retangulo.h"
#include <stdlib.h>
#include "Calculos.h"
typedef struct {
	int id;
	double w;
	double h;
	double x;
	double y;
	char *corPreenchimento;	
	char *corContorno;
	double especura_borda;
}retangulo;

Retangulo creatRetangulo(int id, double width, double height, double x, double y, char *corPreenchimento, char *corContorno, double sw){
	retangulo *newretangulo;
	newretangulo = (retangulo*)malloc(sizeof(retangulo));
	newretangulo->id = id;
	newretangulo->w = width;
	newretangulo->h = height;
	newretangulo->especura_borda = sw;
	newretangulo->x = x;
	newretangulo->y = y;
	newretangulo->corPreenchimento = corPreenchimento;
	newretangulo->corContorno = corContorno;
	return (Retangulo) newretangulo;
}

double getRetanguloSW(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->especura_borda;
}

int getRetanguloId(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->id;
}

double getRetanguloWidth(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->w;
}

double getRetanguloHeight(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->h;
}

double getRetanguloX(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->x;
}

double getRetanguloY(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->y;
}

char *getRetanguloCorPreenchimento(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->corPreenchimento;
}

char *getRetanguloCorContorno(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	return newretangulo->corContorno;
}

void freeCor(Retangulo r){
	retangulo *newretangulo = (retangulo*)r;
	if (newretangulo->corContorno != NULL){
		free(newretangulo->corContorno);
	}
	if (newretangulo->corPreenchimento != NULL){
		free(newretangulo->corPreenchimento);
	}
}

int cmpRetanguloTree(Retangulo r1, Retangulo r2){
	if (doubleEquals(getRetanguloX(r1), getRetanguloX(r2))){
		if (getRetanguloY(r1) >= getRetanguloY(r2)){
			return 1;
		} else {
			return -1;
		}
	} else if (getRetanguloX(r1) > getRetanguloX(r2)){
		return 1;
	} else {
		return -1;
	}	
}

void freeRetangulo(Retangulo r){
	freeCor(r);
	if (r != NULL)
		free(r);
}