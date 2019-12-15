#include "Poligono.h"
#include "Calculos.h"
#include "Rbtree.h"
#include <stdlib.h>

typedef struct {
    Rbtree arvoreSegmentos;
    double x_min, y_min, x_max, y_max;
}poligono;

Poligono createPoligono(FILE *arq_pol){
    poligono *newPol = (poligono*)malloc(sizeof(poligono));
    newPol->arvoreSegmentos = createTree();
    int its_first = 1;
    char line[50];
    double first_x, first_y, x, y, previous_x, previous_y;
    while (!feof(arq_pol)){
        fscanf(arq_pol, "%[^\n]\n", line);
        if (its_first){
            sscanf(line, "%lf %lf", &previous_x, &previous_y);
            first_x = previous_x;
            first_y = previous_y;
            newPol->x_max = previous_x;
            newPol->y_max = previous_y;
            newPol->x_min = previous_x;
            newPol->y_min = previous_y;
            its_first = 0;           
        } else {
            sscanf(line, "%lf %lf", &x, &y);
            if (x > newPol->x_max) newPol->x_max = x;
            if (y > newPol->y_max) newPol->y_max = y;
            if (x < newPol->x_min) newPol->x_min = x;
            if (y < newPol->y_min) newPol->y_min = y;

            Ponto p1 = createPonto(previous_x, previous_y)  ;
            Vertice v1 = createVertice(p1, 'o', 'i', NULL);
            Ponto p2 = createPonto(x, y);
            Vertice v2 = createVertice(p2, 'o', 'f', NULL);
            Segmento s1 = createSegmento(v1, v2);
            setVerticeSegmento(v1, s1);
            setVerticeSegmento(v2, s1);

            insertRbtree(newPol->arvoreSegmentos, s1);
            previous_x = x;
            previous_y = y;
        }
    }

    Ponto p1 = createPonto(x, y)  ;
    Vertice v1 = createVertice(p1, 'o', 'i', NULL);
    Ponto p2 = createPonto(first_x, first_y);
    Vertice v2 = createVertice(p2, 'o', 'f', NULL);
    Segmento s1 = createSegmento(v1, v2);
    setVerticeSegmento(v1, s1);
    setVerticeSegmento(v2, s1);    
    insertRbtree(newPol->arvoreSegmentos, s1);

    return newPol;
}

Rbtree getPoligonoArvore(Poligono p){
    poligono *newPol = (poligono*)p;
    return newPol->arvoreSegmentos;
}