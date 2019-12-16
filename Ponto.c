#include <stdio.h>
#include <stdlib.h>
#include "Ponto.h"
#include "Calculos.h"

typedef struct reg{
    double x;
    double y;
} ponto;

Ponto createPonto(double x, double y){
    ponto *newPonto;
    newPonto = (ponto*)malloc(sizeof(ponto));
    newPonto->x = x;
    newPonto->y = y;
    // newPonto->obj = object;
    
    return (Ponto)newPonto;
}

double getPontoX(Ponto p){
    ponto *newPonto = (ponto*)p;
    return newPonto->x;
}
double getPontoY(Ponto p){
    ponto *newPonto = (ponto*)p;
    return newPonto->y;
}

// void *getPontoObj(Ponto p){
//     ponto *newPonto = (ponto*)p;
//     return newPonto->obj;
// }

void setPontoX(Ponto p, double x){
    ponto *newPonto = (ponto*)p;
    newPonto->x = x;
}
void setPontoY(Ponto p, double y){
    ponto *newPonto = (ponto*)p;
    newPonto->y = y;
}

int cmpPontoTree(Ponto a, Ponto b){
    
    if (doubleEquals(getPontoX(a), getPontoX(b))){
        if (getPontoY(a) >= getPontoY(b))
            return 1;
        else 
            return -1;
    } else if (getPontoX(a) > getPontoX(b))
        return 1;
    else 
        return -1;
}

void freePonto(Ponto p){
    ponto *newPonto = (ponto*)p;
    if (newPonto != NULL){
        free(newPonto);
    }
}