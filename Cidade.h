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
#include "Svg.h"

    typedef void *Cidade;
    typedef void (*Function)(void *, ...);

/* Uma cidade é uma estrutura na qual armazena todas as informações, tal como quadras, hidantes, semaforos, radio-bases, predios, muros e outras formas*/

Cidade createCidade(int i, int nq, int nh, int ns, int nt, int np, int nm);
Lista getList(Cidade city, char t);
void addQuadra(Cidade city, Item info);
void addSemaforo(Cidade city, Item info);
void addTorre(Cidade city, Item info);
void addHidrante(Cidade city, Item info);
void addForma(Cidade city, Item info, int type);
void addMuro(Cidade city, Muro m);
void addPredio(Cidade city, Predio p);
Item getObjForma(Cidade city, Posic p);
Item getObjQuadra(Cidade city, Posic p);
Item getObjHidrante(Cidade city, Posic p);
Item getObjSemaforo(Cidade city, Posic p);
Item getObjHidrante(Cidade city, Posic p);  
Item getObjTorre(Cidade city, Posic p);
Predio getObjPredio(Cidade city, Posic p);
void removeForma(Cidade city, Posic p);
void removePredio(Cidade city, Posic p);
void removeQuadra(Cidade city, Posic p);
void removeTorre(Cidade city, Posic p);
void removeSemaforo(Cidade city, Posic p);
void removeHidrante(Cidade city, Posic p);
Posic searchQuadra(Cidade city, char *cep);
Posic searchSemaforo(Cidade city, char *id);
Posic searchHidrante(Cidade city, char *id);
Posic searchTorre(Cidade city, char *id);
Posic searchForma(Cidade city, int id, int *type);
Posic searchPredio(Cidade city, char *cep);
Posic searchEquipUrban(Cidade city, char *id, char *type);
void printSvgCidade(Cidade city, FILE *svg);
void throughCity (Cidade city, Function f, ...);
/* Dado uma cidade esta função percorre-a elemento por elemento e faz a função determinada func, a partir de alguma das listas determinnadas por t */
void freeCidade(Cidade city);
/* Desaloca remove todos os equipamentos urbanos e quadras e formas da cidade*/

#endif