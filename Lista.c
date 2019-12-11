#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "Quadra.h"

typedef struct{
	Posic prev;
	Posic next;
	void *thing;
}array;

typedef struct{
	int size; // capacidade da lista
	Posic fist; // primeira posição da lista
	Posic last; // último posição da lista
	Posic fep; // primeira posição vazia
	int qtd_elementos;
	array *vet;
}head;

Lista createList(int size){
	head *cabeca;
	cabeca = (head*)malloc(sizeof(head));
	cabeca->size = size;
	cabeca->qtd_elementos = 0;
	cabeca->fep = 0;
	cabeca->fist = -1;
	cabeca->last = -1;
	cabeca->vet = (array*)malloc(sizeof(array)*size);
	int i, prev, next;
	prev = -1;
	next = 1;
	for (i = 0; i < size; i++, prev++, next++){
		cabeca->vet[i].prev = prev;
		cabeca->vet[i].next = next;
		cabeca->vet[i].thing = NULL;
	}
	cabeca->vet[size-1].next = -2;
	return cabeca;
}

int lengthList(Lista L){
	head *newHead = (head*)L;
	return newHead->size;
}

int qtdList(Lista L){
	head *newHead = (head*)L;
	return newHead->qtd_elementos;
}

Posic insertList(Lista L, Item info){
	head *newHead = (head*)L;
	Posic p;
	if (newHead->fep >= 0){
		newHead->vet[newHead->fep].thing = info;
		if (newHead->fist >= 0){
			newHead->vet[newHead->vet[newHead->fep].prev].next = newHead->fep;	
		}else
			newHead->fist = newHead->fep;
		newHead->last = newHead->fep;
		newHead->fep = newHead->vet[newHead->fep].next;
		newHead->vet[newHead->last].next = -1;
		newHead->qtd_elementos++;
	} else{
		printf("Lista cheia\n");
		return -1;
	}
	return newHead->last;
}


Item getObjList(Lista L, Posic p){
	head *newHead = (head*)L;
	return newHead->vet[p].thing;
}

void removeList(Lista L, Posic p){
	head *newHead = (head*)L;
	// fep == -1
	if (newHead->qtd_elementos == 1){
		newHead->fep = p;
		newHead->fist = -1;
		newHead->last = -1;
	} else {
		if(newHead->fist == p){
		newHead->fist = newHead->vet[newHead->fist].next;
		newHead->vet[newHead->fist].prev = -1;
		newHead->vet[p].next = newHead->fep;
		newHead->vet[p].prev = newHead->last;
		newHead->vet[newHead->fep].prev = p;
		newHead->fep = p;
		} else if (newHead->last == p){
			newHead->vet[newHead->vet[p].prev].next = -1;
			newHead->vet[p].next = newHead->fep;
			newHead->fep = p;
			newHead->last = newHead->vet[p].prev;
		} else {
			newHead->vet[newHead->vet[p].prev].next = newHead->vet[p].next;
			newHead->vet[newHead->vet[p].next].prev = newHead->vet[p].prev;
			newHead->vet[p].next = newHead->fep;
			newHead->vet[newHead->fep].prev = p;
			newHead->vet[p].prev = newHead->last;
			newHead->fep = p;
		}
	}
	newHead->qtd_elementos--;
}

Posic getFirst(Lista L){
	head *newHead = (head*)L;
	return newHead->fist;
}

Posic getLast(Lista L){
	head *newHead = (head*)L;
	return newHead->last;
}

Posic getNext(Lista L, Posic p){
	head *newHead = (head*)L;
	return newHead->vet[p].next;
}

Posic getPrevious(Lista L,Posic p){
	head *newHead = (head*)L;
	return newHead->vet[p].prev;
}

void deleteList(Lista L){
	head *newHead = (head*)L;
	if (newHead->vet != NULL)
		free(newHead->vet);
	if (newHead != NULL)
		free(newHead);
}

void printSvgList(Lista L, FILE *svg, svgColor printElement){
	head *newHead = (head*)L;
	Posic p1, p2;
	int i;
	p1 = getFirst(L);
	for (p1 = getFirst(L); p1 >= 0; p1 = getNext(L, p1)){
		printElement(&svg, getObjList(L, p1));
	}
}