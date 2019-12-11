#ifndef PREDIO_H
#define PREDIO_H
#include "Quadra.h"
#include "Ponto.h"

    typedef void *Predio;

Predio createPredio(char face, int numero, double frente, double profundidade, double margem, Quadra q);
char *getPredioCep(Predio p);
char getPredioFace(Predio p);
int getPredioNumero(Predio p);
double getPredioFrente(Predio p);
double getPredioProfundidade(Predio p);
double getPredioMargem(Predio p);
Quadra getPredioQuadra(Predio p);
Ponto getPredioPoint(Predio p, int point);

#endif
