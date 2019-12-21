#ifndef FILA_DE_PRIORIDADE_H
#define FILA_DE_PRIORIDADE_H

/*Tipo abstrato para uma fila de prioridade*/
    typedef void *Fila;
/*cria uma fila de prioridade vazia*/
Fila createFila();
/*adiciona um elemento Item na fila com prioridade prioridade*/
void addFila(Fila f, void *item, int prioridade);
/*extrai o elemento de maior prioridade da fila, mas não o remove da fila, só não o eh mais considerado*/
void *extrairFila(Fila f);

#endif