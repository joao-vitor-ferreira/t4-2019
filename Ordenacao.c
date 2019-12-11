#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ordenacao.h"
#include "Comandos.h"
#include "Calculos.h"
// #include "Elemento.h"

// Vector ltov(Lista list, Mat matx, Mat maty, Str mid){
//     int i;
//     char *id;
//     Posic p;
//     Elemento e;
//     Vector vet;
//     vet = createVector(length(list));
//     p = getFirst(list);
//     for (i = 1; i <= length(list); i++){
//         id  = (char*)malloc(sizeof(char)*(strlen((mid(getObjt(p)))) + 1));
//         strcpy(id, mid(getObjt(p)));
//         e = createElemento(matx(getObjt(p)), maty(getObjt(p)), id);
//         addVector(vet, e, i);
//         p = getNext(p);
//     }
//     return vet;
// }


typedef struct reg {
    double dist;
    void *obj;
}distancia;

Distance createDistance(double dist, void *obj){
    distancia *newDist = (distancia*)malloc(sizeof(distancia));
    newDist->dist = dist;
    newDist->obj = obj;
}

double getDistanceDist(Distance d){
    distancia *newDist = (distancia*)d;
    return newDist->dist;
}
void *getDistanceObj(Distance d){
    distancia *newDist = (distancia*)d;
    return newDist->obj;
}

int cmpDistance(Vector vet, int i, int j){
    Distance d1, d2;
    d1 = getObjVector(vet, i);
    d2 = getObjVector(vet, j);
    return cmpDouble(getDistanceDist(d1), getDistanceDist(d2));
}

void freeDistance(Distance d){
    if (d != NULL)
        free(d);
}

/* modificando o algoritmo do heapsort para encontrar os k vizinhos mais próximos */

void heapknn(Vector vet, int size, int i, Comparacao cmp){
    int l, r, smaller, var;
    char letra;
    smaller = i;
    l = 2*i;
    r = 2*i + 1;

    if (l < size){
        var = cmp(vet, l, smaller);
        if (var == -1)
            smaller = l;
    }
    if (r < size){
        var = cmp(vet, r, smaller);
        if (var == -1)
            smaller = r;
    }
    if (i != smaller){
        swap(vet, i, smaller);
        heapknn(vet, size, smaller, cmp);
    }
}

void knn(Vector vet, Comparacao cmp, int k){
    int i;
    for (i = getSizeVector(vet)/2 -1; i >= 0; i--){
        heapknn(vet, getSizeVector(vet), i, cmp);
    }

    for (i = getSizeVector(vet)-1; i>=0 && k>=0; i--, k--){
        swap(vet, 0, i);
        heapknn(vet, i, 0, cmp);
    }
}


void heapknf(Vector vet, int size, int i, Comparacao cmp){
    int l, r, largest, var;
    char letra;
    largest = i;
    l = 2*i;
    r = 2*i + 1;
    if (l < size){
        var = cmp(vet, l, largest);
        if (var == 1)
            largest = l;
    }
    if (r < size){
        var = cmp(vet, r, largest);
        if (var == 1)
            largest = r;
    }
    if (i != largest){
        swap(vet, i, largest);
        heapknf(vet, size, largest, cmp);
    }
}

void knf(Vector vet, Comparacao cmp, int k){
    int i;
    for (i = getSizeVector(vet)/2 - 1; i >= 0; i--){
        heapknf(vet, getSizeVector(vet), i, cmp);
    }

    for (i = getSizeVector(vet) - 1; i>=0 && k>=0; i--, k--){
        swap(vet, 0, i);
        heapknf(vet, i, 0, cmp);
    }
}


int knnr(Vector vet, Comparacao cmp, double raio){
    int i, qtd_element = 0;
    for (i = getSizeVector(vet)/2 - 1; i >= 0; i--){
        heapknn(vet, getSizeVector(vet), i, cmp);
    }

    for (i = getSizeVector(vet) - 1; i>=0; i--){
        if (cmpRaio(vet, 0, raio) < 0){
            break;
        }
        qtd_element++;
        swap(vet, 0, i);
        heapknn(vet, i, 0, cmp);
    }
    if (qtd_element > 0)
        return i + 1;
    else
        return -1;
}

// void heapSort(Vector vet, Compare cmp, char coodn){
//     int i;
//     for (i = getSizeVector(vet)/2; i > 0; i--){
//         heap(vet, getSizeVector(vet), i, cmp, coodn);
//     }
//     for (i = getSizeVector(vet); i>0; i--){
//         swap(vet, 1, i);
//         heap(vet, i, 1, cmp, coodn);
//     }
// }


// void heap(Vector vet, int size, int i, Compare cmp, char coodn){
//     int l, r, largest, var;
//     char letra;
//     largest = i;
//     l = 2*i;
//     r = 2*i + 1;
//     if (coodn == 'x')
//         letra = 'y';
//     else
//         letra = 'x';
//     if (l < size){
//         var = cmp(vet, l, largest, coodn);
//         if (var == -1)
//             largest = l;
//         if (var == 0){
//             var = cmp(vet, l, largest, letra);
//             if (var == -1)
//                 largest = l;
//         }
//     }
//     if (r < size){
//         var = cmp(vet, r, largest, coodn);
//         if (var == -1)
//             largest = r;
//         if (var == 0){
//             var = cmp(vet, r, largest, letra);
//             if (var == -1)
//                 largest = r;
//         }
//     }
//     if (i != largest){
//         swap(vet, i, largest);
//         heap(vet, size, largest, cmp, coodn);
//     }
// }
