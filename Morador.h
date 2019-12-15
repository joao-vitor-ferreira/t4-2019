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
Pessoa getMoradorPessoa(Morador m);
Pessoa getMoradorPredio(Morador m);
char *getMoradorCompl(Morador m);
void freeMorador(Morador m);
void setMoradorPredio(Morador m, Predio p, char *cep, char *compl, char face, int numero);
void setMoradorPessoa(Morador m, Pessoa ps, char *cpf);

#endif