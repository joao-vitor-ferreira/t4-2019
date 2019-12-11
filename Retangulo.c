#include <stdio.h>
#include "Retangulo.h"
#include <stdlib.h>
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

void freeRetangulo(Retangulo r){
	freeCor(r);
	if (r != NULL)
		free(r);
}