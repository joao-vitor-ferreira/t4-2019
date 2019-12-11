#ifndef HIDRANTE_H
#define HIDRANTE_H
#include "Retangulo.h"
#include "Circulo.h"
#include <stdio.h>

	typedef void *Hidrante;

Hidrante createHidrante(double x, double y, char *id, double sw);
double getHidranteX(Hidrante h);
double getHidranteY(Hidrante h);
char *getHidranteId(Hidrante h);
double getHidranteSW(Hidrante h);
char *getHidranteCorPreenchimento(Hidrante h);
char *getHidranteCorContorno(Hidrante h);
void setHidranteCorPreenchimento(Hidrante h, char *cor);
void setHidranteCorContorno(Hidrante h, char *cor);
void setHidranteX(Hidrante h, double x);
void setHidranteY(Hidrante h, double y);
int hidranteInternoRetangulo(FILE **txt, Hidrante h, Retangulo r);
int hidranteInternoCirculo(FILE **txt, Hidrante h, Circulo c);
void freeHidrante(Hidrante h);

#endif