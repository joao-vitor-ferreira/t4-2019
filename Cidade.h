#ifndef CIDADE_H
#define CIDADE_H
#include <stdarg.h>
#include "Lista.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Muro.h"
#include "Predio.h"
#include "Pessoa.h"
#include "Morador.h"
#include "TipoEC.h"
#include "EstabelecimentoComercial.h"
#include "Svg.h"
#include "Rbtree.h"
#include "GrafoDirecionado.h"
    typedef void *Cidade;
    typedef void (*Function)(void *, ...);

/* Uma cidade é uma estrutura na qual armazena todas as informações, tal como quadras, hidantes, semaforos, radio-bases, predios, muros e outras formas*/

Cidade createCidade();
Lista getList(Cidade city, char t);
Rbtree getTree(Cidade city, char t);
int posicVazio(Posic p);
void addQuadra(Cidade city, Item info);
void addSemaforo(Cidade city, Item info);
void addTorre(Cidade city, Item info);
void addHidrante(Cidade city, Item info);
void addForma(Cidade city, Item info, int type);
void addMuro(Cidade city, Muro m);
void addPredio(Cidade city, Predio p);
void addTipoEC(Cidade city, TipoEC tp);
void addEstabCom(Cidade city, Estab ec);
void addPessoa(Cidade city, Pessoa ps);
void addMorador(Cidade city, Morador m);
/*retorna o grafo da cidade*/
GrafoD getGrafo(Cidade city);
Item getObjForma(Cidade city, PosicTree p);
Item getObjQuadra(Cidade city, PosicTree p);
Item getObjHidrante(Cidade city, PosicTree p);
Item getObjSemaforo(Cidade city, PosicTree p);
Item getObjHidrante(Cidade city, PosicTree p);  
Item getObjTorre(Cidade city, PosicTree p);
Predio getObjPredio(Cidade city, PosicTree p);
Rbtree getCidadeRbtree(Cidade city, char type);
void removeForma(Cidade city, PosicTree p);
void removePredio(Cidade city, PosicTree p);
void removeQuadra(Cidade city, PosicTree p);
void removeTorre(Cidade city, PosicTree p);
void removeSemaforo(Cidade city, PosicTree p);
void removeHidrante(Cidade city, PosicTree p);
Pessoa searchPessoaXCpf(Cidade city, char *cpf);
Morador searchMoradorCpf(Cidade city, char *cpf);
Estab searchEstabCom(Cidade city, char *cnpj);
PosicTree searchQuadra(Cidade city, char *cep);
PosicTree searchSemaforo(Cidade city, char *id);
PosicTree searchHidrante(Cidade city, char *id);
PosicTree searchTorre(Cidade city, char *id);
PosicTree searchForma(Cidade city, int id, int *type);
PosicTree searchPredio(Cidade city, char *cep, char face, int num);
PosicTree searchEquipUrban(Cidade city, char *id, char *type);
/*escreve no arquivo svg todos os equipamentos urbanos, quadras circulos e retangulos da cidade*/
void printSvgCidade(Cidade city, FILE *svg);
/* Dado uma cidade esta função percorre-a elemento por elemento e faz a função determinada func, a partir de alguma das listas determinnadas por t */
void throughCity (Cidade city, Function f, ...);
/* Desaloca remove todos os equipamentos urbanos e quadras e formas da cidade*/
void freeCidade(Cidade city);

#endif