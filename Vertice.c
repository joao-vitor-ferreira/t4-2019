#include <stdio.h>
#include "Vertice.h"
#include <stdlib.h>

typedef struct {
    Ponto point;
    double ang;
    double distancia_bomba;
    char cod;
    char type;
    void *pSeg;
} vertice;

Vertice createVertice(Ponto point, char cod, char type, Segmento pSeg){
    vertice *v = (vertice*)malloc(sizeof(vertice));
    v->point = point;
    v->cod = cod;
    v->type = type;
    v->pSeg = pSeg;
    v->ang = 0;
    return (Vertice)v;
}

Ponto getVerticePonto(Vertice v){
    vertice *newV = (vertice*)v;
    return newV->point;
}

char getVerticeTipo(Vertice v){
    vertice *newV = (vertice*)v;
    return newV->type;
}

char getVerticeCodigo(Vertice v){
    vertice *newV = (vertice*)v;
    return newV->cod;
}

void *getVerticeSegmento(Vertice v){
    vertice *newV = (vertice*)v;
    return newV->pSeg;
}

double getVerticeDistanciaBomba(Vertice v){
    vertice *newV = (vertice*)v;
    return newV->distancia_bomba;
}

double getVerticeAngulo(Vertice v){
    vertice *newV = (vertice*)v;
    return newV->ang;
}

void setVerticeDistanciaBomba(Vertice v, double distancia_bomba){
    vertice *newV = (vertice*)v;
    newV->distancia_bomba = distancia_bomba;
}

void setVerticeAngulo(Vertice v, double angulo){
    vertice *newV = (vertice*)v;
    newV->ang = angulo;
}

void setVerticeSegmento(Vertice v, void *s){
    vertice *newV = (vertice*)v;
    newV->pSeg = s;
}

void freeVertice(Vertice v){
    vertice *newV = (vertice*)v;
    if (newV != NULL)
        free(newV);
}

int comparaVertice(const void *x, const void *y) {
    Vertice a = ((Vertice) x);
    Vertice b = ((Vertice) y);
    if(getVerticeAngulo(a) < getVerticeAngulo(b))
        return -1;
    else if(getVerticeAngulo(a) > getVerticeAngulo(b))
        return 1;
    else if(getVerticeDistanciaBomba(a) < getVerticeDistanciaBomba(b))
        return -1;
    else if(getVerticeDistanciaBomba(a) > getVerticeDistanciaBomba(b))
        return 1;
    else if(getVerticeTipo(a) == 'i' && getVerticeTipo(b) == 'f')
        return -1;
    else if(getVerticeTipo(a) == 'f' && getVerticeTipo(b) == 'i')
        return 1;
    return 0;
}




// int comparaVertice(const void *a, const void *b){
//     Vertice v1 = *((Vertice*)a);
//     Vertice v2 = *((Vertice*)b);

//     if (getVerticeAngulo(v1) < getVerticeAngulo(v2)){
//         return 1;
//     } else if (getVerticeAngulo(v1) > getVerticeAngulo(v2)){
//         return -1;
//     } else {
//         if (getVerticeDistanciaBomba(v1) > getVerticeDistanciaBomba(v2)){
//             return 1;
//         } else if(getVerticeDistanciaBomba(v1) < getVerticeDistanciaBomba(v2)){
//             return -1;
//         } else {
//             if (getVerticeTipo(v1) == 'i' && getVerticeTipo(v2) == 'f'){
//                 return 1;
//             } else {
//                 return 0;
//             }
//         }
//     }
// }