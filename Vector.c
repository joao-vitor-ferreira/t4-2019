#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

typedef struct {
	void *obj;
	int i; // se i == 0 a estrutura armazena um circulo, se i == 1 a estrutura armazena um retangulo
}vector;

typedef struct{
	int size;
	int qntd;
	int countIndice; 
	vector *vet;
}head;


Vector createVector(int n){
	int i;
	head *newHead;
	vector *newVet;
	newHead = (head*)malloc(sizeof(head));
	newVet = (vector*)calloc(n, sizeof(vector));

	(*newHead).size = n;
	(*newHead).qntd = 0;
	(*newHead).countIndice = 0;
	(*newHead).vet = newVet;
	for (i=0; i<n; i++) {
		newVet[i].obj = NULL;
	}
	return (Vector)newHead;
}

int getQntd(Vector vet){
	head *newVector;
	newVector = (head*)vet;
	return newVector->qntd;
}

int getSizeVector(Vector vet){
	head *newVector;
	newVector = (head*)vet;
	return newVector->size;
}

int getQuantidadeVector(Vector vet){
	head *newVector;
	newVector = (head*)vet;
	return newVector->qntd;
}

void setSizeVector(Vector vet, int size){
	head *newVet;
	newVet = (head*)vet;
	newVet->size = size;
}

Item getObjVector(Vector vet, int n){
	head *cabeca;
	vector *vetor;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	if (vetor[n].obj == NULL)
		return NULL;
	else
		return vetor[n].obj;
}

void realocarVector(Vector vet){
	int i;
	head *cabeca;
	vector *vetor, *newVector;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	newVector = (vector*)calloc((cabeca->size)*2, sizeof(vector));
	for (i=0; i<(cabeca->size); i++){
		newVector[i].i = vetor[i].i;
		newVector[i].obj = vetor[i].obj;
	}
	free(vetor);
	cabeca->vet = newVector;
	cabeca->size *= 2;
}

int getTypeObj(Vector vet, int posic){
	head *cabeca;
	vector *vetor;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	if ((*cabeca).vet[posic].obj == NULL)
		return -1;
	return (*cabeca).vet[posic].i;
}

void addVector(Vector vet,	Item obj, int n, int i){
	head *cabeca;
	vector *vetor;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	if (cabeca->size <= cabeca->qntd){
		realocarVector(vet);
		vetor = cabeca->vet;
	}

	if (n < cabeca->size){
		vetor[n].obj = obj;
		vetor[n].i = i;
		cabeca->qntd++;
	}
	else
		printf("INDICE DO VETOR INVÁLIDO\n");	
}

void swap(Vector vet, int i, int j){
	// printf("aki\n");
	head *cabeca;
	vector *vetor, v;
	cabeca = (head*)vet;
	vetor = cabeca->vet;
	v.obj = vetor[i].obj;
	vetor[i].obj = vetor[j].obj;
	vetor[j].obj = v.obj;
}

void freeVector(Vector vet){
	head *cabeca = (head*)vet;
	vector *vetor = cabeca->vet;
	if (cabeca != NULL)
		free(cabeca);
	if (vetor != NULL)
		free(vetor);
}