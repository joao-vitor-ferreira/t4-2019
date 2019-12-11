#ifndef TORRE_H
#define TORRE_H
#include "Retangulo.h"
#include "Circulo.h"
#include <stdio.h>

	typedef void *Torre;

Torre createTorre(double x, double y, char *id, double sw);
double getTorreSW(Torre t);
double getTorreX(Torre t);
double getTorreY(Torre t);
char *getTorreId(Torre t);
char *getTorreCorPreenchimento(Torre t);
char *getTorreCorContorno(Torre t);
void setTorreCorPreenchimento(Torre t, char *cor);
void setTorreCorContorno(Torre t, char *cor);
void setTorreX(Torre t, double x);
void setTorreY(Torre t, double y);
int torreInternaRetangulo(FILE **txt, Torre t, Retangulo r);
int torreInternaCirculo(FILE **txt, Torre t, Circulo c);
int cmpTorre(Torre t1, char *id);
void freeTorre(Torre t);

#endif