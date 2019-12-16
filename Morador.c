#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Morador.h"
#include "Pessoa.h"
#include "Predio.h"

typedef struct {
    Pessoa ps;
    Predio pr;
    char *compl;
    char *cep;
    char *cpf;
    char face;
    int numero;
}morador;

Morador createMorador(Pessoa ps, Predio pr, char *cpf, char *cep, char face, int numero, char *compl){
    morador *newMorador;
    newMorador = (morador*)malloc(sizeof(morador));
    newMorador->ps = ps;
    newMorador->pr = pr;
    newMorador->cep = cep;
    newMorador->cpf = cpf;
    newMorador->face = face;
    newMorador->numero = numero;
    newMorador->compl = compl;
    return newMorador;
}

char *getMoradorCpf(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->cpf;
}

char *getMoradorCep(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->cep;
}

char getMoradorFace(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->face;
}

int getMoradorNumero(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->numero;
}

char *getMoradorCompl(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->compl;
}

void setMoradorPredio(Morador m, Predio p, char *cep, char *compl, char face, int numero){
    morador *newMorador = (morador*)m;
    newMorador->pr = p;
    newMorador->compl = compl;
    newMorador->cep = cep;
    newMorador->face = face;
    newMorador->numero = numero;
}

void setMoradorPessoa(Morador m, Pessoa ps, char *cpf){
    morador *newMorador = (morador*)m;
    newMorador->ps = ps;
    newMorador->cpf = cpf;
}

Pessoa getMoradorPessoa(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->ps;
}

Pessoa getMoradorPredio(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->pr;
}

void freeMorador(Morador m){
    morador *newMorador = (morador*)m;
    if (newMorador->compl != NULL)
        free(newMorador->compl);
    if (newMorador->cep != NULL)
        free(newMorador->cep);        
    if (newMorador->cpf != NULL)
        free(newMorador->cpf);        
    if (newMorador != NULL)
        free(newMorador);
}

int cmpMoradorTree(Morador m1, Morador m2){
    if (strcmp(getMoradorCpf(m1), getMoradorCpf(m2)) >= 0)
        return 1;
    else 
        return 0;
}