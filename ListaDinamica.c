#include <stdio.h>
#include <stdlib.h>
#include "ListaDinamica.h"

typedef struct reg{
	int id;
	void *obj;
	struct reg *next;
	struct reg *prev;
}celula;

typedef struct abc{
	int length;
	struct reg *first;
	struct reg *last;
}list;

ListaDinamica createDinamicList(){
	list *L = (list*)calloc(1, sizeof(list));
	L->first = NULL;
	L->last = NULL;
	L->length = 0;
	return(L);
}

int DinamicListlength(ListaDinamica L){
	list *newlist;
	newlist = (list*)L;
	return newlist->length;
}

PosicLD insertDinamicList(ListaDinamica L, Item info){
	list *newlist;
	celula *newreg, *aux;
	newlist = (list*) L;
	newreg = (celula*)malloc(sizeof(celula));
	newreg->next = NULL;
	newreg->prev = NULL;
	newreg->obj = info;

	if (newlist->length == 0){
		newlist->first = newreg;
		newlist->last = newreg;
		newreg->id = 0;
	} else {
		aux = newlist->last;
		aux->next = newreg;
		newreg->prev = aux;
		newreg->next = NULL;
		newreg->id += 1;
		newlist->last = newreg;
	}
	newlist->length++;

	return (PosicLD) newreg;
}

void removeDinamicList(ListaDinamica L, PosicLD p){
	list *newlist = (list*)L;
	celula *newreg = (celula*)p;
	celula *prev = newreg->prev;
	celula *next = newreg->next;
	
	if (prev!=NULL){
		prev->next = next;
	} else{
		newlist->first = next;	
		if (next == NULL)
			newlist->first = NULL;
	} if (next!=NULL){
		next->prev = prev;
	} else{
		newlist->last = prev;
		if (prev == NULL)
			newlist->last = NULL;
	}
	(newlist->length)--;
	//if (newreg->obj != NULL)
		//free(newreg->obj);
	if (newreg != NULL)
		free(newreg);	
}

PosicLD insertDinamicListBefore(ListaDinamica L, PosicLD p, Item info){
	list *newlist = (list*)L;
	celula *newreg, *aux1, *aux2;
	aux1 = (celula*)p;
	aux2 = aux1->prev;
	newreg = (celula*)malloc(sizeof(celula));
	newreg->next = NULL;
	newreg->prev = NULL;
	if (aux2!=NULL){
		aux2->next = newreg;
		newreg->prev = aux2;
	} else{
		newlist->first = newreg;
	}
	newreg->next = aux1;
	aux1->prev = newreg;
	newreg->obj = info;
	newlist->length++;
	return (PosicLD)newreg;
}

PosicLD insertDinamicListAfter(ListaDinamica L, PosicLD p, Item info){
	list *newlist = (list*)L;
	celula *newreg, *aux1, *aux2;
	aux1 = (celula*)p;
	aux2 = aux1->next;
	newreg = (celula*)malloc(sizeof(celula));
	newreg->next = NULL;
	newreg->prev = NULL;
	if (aux2!=NULL){
		aux2->prev = newreg;
		newreg->next = aux2;
	} 
	else newlist->last = newreg;
	newreg->prev = aux1;
	aux1->next = newreg;
	newreg->obj = info;
	newlist->length++;
	return (PosicLD) newreg;
}

PosicLD getFirstDinamicList(ListaDinamica L){
	list *newlist = (list*)L;
	return (PosicLD) newlist->first;
}

PosicLD getLastDinamicList(ListaDinamica L){
	list *newlist = (list*)L;
	return (PosicLD) newlist->last;
}

PosicLD getNextDinamicList(PosicLD p){
	celula *newreg = (celula*)p;
	if (newreg != NULL){
		if (newreg->next != NULL)
			return(PosicLD)newreg->next;
	}
	return NULL;
}

PosicLD getPreviousDinamicList(PosicLD p){
	celula *newreg = (celula*)p;
	if (newreg!=NULL)
		return (PosicLD) newreg->prev;
	else
		return NULL;	
}

Item getObjtDinamicList(PosicLD p){
	if (p != NULL){
		celula *newreg = (celula*)p;
		return (Item)newreg->obj;
	}
	return NULL;
}

void deleteDinamicListComplete(ListaDinamica L, RemoveLeak equiment){
	PosicLD p1, p;
	int tam;
	list *newlist = (list*)L;
	celula *aux, *aux1;
	aux = newlist->first;
	tam = newlist->length;
	while(aux != NULL){
		aux1 = aux->next;
		if (equiment != NULL)
			equiment(getObjtDinamicList((PosicLD)aux));
		removeDinamicList(L, (PosicLD)aux);
		aux = aux1;
		tam--;
		if (tam <= 0)
			break;
	}
	if (newlist != NULL){
		free(newlist);
	}
}