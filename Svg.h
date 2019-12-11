#ifndef SGV_H
#define SGV_H

#include <stdio.h>
#include "Circulo.h"
#include "Retangulo.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Predio.h"
#include "Muro.h"
#include "Ponto.h"

	typedef void (*Print)(FILE **svg, void *);

void printSvgCirculo(FILE **svg, Circulo c);
void printSvgRetangulo(FILE **svg, Retangulo r);
void printSvgQuadra(FILE **svg, Quadra q);
void printSvgHidrante(FILE **svg, Hidrante h);
void printSvgTorre(FILE **svg, Torre t);
void printSvgSemaforo(FILE **svg, Semaforo s);
void printSvgPredio(FILE **svg, Predio p);
void printSvgMuro(FILE **svg, Muro m);
void printSvgLine(FILE **svg, double x1, double y1, double x2, double y2);
#endif