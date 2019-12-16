#ifndef POLIGONO_H
#define POLIGONO_H
#include <stdio.h>
#include "Rbtree.h"

    typedef void *Poligono;

Poligono createPoligono(FILE *arq_pol);
Rbtree getPoligonoArvore(Poligono p);
void printPoligono(FILE *svg, Poligono pol);
#endif