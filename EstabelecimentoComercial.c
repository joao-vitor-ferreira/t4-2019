#include <stdio.h>
#include "EstabelecimentoComercial.h"
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *cnpj;
	char *cpf;
	char *tipo;
	char *cep;
	char face; 
	int num;
	char *nome;
} estab;

Estab createEstab(char *cnpj, char *cpf, char *tipo, char *cep, char face, int num, char *nome){
	
	estab *newEstab;
	newEstab = (estab*)malloc(sizeof(estab));
	newEstab->cnpj = cnpj;
	newEstab->tipo = tipo;
	newEstab->cep = cep;
	newEstab->face = face;
	newEstab->num = num;
	newEstab->nome = nome;
	newEstab->cpf = cpf;

	return (Estab) newEstab;
}

void setEstabCep(Estab e, char *cep){
	estab *newEstab = (estab*)e;
	newEstab->cep = cep;
}

void setEstabNum(Estab e, int num){
	estab *newEstab = (estab*)e;
	newEstab->num = num;
}

void setEstabFace(Estab e, char face){
	estab *newEstab = (estab*)e;
	newEstab->face = face;
}

char *getEstabCNPJ(Estab e){
	estab *newEstab = (estab*)e;
	return newEstab->cnpj;
}

char *getEstabCPF(Estab e){
	estab *newEstab = (estab*)e;
	return newEstab->cpf;
}

char *getEstabTipo(Estab e){
	estab *newEstab = (estab*)e;
	return newEstab->tipo;
}

char *getEstabCep(Estab e){
	estab *newEstab = (estab*)e;
	return newEstab->cep;
}

char getEstabFace(Estab e){
	estab *newEstab = (estab*)e;
	return newEstab->face;
}

int getEstabNum(Estab e){
	estab *newEstab = (estab*)e;
	return newEstab->num;
}

char *getEstabNome(Estab e){
	estab *newEstab = (estab*)e;
	return newEstab->nome;
}

void freeEstab(Estab e){
	estab *newEstab = (estab*)e;
	if (newEstab->cnpj != NULL)
		free(newEstab->cnpj);
	if (newEstab->tipo != NULL)
		free(newEstab->tipo);
	if (newEstab->cep != NULL)
		free(newEstab->cep);
	if (newEstab->nome != NULL)
		free(newEstab->nome);
	if (newEstab->cpf != NULL)
		free(newEstab->cpf);
}