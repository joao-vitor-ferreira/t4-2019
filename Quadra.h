#ifndef QUADRA_H
#define QUADRA_H
#include "Retangulo.h"
#include <stdio.h>
#include "Circulo.h"
#include "Lista.h"

	typedef void *Quadra;
/* Quadra é uma estrutura composta pelo ponto ancora, altura e largura, cores de preenchimento e contorno e seu identificador, seu cep, na qual será disposta num plano que chamaremos de cidade*/

Quadra createQuadra(double x, double y, double width, double height, char *cep, double sw);
char *getQuadraCorContorno(Quadra q);
char *getQuadraCorPreenchimento(Quadra q);
void setQuadraCorPreenchimento(Quadra q, char *cor);
void setQuadraCorContorno(Quadra q, char *cor);
void setQuadraX(Quadra q, double x);
void setQuadraY(Quadra q, double y);
char *getQuadraCep(Quadra q);
double getQuadraX(Quadra q);
double getQuadraSW(Quadra q);
double getQuadraY(Quadra q);
double getQuadraWidth(Quadra q);
double getQuadraHeight(Quadra q);
int quadraInternaRetangulo(FILE **txt, Quadra q, Retangulo r);
int verificaQuadraInternaRegiaoRet(Quadra q, double x, double y, double w, double h);
int quadraInternaCirculo(FILE **txt, Quadra q, Circulo c);
int comparaQuadra(Quadra q1, char *id);
void freeQuadra(Quadra q);
#endif