#ifndef VERTICE_H
#define VERTICE_H
#include "Ponto.h"
#include "Segmento.h"

    typedef void *Vertice;
    /* Vertice é uma estrutura composta por: coordenada (x, y), um tipo (inicial ou final), um apontador para o segmento a que pertence e um código */

Vertice createVertice(Ponto point, char cod, char type, void *pSeg);
Ponto getVerticePonto(Vertice v);
char getVerticeTipo(Vertice v);
char getVerticeCodigo(Vertice v);
void *getVerticeSegmento(Vertice v);
void setVerticeDistanciaBomba(Vertice v, double distancia_bomba);
double getVerticeDistanciaBomba(Vertice v);
void setVerticeAngulo(Vertice v, double angulo);
void setVerticeSegmento(Vertice v, void *s);
int comparaVertice(const void *x, const void *y);
void freeVertice(Vertice v);
#endif