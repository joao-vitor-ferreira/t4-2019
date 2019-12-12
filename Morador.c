#include <stdio.h>
#include <stdlib.h>
#include "Morador.h"
#include "Pessoa.h"
#include "Predio.h"

typedef struct {
    Pessoa ps;
    Predio pr;
    char *compl;
}morador;

Morador createMorador(Pessoa ps, Predio pr, char *compl){
    morador *newMorador;
    newMorador = (morador*)malloc(sizeof(morador));
    newMorador->ps = ps;
    newMorador->pr = pr;
    newMorador->compl = compl;
    return newMorador;
}

char *getMoradorCpf(Morador m){
    morador *newMorador = (morador*)m;
    return getPessoaCpf(newMorador->ps);
}

char *getMoradorCep(Morador m){
    morador *newMorador = (morador*)m;
    return getPredioCep(newMorador->pr);
}

char getMoradorFace(Morador m){
    morador *newMorador = (morador*)m;
    return getPredioFace(newMorador->pr);
}

int getMoradorNumero(Morador m){
    morador *newMorador = (morador*)m;
    return getPredioNumero(newMorador->pr);
}

char *getMoradorCompl(Morador m){
    morador *newMorador = (morador*)m;
    return newMorador->compl;
}

void freeMorador(Morador m){
    morador *newMorador = (morador*)m;
    if (newMorador->compl != NULL)
        free(newMorador->compl);
    if (newMorador != NULL)
        free(newMorador);
}