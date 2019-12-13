#ifndef PESSOA_H
#define PESSOA_H
#include "Quadra.h"

	typedef void *Pessoa;
	typedef void *Endereco;

Pessoa createPessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nasc); //cria uma pessoa com cpf, nome, sobrenome, sexo e data de nasc.
Endereco createEndereco(char *cep, char *face, int num, char *complm); //cria um endereco com cep, face, numero e complemento
void setPessoaEndereco(Pessoa p, Endereco end); // estabelece o endereco da pessoa p
char *getPessoaCpf(Pessoa p);
char *getPessoaNome(Pessoa p);
char *getPessoaSobreNome(Pessoa p);
char getPessoaSexo(Pessoa p);
char *getPessoaNasc(Pessoa p);
Endereco *getPessoaEndereco(Pessoa p);
char *getEnderecoCep(Endereco end);
char *getEnderecoFace(Endereco end);
int getEnderecoNum(Endereco end);
char *getEnderecoComplm(Endereco end);
double getEnderecoPosicX(Endereco e, Quadra q);
double getEnderecoPosicY(Endereco e, Quadra q);
void freePessoa(Pessoa p);
void freePessoaEndereco(Pessoa p);
#endif