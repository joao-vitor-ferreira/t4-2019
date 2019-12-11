#include <stdio.h>
#include "Hidrante.h"
#include <stdlib.h>
#include "Calculos.h"

typedef struct{
	double x;
	double y;
	char *id;
	char *corPreenchimento;
	char *corContorno;
	double especura_borda;
}hidrante;

Hidrante createHidrante(double x, double y, char *id, double sw){
	hidrante *newHidrante;
	newHidrante = (hidrante*)malloc(sizeof(hidrante));
	newHidrante->x = x;
	newHidrante->y = y;
	newHidrante->id = id;
	newHidrante->especura_borda = sw;
	newHidrante->corContorno = NULL;
	newHidrante->corPreenchimento = NULL;
	return (Hidrante)newHidrante;
}

double getHidranteX(Hidrante h){
	hidrante *newHidrante = (hidrante*)h;
	return newHidrante->x;
}

double getHidranteSW(Hidrante h){
	hidrante *newHidrante = (hidrante*)h;
	return newHidrante->especura_borda;
}

double getHidranteY(Hidrante h){
	hidrante *newHidrante = (hidrante*)h;
	return newHidrante->y;
}

char *getHidranteId(Hidrante h){
	hidrante *newHidrante = (hidrante*)h;
	return newHidrante->id;
}

char *getHidranteCorPreenchimento(Hidrante h){
	hidrante *newHidrante = (hidrante*)h;
	return newHidrante->corPreenchimento;
}

char *getHidranteCorContorno(Hidrante h){
	hidrante *newHidrante = (hidrante*)h;
	return newHidrante->corContorno;
}

void setHidranteCorPreenchimento(Hidrante h, char *cor){
	hidrante *newHidrante = (hidrante*)h;
	if (newHidrante->corPreenchimento != NULL)
		free(newHidrante->corPreenchimento);
	newHidrante->corPreenchimento = cor;
}

void setHidranteCorContorno(Hidrante h, char *cor){
	hidrante *newHidrante = (hidrante*)h;
	if (newHidrante->corContorno != NULL)
		free(newHidrante->corContorno);
	newHidrante->corContorno = cor;
}

void setHidranteX(Hidrante h, double x){
	hidrante *newHidrante = (hidrante*)h;
	newHidrante->x += x;
}

void setHidranteY(Hidrante h, double y){
	hidrante *newHidrante = (hidrante*)h;
	newHidrante->y += y;
}

int hidranteInternoRetangulo(FILE **txt, Hidrante h, Retangulo r){
	double d;
	if (pontoInternoRetangulo(r, getHidranteX(h), getHidranteY(h)) == 1){
		if (*txt != NULL)
			fprintf(*txt, "%s %f %f %s %s\n", getHidranteId(h), getHidranteX(h), getHidranteY(h), getHidranteCorPreenchimento(h), getHidranteCorContorno(h));
		return 1;
	}
	return 0;
}

int hidranteInternoCirculo(FILE **txt, Hidrante h, Circulo c){
	double d;
	if (pontoInternoCirculo(c, getHidranteX(h), getHidranteY(h)) == 1){
		if (*txt != NULL)
			fprintf(*txt, "%s %f %f %s %s\n", getHidranteId(h), getHidranteX(h), getHidranteY(h), getHidranteCorPreenchimento(h), getHidranteCorContorno(h));
		return 1;
	}
	return 0;
}

void freeHidrante(Hidrante h){
	hidrante *newHidrante = (hidrante*)h;
	if (newHidrante->corContorno != NULL){
		free(newHidrante->corContorno);
	} if (newHidrante->corPreenchimento != NULL){
		free(newHidrante->corPreenchimento);
	} if (newHidrante->id != NULL){
		free(newHidrante->id);
	}
}