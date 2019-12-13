#ifndef MORADOR_H
#define MORADOR_H
#include "Pessoa.h"
#include "Predio.h"

    typedef void *Morador;

Morador createMorador(Pessoa ps, Predio pr, char *cpf, char *cep, char face, int numero, char *compl);
char *getMoradorCpf(Morador m);
char *getMoradorCep(Morador m);
char getMoradorFace(Morador m);
int getMoradorNumero(Morador m);
char *getMoradorCompl(Morador m);
void freeMorador(Morador m);

#endif