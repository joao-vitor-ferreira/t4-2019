#include <stdlib.h>
#include "Muro.h"

typedef struct{
    Ponto pIni;
    Ponto pFim;
} muro;

Muro createMuro(Ponto ini, Ponto fim){
    muro *newMuro;
    newMuro = (muro*)malloc(sizeof(muro));
    newMuro->pIni = ini;
    newMuro->pFim = fim;

    return (Muro)newMuro;
}

Ponto getMuroPontoInicial(Muro m){
    muro *newMuro = (muro*)m;
    return newMuro->pIni;
}

Ponto getMuroPontoFinal(Muro m){
    muro *newMuro = (muro*)m;
    return newMuro->pFim;
}