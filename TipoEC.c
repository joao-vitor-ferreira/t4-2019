#include <stdio.h>
#include "TipoEC.h"

typedef struct {
    char *codt;
    char *descricao;
}tipo_ec;

TipoEC createTipoEc(char *codt, char *descricao){
    tipo_ec *newTipo;
    newTipo = (tipo_ec*)malloc(sizeof(tipo_ec));
    newTipo->codt = codt;
    newTipo->descricao = descricao;
    return newTipo;
}

char *getTipoECCodt(TipoEC t){
    tipo_ec *newTipo = (tipo_ec*)t;
    return newTipo->codt;
}

char *getTipoECDescricao(TipoEC t){
    tipo_ec *newTipo = (tipo_ec*)t;
    return newTipo->descricao;
}

void freeTipoECDescricao(TipoEC t){
    tipo_ec *newTipo = (tipo_ec*)t;
    if (newTipo != NULL)
        free(newTipo);
}   