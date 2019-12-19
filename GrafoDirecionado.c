#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "ListaDinamica.h"
#include "Rbtree.h"
#include "GrafoDirecionado.h"
#include "Calculos.h"

typedef struct{
	ListaDinamica *vertices;
	Rbtree *aVertices;
}grafoD;

double calculaRotaPontos(double x1, double y1, double x2, double y2, double vm){
	double calc = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	calc = calc * vm; //vel media
	return calc;
}

typedef struct {
	char *id;
	double x;
	double y;
	bool isOpen;
	struct vertice *previous;
	struct aresta *previousAresta;
	double bestRoute;
	ListaDinamica *arestas;
}vertice;

typedef struct {
	VerticeG *v1;
	VerticeG *v2;
	char *ldir; //quadra ao lado direito (hifen = nenhuma)
	char *lesq; //quadra ao lado esquerdo (hifen = nenhuma)
	double cmp; //comprimento da rua(aresta)
	double vm; //velocidade media na rua
	char *nome; //nome da rua
	bool interditado;
}aresta;

GrafoD createGrafo(){ //grafo possui vertices, que por sua vez possuem arestas(ou caminhos)
	grafoD *newGrafoD = malloc(sizeof(grafoD));
	newGrafoD->vertices = createDinamicList();
	newGrafoD->aVertices = createTree();
	return newGrafoD;
}

VerticeG createVerticeGrafo(char *id, double x, double y){
	vertice *newVertice= malloc(sizeof(vertice));
	newVertice->id = id;
	newVertice->x = x;
	newVertice->y = y;
	newVertice->arestas = createDinamicList();
	newVertice->isOpen = true;
	newVertice->previous = NULL;
	newVertice->bestRoute = LONG_MAX/2;
	newVertice->previousAresta = NULL;
	return newVertice;
}

VerticeG getV1FromAresta(Aresta a){
	aresta *newAresta = a;
	return newAresta->v1;
}

VerticeG getV2FromAresta(Aresta a){
	aresta *newAresta = a;
	return newAresta->v2;
}

double getVelMediaAresta(Aresta a){
	aresta *newAresta = a;
	return newAresta->vm;
}

VerticeG searchVerticeGrafo(Rbtree tree, PosicTree root, char *id){
	if (posicTreeVazio(tree, root))
		return;
	searchVerticeGrafo(tree, getRbtreeLeft(tree, root), id);
	searchVerticeGrafo(tree, getRbtreeRight(tree, root), id);
	VerticeG v1 = getObjRbtree(tree, root);
	if (strcmp(getVerticeId(v1), id) == 0)
		return root;
	else
		return getNullTree(tree);
	
}

Aresta createAresta(char *i, char *j, char *ldir, char *lesq, double cmp, double vm, char *nome, GrafoD grafoDir){
	aresta *newAresta = malloc(sizeof(aresta));
	GrafoD *newGrafoD = grafoDir;
	VerticeG v;
	PosicLD p;
	newAresta->v1 = searchVerticeGrafo(getGrafoRbtreeVertices(newGrafoD), getRoot(getGrafoRbtreeVertices(newGrafoD)), i);
	newAresta->v2 = searchVerticeGrafo(getGrafoRbtreeVertices(newGrafoD), getRoot(getGrafoRbtreeVertices(newGrafoD)), j);
	// int n = 0;
	// for(p = getFirstDinamicList(getGrafoListaVertices(grafoDir)); n < 2; p = getNextDinamicList(p)){
	// 	v = getObjtDinamicList(p);
	// 	if(strcmp(getVerticeId(v), i) == 0){
	// 		newAresta->v1 = v;
	// 		n++;
	// 	}
	// 	else if(strcmp(getVerticeId(v), j) == 0){
	// 		newAresta->v2 = v;
	// 		n++;
	// 	}
	// }
	newAresta->ldir = ldir;
	newAresta->lesq = lesq;
	newAresta->cmp = cmp;
	newAresta->vm = vm;
	newAresta->nome = nome;
	newAresta->interditado = false;
	return newAresta;
}

void resetAux(Rbtree tree, PosicTree root){
	if (posicTreeVazio(tree, root))
		return;
	resetAux(tree, getRbtreeLeft(tree, root));
	resetAux(tree, getRbtreeRight(tree, root));
	VerticeG v1 = getObjRbtree(tree, root);
	if(verticeIsOpen(v1) == false){
		openVertice(v1);
	}
	if(getVerticePrevious(v1) != NULL){
		setVerticePrevious(v1, NULL);
	}
	if(getVerticeBestRoute(v1) != LONG_MAX/2){
		setVerticeBestRoute(v1, LONG_MAX/2);
	}
	if(getVerticePreviousAresta(v1) != NULL){
		setVerticePreviousAresta(v1, NULL);
	}
}

void resetGrafoInfo(GrafoD grafoDir){
	grafoD *newGrafoD = grafoDir;
	PosicLD p;
	VerticeG verticeAtual;
	resetAux(getGrafoRbtreeVertices(grafoDir), getRoot(getGrafoRbtreeVertices(grafoDir)));
}

VerticeG eVMPDPAux(Rbtree tree, PosicTree root, double x, double y, double *menorDist){
	double dist_Test;
	VerticeG vert_ret, vert_ant;
	if (posicTreeVazio(tree, root))
		return getNullTree(tree);
	vert_ant = eVMPDPAux(tree, getRbtreeLeft(tree, root), x, y, menorDist);
	if (!posicTreeVazio(tree, getRbtreeLeft(tree, root)))
		vert_ret = vert_ant;
	vert_ant = eVMPDPAux(tree, getRbtreeRight(tree, root), x, y, menorDist);
	if (!posicTreeVazio(tree, getRbtreeLeft(tree, root)))
		vert_ret = vert_ant;	
	VerticeG verticeRoot = getObjRbtree(tree, root);
	dist_Test = calculaRotaPontos(getVerticePosicX(verticeRoot), getVerticePosicY(verticeRoot), x, y, 1);
	if (dist_Test < (*menorDist)){
		*menorDist = dist_Test;
		return verticeRoot;
	}
}

VerticeG encontraVerticeMaisProxDoPonto(GrafoD grafoDir, double x, double y){
	grafoD *newGrafoD = grafoDir;
	PosicLD p, p2;
	VerticeG verticeAtual, verticeRetorno;
	double menorDist = LONG_MAX/2;
	double dist_Test;
	verticeRetorno = eVMPDPAux(getGrafoRbtreeVertices(grafoDir), getRoot(getGrafoRbtreeVertices(grafoDir)), x, y, &menorDist);
	// for(p = getFirstDinamicList(getGrafoListaVertices(newGrafoD)); p != NULL; p = getNextDinamicList(p)){
		
	// 	verticeAtual = getObjtDinamicList(p);

	// 	dist_Test = calculaRotaPontos(getVerticePosicX(verticeAtual), getVerticePosicY(verticeAtual), x, y, 1);
		
	// 	if(dist_Test < menorDist) {
	// 		menorDist = dist_Test;
	// 		p2 = getFirstDinamicList(getVerticeListaArestas(verticeAtual));
	// 		if(p2)
	// 			verticeRetorno = verticeAtual;
	// 	}
	// }	
	return verticeRetorno;
}

bool interditado(Aresta a){
	aresta *newAresta = a;
	return newAresta->interditado;
}

ListaDinamica calculaMelhorCaminho(GrafoD grafoDir, VerticeG v0, VerticeG vEnd){
	grafoD *newGrafoD = grafoDir;
	setVerticePrevious(v0, NULL);
	setVerticeBestRoute(v0, 0);

	VerticeG verticeTest, verticeAtual;
	VerticeG v1, v2;
	PosicLD p, p2, p3;
	Aresta a;
	
	int n = 0, i = 0, j = 0;
	double routeTest;

	double menorRota;
	bool finished = false;
	while(!finished){
		menorRota = LONG_MAX / 2;
		for(p2 = getFirstDinamicList(getGrafoListaVertices(grafoDir)); p2 != NULL; p2 = getNextDinamicList(p2)){ //enquanto houver VerticeG aberto, verifica (algoritmo de Djikstra)
			verticeTest = getObjtDinamicList(p2);

			if(verticeIsOpen(verticeTest) && getVerticeBestRoute(verticeTest) < menorRota) { //pega o VerticeG com a melhor estimativa atual
				menorRota = getVerticeBestRoute(verticeTest);
				verticeAtual = verticeTest;
			}
		}
		if(menorRota == LONG_MAX / 2){
			finished = true;
			break;
		}
		closeVertice(verticeAtual);	
		for(p = getFirstDinamicList(getVerticeListaArestas(verticeAtual)); p != NULL; p = getNextDinamicList(p)){ //verifica cada aresta do VerticeG atual
			a = getObjtDinamicList(p);
			
			if(interditado(a)){
				continue;
			}
			v2 = getV2FromAresta(a);

			if(verticeIsOpen(v2)){
				if(i == 0){ //apenas na primeira iteracao		
					v1 = getV1FromAresta(a);
					i++;
				}

				routeTest = calculaRotaPontos(getVerticePosicX(v1), getVerticePosicY(v1), getVerticePosicX(v2), getVerticePosicY(v2), getVelMediaAresta(a));
				routeTest = routeTest + getVerticeBestRoute(v1);
				if(routeTest < getVerticeBestRoute(v2)){ // rota de v1 a v2 melhor do que a anterior
					setVerticeBestRoute(v2, routeTest);
					setVerticePrevious(v2, v1);
				}
			}
		}
		i = 0;
	}

	ListaDinamica listCaminho = createDinamicList();
	verticeAtual = vEnd;
	while(verticeAtual != v0){
		insertDinamicList(listCaminho, verticeAtual);
		n++;
		verticeAtual = getVerticePrevious(verticeAtual);
	}
	insertDinamicList(listCaminho, v0);

	return listCaminho;
}

void insertVerticeGrafo(GrafoD grafoDir, VerticeG vert){
	grafoD *newGrafoD = grafoDir;
	insertDinamicList(newGrafoD->vertices, vert);
	return;
}

void insertVerticeDoGrafo(GrafoD grafoDir, VerticeG vert){
	grafoD *newGrafoD = (grafoD*)grafoDir;
	insertRbtree(newGrafoD->aVertices, vert, cmpVerticeDoGrafoTree);
}

void insertArestaVertice(VerticeG v, Aresta a){
	vertice *newVertice= v;
	insertDinamicList(newVertice->arestas, a); 
}

void openVertice(VerticeG v){
	vertice *newVertice= v;
	newVertice->isOpen = true;
}

void closeVertice(VerticeG v){
	vertice *newVertice= v;
	newVertice->isOpen = false;
}

void setVerticePrevious(VerticeG v, VerticeG vPrev){
	vertice *newVertice= v;
	newVertice->previous = vPrev;
}

void setVerticePreviousAresta(VerticeG v, Aresta aPrev){
	vertice *newVertice= v;
	newVertice->previousAresta = aPrev;
}

VerticeG getVerticePrevious(VerticeG v){
	vertice *newVertice= v;
	return newVertice->previous;
}

Aresta getVerticePreviousAresta(VerticeG v){
	vertice *newVertice= v;
	return newVertice->previousAresta;
}

void setVerticeBestRoute(VerticeG v, double bestRoute){
	vertice *newVertice= v;
	newVertice->bestRoute = bestRoute;
}

ListaDinamica *getGrafoListaVertices(GrafoD grafoDir){
	grafoD *newGrafoD = grafoDir;
	return newGrafoD->vertices;
}

Rbtree *getGrafoRbtreeVertices(GrafoD grafoDir){
	grafoD *newGrafoD = grafoDir;
	return newGrafoD->aVertices;
}

ListaDinamica *getVerticeListaArestas(VerticeG v){
	vertice *newVertice= v;
	return newVertice->arestas;
}

char *getVerticeId(VerticeG v){
	vertice *newVertice= v;
	return newVertice->id;
}

double getVerticePosicX(VerticeG v){
	vertice *newVertice= v;
	return newVertice->x;
}

double getVerticePosicY(VerticeG v){
	vertice *newVertice= v;
	return newVertice->y;
}

bool verticeIsOpen(VerticeG v){
	vertice *newVertice= v;
	return newVertice->isOpen;
}

double getVerticeBestRoute(VerticeG v){
	vertice *newVertice= v;
	return newVertice->bestRoute;
}

char *getArestaNome(Aresta a){
	aresta *newAresta = a;
	return newAresta->nome;
}

char *getArestaLEsq(Aresta a){
	aresta *newAresta = a;
	return newAresta->lesq;
}

char *getArestaLDir(Aresta a){
	aresta *newAresta = a;
	return newAresta->ldir;
}

int cmpVerticeDoGrafoTree(VerticeG v1, VerticeG v2){
	if (doubleEquals(getVerticePosicX(v1), getVerticePosicY(v2))){
		if (getVerticePosicY(v1) >= getVerticePosicY(v2))
			return 1;
		else
			return -1;
	} else if (getVerticePosicX(v2) > getVerticePosicX(v2))
		return 1;
	else
		return -1;
}