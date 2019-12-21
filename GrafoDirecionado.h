#ifndef GRAFODIRECIONADO_H
#define GRAFODIRECIONADO_H
#include <stdbool.h>
#include "ListaDinamica.h"
#include "Ponto.h"
	typedef void *VerticeG;
	typedef void *Aresta;
	typedef void *GrafoD;

GrafoD createGrafo();
VerticeG createVerticeGrafo(char *id, double x, double y);
double calculaRotaPontos(double x1, double y1, double x2, double y2, double vm);
Aresta createAresta(char *i, char *j, char *ldir, char *lesq, double cmp, double vm, char *nome, GrafoD grafoDir);
/*adiciona no grafo grafoDir o vertice vert na arvore de vertices do grafo*/
void insertVerticeDoGrafo(GrafoD grafoDir, VerticeG vert);
/*adiciona no vertice v do grafo a aresta a na lista de adjacencia do vertice*/
void insertArestaVertice(VerticeG v, Aresta a);
/*seta o vertice como aberto para o algoritmo de dijkstra*/
void openVertice(VerticeG v);
/*seta o vertice como fechado para o algoritmo de dijkstra*/
void closeVertice(VerticeG v);
/*retorna o id do vertice v*/
char *getVerticeId(VerticeG v);
ListaDinamica *getGrafoListaVertices(GrafoD grafoDir);
/*dado um vertice do grafo, retorna a lista de adjacencia do vertice*/
ListaDinamica *getVerticeListaArestas(VerticeG v);
char *getVerticeId(VerticeG v);
/*retorna a posição do vertice no eixo x*/
double getVerticePosicX(VerticeG v);
/*retorna a posição do vertice no eixo y*/
double getVerticePosicY(VerticeG v);
/*retorna o numero de vertices no grafo*/
int getGrafoQtdVertice(GrafoD graph);
/*retorna o numero de aresta no grafo*/
int getGrafoQtdAresta(GrafoD graph);
/*retorna true se o vertice ja foi aberto no algoritmo dde dijkstra, senão retorna falso*/
bool verticeIsOpen(VerticeG v);
/*dado um vertice v, aponta v para o vertice anterior no algoritmo de dijjkstra*/
void setVerticePrevious(VerticeG v, VerticeG vPrev);
void setVerticePreviousAresta(VerticeG v, Aresta aPrev);
/*escreve o valor smallestDist na variavel bestRoute do vertice*/
void setVerticeBestRoute(VerticeG v, double smallestDist);
/*dado um vertice v, retorna o vertice anterior no algoritmo de dijkstra, caso não tenha executao o algoritmo aponta pra NULL*/
VerticeG getVerticePrevious(VerticeG v);
/*retorna a aresta para o*/
Aresta getVerticePreviousAresta(VerticeG v);
double getVerticeBestRoute(VerticeG v);
void resetGrafoInfo(GrafoD grafoDir);
VerticeG encontraVerticeMaisProxDoPonto(GrafoD grafoDir, double x, double y);
/*usa o algoritmo de Dijkstra para calcular a melhor rota do vertice v0 ao vertice vEnd*/
ListaDinamica calculaMelhorCaminho(GrafoD grafoDir, VerticeG v0, VerticeG vEnd, char vm_ou_cpm);
/*retorna o vertice inicial da aresta*/
VerticeG getV1FromAresta(Aresta a);
/*retorna o vertice final da aresta*/
VerticeG getV2FromAresta(Aresta a);
/*função retorna velocidade media da aresta*/
double getVelMediaAresta(Aresta a);
/*função para determinar se a aresta está transitavel ou não. Se sim retorna true, senão retorna false*/
bool interditado(Aresta a);
/*função retorna o nome da rua em que a aresta está*/
char *getArestaNome(Aresta a);
/*retorna o cep da quadra do lado esquerdo da aresta, caso não a encontre retorna "-"*/
char *getArestaLEsq(Aresta a);
/*retorna o cep da quadra do lado direito da aresta, caso não a encontre retorna "-"*/
char *getArestaLDir(Aresta a);
/*função de comparação de dois vertice para arvore, retorna 1 se vertice v1 >= v1, senão retorna -1*/
int cmpVerticeDoGrafoTree(VerticeG v1, VerticeG v2);
/*procura na arvore de vertices do grafo o vertice identificado por id*/
VerticeG searchVerticeGrafo(Rbtree tree, PosicTree root, char *id);
/*retorna a arvore de vertice do grafo*/
Rbtree *getGrafoRbtreeVertices(GrafoD grafoDir);
/*encontra o vertice do grafo mais próximo do ponot pt*/
VerticeG findNearestVertice(GrafoD graph, Ponto pt);
/*algoritmo de dijkstra*/
ListaDinamica dijkstra(GrafoD graph, VerticeG v0, VerticeG vEnd, char vm_ou_cpm);
#endif