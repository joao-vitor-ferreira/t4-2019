#ifndef MURO_H
#define MURO_H
#include "Ponto.h"

    typedef void *Muro;

Muro createMuro(Ponto ini, Ponto fim);
Ponto getMuroPontoInicial(Muro m);
Ponto getMuroPontoFinal(Muro m);

#endif