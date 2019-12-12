#ifndef TIPOEC_H
#define TIPOEC_H

    typedef void *TipoEC;

TipoEC createTipoEc(char *codt, char *descricao);
char *getTipoECCodt(TipoEC t);
char *getTipoECDescricao(TipoEC t);
void freeTipoECDescricao(TipoEC t);

#endif