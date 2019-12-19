#ifndef GRAFODIRECIONADO_H
#define GRAFODIRECIONADO_H
#include <stdbool.h>
#include "ListaDinamica.h"

	typedef void *VerticeG;
	typedef void *Aresta;
	typedef void *GrafoD;

GrafoD createGrafo();
VerticeG createVerticeGrafo(char *id, double x, double y);
double calculaRotaPontos(double x1, double y1, double x2, double y2, double vm);
Aresta createAresta(char *i, char *j, char *ldir, char *lesq, double cmp, double vm, char *nome, GrafoD grafoDir);
void insertVerticeGrafo(GrafoD grafoDir, VerticeG vert);
void insertArestaVertice(VerticeG v, Aresta a);
void openVertice(VerticeG v);
void closeVertice(VerticeG v);
char *getVerticeId(VerticeG v);
ListaDinamica *getGrafoListaVertices(GrafoD grafoDir);
ListaDinamica *getVerticeListaArestas(VerticeG v);
char *getVerticeId(VerticeG v);
double getVerticePosicX(VerticeG v);
double getVerticePosicY(VerticeG v);
bool verticeIsOpen(VerticeG v);
void setVerticePrevious(VerticeG v, VerticeG vPrev);
void setVerticePreviousAresta(VerticeG v, Aresta aPrev);
void setVerticeBestRoute(VerticeG v, double smallestDist);
VerticeG getVerticePrevious(VerticeG v);
Aresta getVerticePreviousAresta(VerticeG v);
double getVerticeBestRoute(VerticeG v);
void resetGrafoInfo(GrafoD grafoDir);
VerticeG encontraVerticeMaisProxDoPonto(GrafoD grafoDir, double x, double y);
ListaDinamica calculaMelhorCaminho(GrafoD grafoDir, VerticeG v0, VerticeG vEnd);
VerticeG getV1FromAresta(Aresta a);
VerticeG getV2FromAresta(Aresta a);
double getVelMediaAresta(Aresta a);
bool interditado(Aresta a);
char *getArestaNome(Aresta a);
char *getArestaLEsq(Aresta a);
char *getArestaLDir(Aresta a);
int cmpVerticeDoGrafoTree(VerticeG v1, VerticeG v2);


#endif