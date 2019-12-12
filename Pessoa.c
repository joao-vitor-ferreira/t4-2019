#include <stdio.h>
#include "Pessoa.h"
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *cep;
	char *face;
	int num;
	char *complm;
} endereco;

typedef struct{
	char *cpf;
	char *nome;
	char *sobrenome;
	char *sexo; 
	char *nasc;
	endereco *endereco;
} pessoa;

Pessoa createPessoa(char *cpf, char *nome, char *sobrenome, char *sexo, char *nasc){
	pessoa *newPessoa;
	newPessoa = (pessoa*)malloc(sizeof(pessoa));
	newPessoa->cpf = cpf;
	newPessoa->nome = nome;
	newPessoa->sobrenome = sobrenome;
	newPessoa->sexo = sexo;
	newPessoa->nasc = nasc;
	newPessoa->endereco = NULL;
	return (Pessoa) newPessoa;
}

Endereco createEndereco(char *cep, char *face, int num, char *complm){
	endereco *newEndereco;
	newEndereco = (endereco*)malloc(sizeof(endereco));
	newEndereco->cep = cep;
	newEndereco->face = face;
	newEndereco->num = num;
	newEndereco->complm = complm;
	return (Endereco) newEndereco;
}

void setPessoaEndereco(Pessoa p, Endereco end){
	pessoa *newPessoa = (pessoa*) p;
	newPessoa->endereco = end;
}

char *getPessoaCpf(Pessoa p){
	pessoa *newPessoa = (pessoa*) p;
	return newPessoa->cpf;
}

char *getPessoaNome(Pessoa p){
	pessoa *newPessoa = (pessoa*) p;
	return newPessoa->nome;
}

char *getPessoaSobreNome(Pessoa p){
	pessoa *newPessoa = (pessoa*) p;
	return newPessoa->sobrenome;
}

char *getPessoaSexo(Pessoa p){
	pessoa *newPessoa = (pessoa*) p;
	return newPessoa->sexo;
}

char *getPessoaNasc(Pessoa p){
	pessoa *newPessoa = (pessoa*) p;
	return newPessoa->nasc;
}

Endereco *getPessoaEndereco(Pessoa p){
	pessoa *newPessoa = (pessoa*) p;
	return (Endereco) newPessoa->endereco;
}

double getEnderecoPosicX(Endereco e, Quadra q){
	endereco *newEndereco = e;
	if((strcmp(getEnderecoFace(newEndereco), "N") == 0) || (strcmp(getEnderecoFace(newEndereco), "S") == 0)) {
		return (getQuadraX(q) + (getQuadraWidth(q)/2));
	}
	else if (strcmp(getEnderecoFace(e), "L") == 0) {
		return (getQuadraX(q));
	}
	else {
		return (getQuadraX(q) + getQuadraWidth(q));
	}
}

double getEnderecoPosicY(Endereco e, Quadra q){
	endereco *newEndereco = e;
	if(strcmp(getEnderecoFace(newEndereco), "N") == 0) {
		return (getQuadraY(q) + getQuadraHeight(q));
	}
	else if (strcmp(getEnderecoFace(newEndereco), "S") == 0) {
		return (getQuadraY(q));
	}
	else {
		return (getQuadraY(q) + (getQuadraHeight(q)/2)  );
	}
}

void freePessoaEndereco(Pessoa p){
	pessoa *newPessoa = (pessoa*) p;
	free(newPessoa->endereco);
}

char *getEnderecoCep(Endereco end){
	endereco *newEnd = (endereco*) end;
	return (newEnd->cep);
}

char *getEnderecoFace(Endereco end){
	endereco *newEnd = (endereco*) end;
	return (newEnd->face);
}

int getEnderecoNum(Endereco end){
	endereco *newEnd = (endereco*) end;
	return (newEnd->num);
}
char *getEnderecoComplm(Endereco end){
	endereco *newEnd = (endereco*) end;
	return (newEnd->complm);
}

void freePessoa(Pessoa p){
	pessoa *newPessoa = (pessoa*)p;
	if (newPessoa->cpf != NULL)
		free(newPessoa->cpf);
	if (newPessoa->nome != NULL)
		free(newPessoa->nome);
	if (newPessoa->sobrenome != NULL)
		free(newPessoa->sobrenome);
	if (newPessoa->sexo != NULL)
		free(newPessoa->sexo);
	if (newPessoa->nasc != NULL)
		free(newPessoa->nasc);
	if (newPessoa->endereco != NULL)
		free(newPessoa->endereco);
}
