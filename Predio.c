#include <stdio.h>
#include <stdlib.h>
#include "Predio.h"

typedef struct{
    char face;
    int num;
    double frnt;
    double prof;
    double mrg;
    Quadra q;
} predio;

Predio createPredio(char face, int numero, double frente, double profundidade, double margem, Quadra q){
    predio *newPredio = (predio*)malloc(sizeof(predio));
    newPredio->face = face;
    newPredio->num = numero;
    newPredio->frnt = frente;
    newPredio->prof = profundidade;
    newPredio->mrg = margem;
    newPredio->q = q;
    return (Predio)newPredio;
}

char *getPredioCep(Predio p){
    predio *newPredio = (predio*)p;
    return getQuadraCep(newPredio->q);
}

char getPredioFace(Predio p){
    predio *newPredio = (predio*)p;
    return newPredio->face;
}

int getPredioNumero(Predio p){
    predio *newPredio = (predio*)p;
    return newPredio->num;
}

double getPredioFrente(Predio p){
    predio *newPredio = (predio*)p;
    return newPredio->frnt;
}

double getPredioProfundidade(Predio p){
    predio *newPredio = (predio*)p;
    return newPredio->prof;
}

double getPredioMargem(Predio p){
    predio *newPredio = (predio*)p;
    return newPredio->mrg;
}

Quadra getPredioQuadra(Predio p){
    predio *newPredio = (predio*)p;
    return newPredio->q;
}

Ponto getPredioPoint(Predio p, int point){
    double x, y;
    predio *newPredio = (predio*)p;
    Quadra q = newPredio->q;
    x = getQuadraX(q);
    y = getQuadraY(q);
    if (newPredio->face == 'N'){
        x += getQuadraWidth(q);
        if (point == 1){
            x -= (getPredioNumero(p) + getPredioFrente(p)/2);
            y += getPredioMargem(p);
        } else if(point == 2){
            x -= (getPredioNumero(p) - getPredioFrente(p)/2);
            y += getPredioMargem(p);            
        } else if (point == 3){
            x -= (getPredioNumero(p) + getPredioFrente(p)/2);
            y += getPredioMargem(p) + getPredioProfundidade(p);
        } else if (point == 4){
            x -= (getPredioNumero(p) - getPredioFrente(p)/2);
            y += getPredioMargem(p) + getPredioProfundidade(p);            
        }
    } else if (newPredio->face == 'S'){
        y += getQuadraHeight(q);
        if (point == 1){
            x += (getPredioNumero(p) - getPredioFrente(p)/2);
            y -= (getPredioMargem(p) + getPredioProfundidade(p));
        } else if (point == 2){
            x += (getPredioNumero(p) + getPredioFrente(p)/2);
            y -= (getPredioMargem(p) + getPredioProfundidade(p));
        } else if (point == 3){
            x += (getPredioNumero(p) - getPredioFrente(p)/2);
            y -= getPredioMargem(p);
        } else if (point == 4){
            x += (getPredioNumero(p) + getPredioFrente(p)/2);
            y -= getPredioMargem(p);            
        }
    } else if (newPredio->face == 'L'){
        if (point == 1){
            x += getPredioMargem(p);
            y += (getPredioNumero(p) - getPredioFrente(p)/2);
        } else if (point == 2){
            x += getPredioMargem(p) + getPredioProfundidade(p);
            y += (getPredioNumero(p) - getPredioFrente(p)/2);
        } else if (point == 3){
            x += getPredioMargem(p);
            y += (getPredioNumero(p) + getPredioFrente(p)/2);            
        } else if (point == 4){
            x += getPredioMargem(p) + getPredioProfundidade(p);
            y += (getPredioNumero(p) + getPredioFrente(p)/2);            
        }
    } else if (newPredio->face == 'O'){
        x += getQuadraWidth(q);
        y += getQuadraHeight(q);
        if (point == 1){
            x -= (getPredioMargem(p) + getPredioProfundidade(p));
            y -= (getPredioNumero(p) + getPredioFrente(p)/2);
        } else if (point == 2){
            x -= getPredioMargem(p);
            y -= (getPredioNumero(p) + getPredioFrente(p)/2);            
        } else if(point == 3){
            x -= (getPredioMargem(p) + getPredioProfundidade(p));
            y -= (getPredioNumero(p) - getPredioFrente(p)/2);            
        } else if (point == 4){
            x -= getPredioMargem(p);
            y -= (getPredioNumero(p) - getPredioFrente(p)/2);            
        }
    }
    	// printf("x %f y %f\n", x, y);
        // printf("-----------------------------\n");

    return createPonto(x, y);
}