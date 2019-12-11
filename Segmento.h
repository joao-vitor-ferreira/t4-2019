#ifndef SEGMENTO_H
#define SEGMENTO_H
#include "Ponto.h"
// #include "Vertice.h"

    /* Segmento é uma estrutura composta por um ponto inicial e por um ponto final a qual os dois pontos se ligam */
    typedef void *Segmento;
    

Segmento createSegmento(void *vini, void *vFim);
void *getSegmentoVerticeInicial(Segmento seg);
void *getSegmentoVerticeFinal(Segmento seg);
void setSegmentoVerticeInicial(Segmento seg, void *vIni);
void setSegmentoVerticeFinal(Segmento seg, void *vIni);
void setSegmentoId(Segmento s, int id);
int getSegmentoId(Segmento s);
void freeSegmento(Segmento seg);

#endif