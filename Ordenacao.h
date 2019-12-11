#ifndef ORDENACAO_H
#define ORDENACAO_H
#include "Vector.h"
#include "Lista.h"

typedef char *(*Str)(Item);
typedef double (*Mat)(Item);
typedef void *Distance;
// typedef int (*Compare)(Vector vet, int i, int j, char p);
typedef int (*Comparacao)(Vector vet, int i, int j);

// Vector ltov(Lista list, Mat matx, Mat maty, Str id);
// void heapSort(Vector vet, Compare cmp, char coodn);
/*Estrutura usada para auxiliar na função knn na ordenação*/
Distance createDistance(double distancia, void *obj);
double getDistanceDist(Distance d);
void *getDistanceObj(Distance d);
int cmpDistance(Vector vet, int i, int j);
void freeDistance(Distance d);

/*k neighbors farest, é a função que dado um Vector vet, ordena em ordem crescente os k maiores valores de vet*/
void knf(Vector vet, Comparacao cmp, int k);
/*k neighbors nearest, é a função que dado um Vector vet, ordena em ordem decrescente os k menores valores de vet*/
void knn(Vector vet, Comparacao cmp, int k);
/*função que ordena no Vector vet todos os valores que são maiores que o raio, os colocando em ordem ccrescente do indice I em diante e o retorna  */
int knnr(Vector vet, Comparacao cmp, double raio);

#endif