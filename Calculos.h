#ifndef Calculos_H
#define Calculos_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>	
#include <math.h>
#include "Circulo.h"
#include "Retangulo.h"
#include "Ponto.h"
#include "Segmento.h"
#include "Vertice.h"
	
/*CALCULA A DISTÂNCIA ENTRE DOIS PONTOS NO PLANO CARTESIANO*/
double distanciaEntrePontos(double xa, double ya, double xb, double yb);
/* RETORNA 1 SE O PONTO DE COORDENADAS (X, Y) FOR INTERNO AO RETANGULO*/
int pontoInternoRetangulo(Retangulo r, double x, double y);
/* RETORNA 1 SE O PONTO DE COORDENADAS (X,Y) FOR INTERNO AO CIRCULO*/
int pontoInternoCirculo(Circulo c, double x, double y);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoCirculoRetangulo(Circulo c, Retangulo r);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoCirculoCirculo(Circulo c1, Circulo c2);
/*	A FUNÇÃO RETORNA 1 CASO A SOBREPOSIÇÃO OCORRA E A FUNÇÃO RETORNA 0 CASO CONTRÁRIO*/
int sobreposicaoRetanguloRetangulo(Retangulo r1, Retangulo r2);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE MASSA DE DOIS RETANGULOS*/
double dcmRetanguloRetangulo(Retangulo r1, Retangulo r2);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE UM CIRCULO E DE UM RETANGULOS*/
double dcmCirculoRetangulo(Circulo c1, Retangulo r1);
/* A FUNÇÃO RETORNA A DISTÂNCIA DO CENTRO DE MASSA DE DOIS CIRCULO*/
double dcmCirculoCirculo(Circulo c1, Circulo c2);
/*A FUNÇÃO RETORNA A DISTANCIA ENTRE DOIS PONTOS DE ACORDO COM A METRICA L1*/
double distPointsL1(double x1, double y1, double x2, double y2);
/*A FUNÇÃO VERIFICA SE OS PONTOS REFERENTES AO RETANGULO NO SVG (XR, YR, WIDTH, HEIGHT) ESTÃO INTEIRAMENTE DENTRO DO CIRCULO (XC, YC, RAIO)*/
int retanguloInternoCirculo(double xr, double yr, double width, double height, double xc, double yc, double raio);
/*A FUNÇÃO VERIFICA SE O RETANGULO(RI) ESTÁ TOTALMENTE INSERIDO DENTRO DE OUTRO RETANGULO(RE)*/
int retanguloInternoRetangulo(double xi, double yi, double wi, double hi, double xe, double ye, double we, double he);
/*A FUNÇÃO VERIFICA SE O CIRCULO(C) ESTÁ TOTALMENTE INSERIDO DENTRO DE OUTRO RETANGULO(R)*/
int circuloInternoRetangulo(double raio, double xc, double yc, double xr, double yr, double wr, double hr);
/*COMPARA DOIS VALORES V1 E V2 DO TIPO double E RETORNA 1 SE V1 > V2, 0 SE V1 == V2 OU -1 SE V1 < V2*/
int cmpDouble(double v1, double v2);
/*função a qual retorna o valor absoluto de value, |value|*/
double funcAbs(double value);
/*cria um segmento orientado S (p1 --> p2) de forma que o Ponto bomba esteja a esquerda de S*/
Segmento criaSegmentoAEsquerda(Ponto p1, Ponto p2, Ponto bomba);
/*verifica se dois segmentos se interseptam, se sim retorna 1 e o Ponto interseccao recebe a coordenada de intersecção, senão retorna 0 e o Ponto interseccao recebe NULL*/
int interseccaoSegmento(Segmento s1, Segmento s2, Ponto interseccao);
/*calcula a arco tangente de (p1.y - bomba.y) (p1.x - bomba.x) em radianos*/
double anguloPonto(Ponto p1, Ponto bomba);
/*retorna 1 se são iguais, 0 se são diferentes*/
int doubleEquals(double a, double b);
#endif