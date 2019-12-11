#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
	/*
	
	O Objeto Lista é uma lista de elementos dispostos estaticamente (em um vetor) o qual armazena em si outro objeto
	
	*/

	typedef void *Lista;
	
	typedef int Posic;
	/*Refere-se ao indicar da posição de um objeto na lista */
	typedef void *Item;
	/*Abstração de quaquer objeto a ser armazenado */
	typedef void (*svgColor)(FILE **, void *);

	Lista createList(int size);
	/* Cria uma instancia de Lista com nx elementos*/
	int lengthList(Lista L);
	/* Informa o tamanho da Lista*/
	int qtdList(Lista L);
	/* Informa quantos elementos existem na lista*/
	Posic insertList(Lista L, Item info);
	/* Adiciona uma informação)(Elemento) na Lista, porém a se a lista estiver cheia ele retorna null*/
	void removeList(Lista L, Posic p);
	/* remove um elemento da lista em Posic p */
	void deleteList(Lista L);
	/* Remove todos os elementos da Lista, deixando a lista vazia*/
	Posic getFirst(Lista L);
	/* Função que devolve o Posic referente ao primeiro elemento da lista*/
	Posic getNext(Lista L, Posic p);
	/* Dado uma posição na lista, esta função devolve o Posic do posterior a ele*/
	Posic getLast(Lista L);
	/* Dado uma lista, esta função devolve o Posic do último elemento da lista*/
	Posic getPrevious(Lista L,Posic p);
	/*Dado uma lista, esta função devolve o Posic anterior ao Posic p */
	Item getObjList(Lista L, Posic p);
	/* Dado uma lista, esta função retorna o objeto referente ao Posic p*/
	void printSvgList(Lista L, FILE *svg, svgColor printElement);
	/* imprime no arquivo svg o determinado objeto da lista*/
#endif

