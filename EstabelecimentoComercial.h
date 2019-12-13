#ifndef ESTABELECIMENTOCOMERCIAL_H
#define ESTABELECIMENTOCOMERCIAL_H

	typedef void *Estab;

Estab createEstab(char *cnpj, char *cpf, char *codt, char *cep, char face, int num, char *nome); //retorna um estabelecimento com cnpj, codigo de tipo TRANSFORMADO EM DESCRICAO, cep, face(Norte, Leste, ...), numero e Nome
char *getEstabNome(Estab e); //retorna nome do estabelecimento comercial e
char *getEstabTipo(Estab e); //retorna tipo do estabelecimento comercial e
char *getEstabCep(Estab e); //retorna Cep do estabelecimento comercial e
char getEstabFace(Estab e); //retorna Face do estabelecimento comercial e
char *getEstabCNPJ(Estab e); //retorna o CNPJ do estabelecimento comercial e
char *getEstabCPF(Estab e); //retorna o CPF do estabelecimento comercial e
void setEstabCep(Estab e, char *cep); //muda Cep do estabelecimento comercial e
void setEstabFace(Estab e, char face); //muda Face do estabelecimento comercial e
void setEstabNum(Estab e, int num); //muda Numero do estabelecimento comercial e
int getEstabNum(Estab e); //retorna numero do estabelecimento comercial e
void freeEstab(Estab e);

#endif