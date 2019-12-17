#include <stdlib.h>
#include "Muro.h"
#include "Calculos.h"

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

int cmpMuroTree(Muro m1, Muro m2){
    Ponto p1 = getMuroPontoInicial(m1);
    Ponto p2 = getMuroPontoFinal(m2);
    if (doubleEquals(getPontoX(p1), getPontoX(p2))){
        if (getPontoY(p1) >= getPontoY(p2))
            return 1;
        else
            return -1;
    } else if (getPontoX(p1) > getPontoX(p2)){
        return 1;
    } else {
        return -1;
    }
}