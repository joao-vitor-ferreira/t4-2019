#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Cidade.h"
#include "Lista.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Pessoa.h"
#include "TipoEC.h"
#include "Morador.h"
#include "EstabelecimentoComercial.h"
#include "Svg.h"
#include "Hash.h"
#include "Rbtree.h"
#include "Calculos.h"

typedef struct {
    Lista lQua;
    Lista lSem;
    Lista lHid;
    Lista lTor;
    Lista lFor;
    Lista lPre;
    Lista lMur;
    int cirQntd;
    int retQntd;
    Hash hTipoECXCodt;
    Hash hPessoaXCpf;
    Hash hMoradorXCpf;
    Hash hTipoEcXEC;
    Hash hECXCnpj;
    Hash hECXTipoEC;
    Rbtree aTor;
    Rbtree aQua;
    Rbtree aSem;
    Rbtree aHid;
    Rbtree aFor;
    Rbtree aPre;
    Rbtree aMur;

}cidade;

typedef struct {
    void *thing;
    int type; /* 0 para Circulo e 1 para retangulo*/
}forms;



Cidade createCidade(int i, int nq, int nh, int ns, int nt, int np, int nm){
    cidade *city;
    city = (cidade*)malloc(sizeof(cidade));
    city->lQua = createList(nq);
    city->lSem = createList(ns);
    city->lTor = createList(nt);
    city->lHid = createList(nh);
    city->lFor = createList(i);
    city->lPre = createList(np);
    city->lMur = createList(nm);
    city->cirQntd = 0;
    city->retQntd = 0;

    city->hMoradorXCpf = createHash(10000);
    city->hPessoaXCpf = createHash(10000);
    city->hTipoECXCodt = createHash(10000);
    city->hTipoEcXEC = createHash(10000);
    city->hECXCnpj = createHash(10000);
    city->hECXTipoEC = createHash(10000);

    city->aTor = createTree();
    city->aSem = createTree();
    city->aQua = createTree();
    city->aHid = createTree();
    city->aPre = createTree();
    city->aMur = createTree();
    city->aFor = createTree();

    return city;
}

Lista getList(Cidade city, char t){
    cidade *newCity = (cidade*)city;
    if (t == 'q'){
        return newCity->lQua;
    } else if (t == 't'){
        return newCity->lTor;
    } else if (t == 'h'){
        return newCity->lHid;
    } else if (t == 's'){
        return newCity->lSem;
    } else if (t == 'f'){
        return newCity->lFor;
    } else if (t == 'p'){
        return newCity->lPre;
    } else if (t == 'm'){
        return newCity->lMur;
    }
    
    printf("Paramento \"t\" incorreto\n");
    return NULL;
}

Rbtree getTree(Cidade city, char t){
    cidade *newCity = (cidade*)city;
    if (t == 'q'){
        return newCity->aQua;
    } else if (t == 't'){
        return newCity->aTor;
    } else if (t == 'h'){
        return newCity->aHid;
    } else if (t == 's'){
        return newCity->aSem;
    } else if (t == 'f'){
        return newCity->aFor;
    } else if (t == 'p'){
        return newCity->aPre;
    } else if (t == 'm'){
        return newCity->aMur;
    }
    return NULL;
}

int posicVazio(Posic p){
    return listaPosicVazio(p);
}

void addTipoEC(Cidade city, TipoEC tp){
    cidade *newCity = (cidade*)city;
    addHash(newCity->hTipoECXCodt, tp, getTipoECCodt(tp));
}

void addEstabCom(Cidade city, Estab ec){
    cidade *newCity = (cidade*)city;
    addHash(newCity->hECXCnpj, ec, getEstabCNPJ(ec));
    addHash(newCity->hECXTipoEC, ec, getEstabTipo(ec));
}

void addPessoa(Cidade city, Pessoa ps){
    cidade *newCity = (cidade*)city;
    addHash(newCity->hPessoaXCpf, ps, getPessoaCpf(ps));
}

void addMorador(Cidade city, Morador m){
    cidade *newCity = (cidade*)city;
    addHash(newCity->hMoradorXCpf, m, getMoradorCpf(m));
}

int cmpFormaTree(Item a, Item b){
    forms *f1 = (forms*)a;
    forms *f2 = (forms*)b;
    if (f1->type == 0 && f2->type == 0)
        return cmpCirculoTree(f1->thing, f2->thing);
    else if (f1->type == 1 && f2->type == 1)
        return cmpRetanguloTree(f1->thing, f2->thing);
    else if (f1->type == 0 && f2->type == 1){
        if (doubleEquals(getCirculoX(f1->thing), getRetanguloX(f2->thing))){
            if (getCirculoY(f1->thing) >= getRetanguloY(f2->thing))
                return 1;
            else 
                return-1;
        } else if (getCirculoX(f1->thing) > getRetanguloX(f2->thing))
            return 1;
        else 
            return -1;
    } else {
        if (doubleEquals(getCirculoX(f2->thing), getRetanguloX(f1->thing))){
            if (getCirculoY(f2->thing) <= getRetanguloY(f1->thing))
                return 1;
            else 
                return-1;
        } else if (getCirculoX(f2->thing) < getRetanguloX(f1->thing))
            return 1;
        else 
            return -1;        
    }
}

void addForma(Cidade city, Item info, int type){
    cidade *newCity = (cidade*)city;
    forms *forma = (forms*)malloc(sizeof(forms));
    forma->thing = info;
    forma->type = type;
    // insertList(newCity->lFor, forma);
    insertRbtree(newCity->aFor, forma, cmpFormaTree);
    if (type == 0){
        newCity->cirQntd++;
    } else {
        newCity->retQntd++;
    }
}

void addMuro(Cidade city, Muro m){
    cidade *newCity = (cidade*)city;
    // insertList(newCity->lMur, m);
    insertRbtree(newCity->aMur, m, cmpMuroTree);
}

void addPredio(Cidade city, Predio p){
    cidade *newCity = (cidade*)city;
    // insertList(newCity->lPre, p);
    insertRbtree(newCity->aPre, p, cmpPredioTree);
}

void addQuadra(Cidade city, Quadra q){
    cidade *newCity = (cidade*)city;
    // p = insertList(newCity->lQua, q);
    insertRbtree(newCity->aQua, q, cmpQuadraTree);
}

void addSemaforo(Cidade city, Semaforo s){
    cidade *newCity = (cidade*)city;
    // insertList(newCity->lSem, s);
    insertRbtree(newCity->aSem, s, cmpSemaforoTree);
}

void addTorre(Cidade city, Torre t){
    cidade *newCity = (cidade*)city;
    insertRbtree(newCity->aTor, t, cmpTorreTree);
}

void addHidrante(Cidade city, Hidrante h){
    cidade *newCity = (cidade*)city;
    insertRbtree(newCity->aHid, h, cmpHidranteTree);
}

Item getObjForma(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    forms *forma = /*getObjList(newCity->lFor, p);*/getObjRbtree(newCity->aFor, p);
    return forma->thing;
}
Quadra getObjQuadra(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    return getObjRbtree(newCity->aQua, p);
}

Hidrante getObjHidrante(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    return getObjRbtree(newCity->aHid, p);
}

Semaforo getObjSemaforo(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    return getObjRbtree(newCity->aSem, p);
}

Torre getObjTorre(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    return getObjRbtree(newCity->aTor, p);
}

Predio getObjPredio(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    // return getObjList(newCity->lPre, p);
    return getObjRbtree(newCity->aPre, p);
}

Rbtree getCidadeRbtree(Cidade city, char type){
    cidade *newCity = (cidade*)city;
    if (type == 't')
        return (Rbtree)newCity->aTor;
    else if (type == 'p')
        return(Rbtree)newCity->aPre;
    return NULL;
}

Pessoa searchPessoaXCpf(Cidade city, char *cpf){
    cidade *newCity = (cidade*)city;
    return (Pessoa)searchHash(newCity->hPessoaXCpf, cpf, getPessoaCpf);
}

Morador searchMoradorCpf(Cidade city, char *cpf){
    cidade *newCity = (cidade*)city;
    return (Morador)searchHash(newCity->hMoradorXCpf, cpf, getMoradorCpf);
}

Estab searchEstabCom(Cidade city, char *cnpj){
    cidade *newCity = (cidade*)city;
    Estab ec;
    return (Estab)searchHash(newCity->hECXCnpj, cnpj, getEstabCNPJ);
}

int searchPA(Rbtree tree, PosicTree atual, PosicTree *search, char *cep, char face, int num){
    int i;
    if (posicTreeVazio(tree, atual))
        return -1;
    i = searchPA(tree, getRbtreeLeft(tree, atual), search, cep, face, num);
    if (i == 0)
        return 0;
    i = searchPA(tree, getRbtreeRight(tree, atual), search, cep, face, num);
    if (i == 0)
        return 0;

    Predio p1 = getObjRbtree(tree, atual);
    if (strcmp(cep, getPredioCep(p1)) == 0 && getPredioFace(p1) == face && getPredioNumero(p1) == num){
        *search = atual;
        return 0;
    }
}

PosicTree searchPredio(Cidade city, char *cep, char face, int num){
    cidade *newCity = (cidade*)city;
    Predio pre;
    PosicTree pos, search = getNullTree(newCity->aPre);
    searchPA(newCity->aPre, getRoot(newCity->aPre), &search, cep, face, num);
    return search;

    // for(pos = getFirst(newCity->lPre); pos >= 0; pos = getNext(newCity->lPre, pos)){
    //     pre = getObjList(newCity->lPre, pos);
    //     if ((strcmp(cep, getPredioCep(pre)) == 0) && (face == getPredioFace(pre)) && (num == getPredioNumero(pre))){
    //         return pos;
    //     }
    // }
    // return -1;
}

int searchFormaRec(Rbtree tree, PosicTree pos, PosicTree *search, int *type, int id){
    forms *forma;
    Cidade c1;
    Retangulo r1;
    if (posicTreeVazio(tree, pos))
        return -1;
    searchFormaRec(tree, getRbtreeLeft(tree, pos), search, type, id);
    searchFormaRec(tree, getRbtreeRight(tree, pos), search, type, id);
    forma = (forms*)getObjRbtree(tree, pos);
    if (forma->type == 0){
        c1 = forma->thing;
        if (getCirculoId(c1) == id){
            *type = forma->type;
            *search = pos;
        } 
    } else{
        r1 = forma->thing;
        if (getRetanguloId(r1) == id){
            *type = forma->type;
            *search = pos;
        }
    }
    return 0;
}

PosicTree searchForma(Cidade city, int id, int *type){
    cidade *newCity = (cidade*)city;
    PosicTree search = getNullTree(newCity->aFor);
    searchFormaRec(newCity->aFor, getRoot(newCity->aFor), &search, type, id);
    return search;
}

/*
Posic searchForma(Cidade city, int id, int *type){
    cidade *newCity = (cidade*)city;
    Circulo c1;
    Retangulo r1;
    forms *forma;
    Posic p1;
    for (p1 = getFirst(newCity->lFor); p1 >= 0; p1 = getNext(newCity->lFor, p1)){
        forma = getObjList(newCity->lFor, p1);
        if (forma->type == 0){
            c1 = forma->thing;
            if (getCirculoId(c1) == id){
                *type = forma->type;
                return p1;
            } 
        } else{
            r1 = forma->thing;
            if (getRetanguloId(r1) == id){
                *type = forma->type;
                return p1;
            }
        }
    }
    *type = -1;
    return -1;
}
*/

int searchQA(Rbtree tree, PosicTree atual, PosicTree *search, char *cep){
    int i = 0;
    if (posicTreeVazio(tree, atual))
        return -1;
    i = searchQA(tree, getRbtreeLeft(tree, atual), search, cep);
    if (i == 0)
        return 0;
    i = searchQA(tree, getRbtreeRight(tree, atual), search, cep);
    if (i == 0)
        return 0;
    Quadra q1 = getObjRbtree(tree, atual);
    if (strcmp(cep, getQuadraCep(q1)) == 0){
        *search = atual;
        return 0;
    }
    return -1;
}

PosicTree searchQuadra(Cidade city, char *cep){
    cidade *newCity = (cidade*)city;
    Quadra q1;
    PosicTree pt1 = getRoot(newCity->aQua), search;
    searchQA(newCity->aQua, pt1, &search, cep);
    return search;
    // Posic p1;
    // for (p1 = getFirst(newCity->lQua); p1 >= 0; p1 = getNext(newCity->lQua, p1)){
    //     q1 = getObjList(newCity->lQua, p1);
    //     if (strcmp(getQuadraCep(q1), cep) == 0){
    //         return p1;
    //     }
    // }
    // return -1;
}

int searchSA(Rbtree tree, PosicTree atual, PosicTree *search, char *id){
    int i;
    if (posicTreeVazio(tree, atual))
        return -1;
    searchSA(tree, getRbtreeLeft(tree, atual), search, id);
    searchSA(tree, getRbtreeRight(tree, atual), search, id);
    Semaforo s1 = getObjRbtree(tree, atual);
    if (strcmp(id, getSemaforoId(s1)) == 0){
        *search = atual;
        return 0;
    }
    return -1;
}

PosicTree searchSemaforo(Cidade city, char *id){
    cidade *newCity = (cidade*)city;
    Semaforo s1;
    PosicTree pt1, search;
    searchSA(newCity->aSem, getRoot(newCity->aSem), &search, id);
    return search;
    // Posic p1;
    // for (p1 = getFirst(newCity->lSem); p1 >= 0; p1 = getNext(newCity->lSem, p1)){
    //     s1 = getObjList(newCity->lSem, p1);
    //     if (strcmp(getSemaforoId(s1), id) == 0){
    //         return p1;
    //     }
    // }
    // return -1;
}

int searchTA(Rbtree tree, PosicTree atual, PosicTree *search, char *id){
        int i;
    if (posicTreeVazio(tree, atual))
        return -1;
    searchSA(tree, getRbtreeLeft(tree, atual), search, id);
    searchSA(tree, getRbtreeRight(tree, atual), search, id);
    Torre t1 = getObjRbtree(tree, atual);
    if (strcmp(id, getTorreId(t1)) == 0){
        *search = atual;
        return 0;
    }
    return -1;
}

PosicTree searchTorre(Cidade city, char *id){
    cidade *newCity = (cidade*)city;
    Torre t1;
    PosicTree p1, search;
    searchTA(newCity->aTor, getRoot(newCity->aTor), &search, id);
    return search;
    // Posic p1;
    // for (p1 = getFirst(newCity->lTor); p1 >= 0; p1 = getNext(newCity->lTor, p1)){
    //     t1 = getObjList(newCity->lTor, p1);
    //     if (strcmp(getTorreId(t1), id) == 0){
    //         return p1;
    //     }
    // }
    // return -1;
}

int searchHA(Rbtree tree, PosicTree atual, PosicTree *search, char *id){
    int i;
    if (posicTreeVazio(tree, atual))
        return -1;
    searchSA(tree, getRbtreeLeft(tree, atual), search, id);
    searchSA(tree, getRbtreeRight(tree, atual), search, id);
    Hidrante h1 = getObjRbtree(tree, atual);
    if (strcmp(id, getHidranteId(h1)) == 0){
        *search = atual;
        return 0;
    }
    return -1;
}

PosicTree searchHidrante(Cidade city, char *id){
    cidade *newCity = (cidade*)city;
    
    PosicTree p1, search;
    searchHA(newCity->aHid, getRoot(newCity->aHid), &search, id);
    return search;

    // Posic p1;
    // for (p1 = getFirst(newCity->lHid); p1 >= 0; p1 = getNext(newCity->lHid, p1)){
    //     h1 = getObjList(newCity->lHid, p1);
    //     if (strcmp(getHidranteId(h1), id) == 0){
    //         return p1;
    //     }
    // }
    // return -1;
}

PosicTree searchEquipUrban(Cidade city, char *id, char *type){
    PosicTree p1;
    cidade *newCity = (cidade*)city;
    p1 = searchHidrante(city, id);
    if(posicTreeVazio(newCity->aHid, p1)){
        p1 = searchSemaforo(city, id);
        if(posicTreeVazio(newCity->aSem, p1)){
            p1 = searchTorre(city, id);
            if (posicTreeVazio(newCity->aTor, p1)){
                *type = 'z';
                return getNullTree(getTree(city, 't')); // vou usar o nó vazio da arvore de torres pra referenciar vazio nos comandos
            }
            else {
                *type = 't';
                return p1;
            }
        } else{
            *type = 's';
            return p1;
        }
    } else{
        *type = 'h';
        return p1;
    }
    return getNullTree(getTree(city, 't'));
}

void removeForma(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    forms *forma = getObjRbtree(newCity->aFor, p);
    Circulo c1;
    Retangulo r1;
    if (forma->type == 0){
        c1 = forma->thing;
        if (getCirculoCorContorno(c1) != NULL)
            free(getCirculoCorContorno(c1));
        if (getCirculoCorPreenchimento(c1) != NULL)
            free(getCirculoCorPreenchimento(c1));
        free(c1);
        newCity->cirQntd--;
    } else{
        r1 = forma->thing;
        if (getRetanguloCorContorno(r1) != NULL)
            free(getRetanguloCorContorno(r1));
        if (getRetanguloCorPreenchimento(r1) != NULL)
            free(getRetanguloCorPreenchimento(r1));
        free(r1);
        newCity->retQntd--;
    }
    free(forma);
    // removeList(newCity->lFor, p);
    removeRbtree(newCity->aFor, p);
}

void removeQuadra(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    Quadra q1 =/* getObjList(newCity->lQua, p);*/getObjRbtree(newCity->aQua, p);
        if (getQuadraCep(q1) != NULL)
            free(getQuadraCep(q1));
        if (getQuadraCorContorno(q1) != NULL)
            free(getQuadraCorContorno(q1));
        if (getQuadraCorPreenchimento(q1) != NULL)
            free(getQuadraCorPreenchimento(q1));
        free(q1);
    // removeList(newCity->lQua, p);
    removeRbtree(newCity->aQua, p);
}

void removeTorre(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    Torre t1 = /*getObjList(newCity->lTor, p);*/getObjRbtree(newCity->aTor, p);
    if (getTorreCorContorno(t1) != NULL)
        free(getTorreCorContorno(t1));
    if (getTorreCorPreenchimento(t1) != NULL)
        free(getTorreCorPreenchimento(t1));
    if (getTorreId(t1) != NULL)
        free(getTorreId(t1));
    free(t1);
    removeRbtree(newCity->aTor, p);
}

void removeSemaforo(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    Semaforo s1 = /*getObjList(newCity->lSem, p);*/getObjRbtree(newCity->aSem, p);
    if (getSemaforoCorContorno(s1) != NULL)
        free(getSemaforoCorContorno(s1));
    if (getSemaforoCorPreenchimento(s1) != NULL)
        free(getSemaforoCorPreenchimento(s1));
    if (getSemaforoId(s1) != NULL)
        free(getSemaforoId(s1));
    free(s1);
    // removeList(newCity->lSem, p);
    removeRbtree(newCity->aSem, p);
}

void removeHidrante(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    Hidrante h1 = /*getObjList(newCity->lHid, p);*/getObjRbtree(newCity->aHid, p);
    if (getHidranteCorContorno(h1) != NULL)
        free(getHidranteCorContorno(h1));
    if (getHidranteCorPreenchimento(h1) != NULL)
        free(getHidranteCorPreenchimento(h1));
    if (getHidranteId(h1) != NULL)
        free(getHidranteId(h1));
    free(h1);
    removeRbtree(newCity->aHid, p);
}

void removePredio(Cidade city, PosicTree p){
    cidade *newCity = (cidade*)city;
    removeRbtree(newCity->aPre, p);
}

typedef void (*removeElement)(Cidade, Posic);

void deleteListCity(Cidade city, Lista list, removeElement func){
    Posic p = getFirst(list), paux;
    for (; p >= 0;){
        paux = getNext(list, p);
        func(city, p);
        p = paux;
    }
    deleteList(list);
}

typedef void (*removeElementTree)(Cidade, PosicTree);

int delTree(Cidade city, Rbtree tree, PosicTree atual, removeElementTree func){
    if (posicTreeVazio(tree, atual))
        return -1;
    delTree(city, tree, getRbtreeLeft(tree, atual), func);
    delTree(city, tree, getRbtreeRight(tree, atual), func);
    func(city, atual);
    return 0;
}

void deleteTreeCity(Cidade city, Rbtree tree, removeElementTree func){
    delTree(city, tree, getRoot(tree), func);
    freeTree(tree);
}

void freeCidade(Cidade city){
    cidade *newCity = (cidade*)city;
    // printf("lista for\n");
    deleteTreeCity(city, newCity->aFor, &removeForma);
    deleteTreeCity(city, newCity->aPre, &removePredio);
    // printf("lista hid\n");
    deleteTreeCity(city, newCity->aHid, &removeHidrante);
    // printf("lista qua\n");
    deleteTreeCity(city, newCity->aQua, &removeQuadra);
    // printf("lista sem\n");
    deleteTreeCity(city, newCity->aSem, &removeSemaforo);
    // printf("lista tor\n");
    deleteTreeCity(city, newCity->aTor, &removeTorre);
    if (newCity != NULL)
        free(newCity);
}

void printForma(Rbtree tree, PosicTree root, FILE *svg, SvgTree funcCir, SvgTree funcRet){
    if (posicTreeVazio(tree, root))
        return;
    printForma(tree, getRbtreeLeft(tree, root), svg, funcCir, funcRet);
    printForma(tree, getRbtreeRight(tree, root), svg, funcCir, funcRet);
    forms *forma = (forms*)getObjRbtree(tree, root);
    if (forma->type == 0)
        funcCir(&svg, forma->thing);
    else
        funcRet(&svg, forma->thing);
}

void printSvgCidade(Cidade city, FILE *svg){
    cidade *newCity = (cidade*)city;
    forms *forma;
    Posic p1, type;
    printSvgRbtree(newCity->aHid, getRoot(newCity->aHid), svg, printSvgHidrante);
    printSvgRbtree(newCity->aQua, getRoot(newCity->aQua), svg, printSvgQuadra);
    printSvgRbtree(newCity->aSem, getRoot(newCity->aSem), svg, printSvgSemaforo);
    printSvgRbtree(newCity->aTor, getRoot(newCity->aTor), svg, printSvgTorre);
    printSvgRbtree(newCity->aPre, getRoot(newCity->aPre), svg, printSvgPredio);
    printSvgRbtree(newCity->aMur, getRoot(newCity->aMur), svg, printSvgMuro);
    printForma(newCity->aFor, getRoot(newCity->aFor), svg, printSvgCirculo, printSvgRetangulo);
}

void a(Lista list, Function f, int forma, va_list *ap){
    int position = getFirst(list), paux;
    forms *cor; // circulo ou retangulo
    for (;position >= 0;){
        paux = position;
        //printf("paux %d\n", paux);
        position = getNext(list, position);
        //printf("pos %d\n", position);
        if (forma){
            cor = (forms*)getObjList(list, paux);
            if(cor->type == 1){
                f(cor->thing, 1, ap);
            }else{
                f(cor->thing, 0, ap);
            }
        } else{
            f(getObjList(list, paux),ap);
        }
    }
}

void b(Rbtree tree, PosicTree root, Function f, int forma, va_list *ap){
    if (posicTreeVazio(tree, root))
        return;
    b(tree, getRbtreeLeft(tree, root), f, forma, ap);
    b(tree, getRbtreeRight(tree, root), f, forma, ap);
    if(forma){
        forms *fm = (forms*)getObjRbtree(tree, root);
        if (fm->type == 1)
            f(fm->thing, 1, ap);
        else
            f(fm->thing, 0, ap);
        
    } else
        f(getObjRbtree(tree, root), ap);
}

void throughCity (Cidade city, Function f, ...){
    char t;
    va_list ap;
    va_start(ap, f);
    t = va_arg(ap, int);
    cidade *newCity = (cidade*)city;
    if (t == 'q'){
        // a(newCity->lQua, f, 0, &ap);
        b(newCity->aQua, getRoot(newCity->aQua), f, 0, &ap);
    } else if (t == 't'){
        // a(newCity->lTor, f, 0, &ap);
        b(newCity->aTor, getRoot(newCity->aTor), f, 0, &ap);
    } else if (t == 'h'){
        // a(newCity->lHid, f, 0, &ap);
        b(newCity->aHid, getRoot(newCity->aHid), f, 0, &ap);
    } else if (t == 's'){
        // a(newCity->lSem, f, 0, &ap);
        b(newCity->aSem, getRoot(newCity->aSem), f, 0, &ap);
    } else if (t == 'f'){
        // a(newCity->lFor, f, 1, &ap);
        b(newCity->aFor, getRoot(newCity->aFor), f, 1, &ap);
    } else if (t == 'p'){
        // a(newCity->lPre, f, 0, &ap);
        b(newCity->aPre, getRoot(newCity->aPre), f, 0, &ap);
    } else if (t == 'm'){
        // a(newCity->lMur, f, 0, &ap);
        b(newCity->aMur, getRoot(newCity->aMur), f, 0, &ap);
    }
    va_end(ap);
}
