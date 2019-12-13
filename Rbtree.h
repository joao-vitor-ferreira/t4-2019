#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define NB_ELEMS 5
#define false 0;
#define true 1;

typedef int bool;
typedef void *Rbtree;
typedef void *PosicTree;
typedef void *Item;
typedef void *Forma;

// Cria a arvoree retora um Rbtree (void pointer)
Rbtree createTree();

// Dado umvoid poiter tree (head), retorna o void pointer para a raiz
PosicTree getRoot(Rbtree tree);

// Função utilitária para inserir novo nó na árvore Red Black
void insertRbtree(Rbtree *tree, Item data,double x, double y);

// Uma função utilitária para percorrer a árvore Vermelho-Preto de maneira inorder
void printTree(Rbtree tree);

// Retorna o numero total de elementos
int qtdRbtree(Rbtree tree);

/* Dada uma árvore de pesquisa binária e uma chave, essa função exclui a chave
    e retorna a nova raiz */
void delete(Rbtree tree, int data);

Item getObjRbtree(Rbtree tree, PosicTree p);
void removeRbtree(Rbtree tree, PosicTree p);
