#ifndef MURO_H
#define MURO_H
#include "Ponto.h"

    typedef void *Muro;

Muro createMuro(Ponto ini, Ponto fim);
Ponto getMuroPontoInicial(Muro m);
Ponto getMuroPontoFinal(Muro m);
int cmpMuroTree(Muro m1, Muro m2);

#endif