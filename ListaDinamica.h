#ifndef LISTADINAMICA_H
#define LISTADINAMICA_H

	typedef void *ListaDinamica;
	typedef void *PosicLD;
	typedef void *Item;
	typedef void (*RemoveLeak)(Item);

	ListaDinamica createDinamicList();
	int DinamicListlength(ListaDinamica L);
	PosicLD insertDinamicList(ListaDinamica L, Item info);
	void removeDinamicList(ListaDinamica L, PosicLD p);
	void deleteDinamicListComplete(ListaDinamica L, RemoveLeak equipament);
	PosicLD insertDinamicListBefore(ListaDinamica L, PosicLD p, Item info);
	PosicLD insertDinamicListAfter(ListaDinamica L, PosicLD p, Item info);
	PosicLD getFirstDinamicList(ListaDinamica L);
	PosicLD getNextDinamicList(PosicLD p);
	PosicLD getLastDinamicList(ListaDinamica L);
	PosicLD getPreviousDinamicList(PosicLD p);
	Item getObjtDinamicList(PosicLD p);

	/*RETORNA O CONTEÚDO DO NÓ DA ListaDinamica E POSIÇÃO P*/
#endif

