#include <stdio.h>
#include <stdlib.h>
#include "Ponto.h"
#include "Segmento.h"
#include "Vertice.h"

typedef struct {
    int id;
    void *vIni;
    void *vFim;
} segmento;


Segmento createSegmento(void *vIni, void *vFim){
    segmento *seg = (segmento*)malloc(sizeof(segmento));
    seg->vIni = vIni;
    seg->vFim = vFim;
    seg->id = -1;
    return (Segmento)seg;
}

void *getSegmentoVerticeInicial(Segmento seg){
    segmento *newSeg = (segmento*)seg;
    return newSeg->vIni;
}

void *getSegmentoVerticeFinal(Segmento seg){
    segmento *newSeg = (segmento*)seg;
    return newSeg->vFim;
}

void setSegmentoVerticeInicial(Segmento seg, void *vIni){
    segmento *newSeg = (segmento*)seg;
    newSeg->vIni = vIni;
}

void setSegmentoVerticeFinal(Segmento seg, void *vFim){
    segmento *newSeg = (segmento*)seg;
    newSeg->vFim = vFim;
}

int getSegmentoId(Segmento s){
    segmento *newSeg = (segmento*)s;
    return newSeg->id;
}

void setSegmentoId(Segmento s, int id){
    segmento *newSeg = (segmento*)s;
    newSeg->id = id;
}

int cmpSegmentoTree(Segmento a, Segmento b){
    Ponto p1 = getVerticePonto(getSegmentoVerticeInicial(a));
    Ponto p2 = getVerticePonto(getSegmentoVerticeInicial(b));
    return cmpPontoTree(p1, p2);
}

void freeSegmento(Segmento seg){
    segmento *newSeg = (segmento*)seg;
    if (newSeg != NULL){
        free(newSeg);
    }
}     