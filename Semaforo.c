#include <stdio.h>
#include "Semaforo.h"
#include <stdlib.h>
#include "Calculos.h"
#include "Retangulo.h"

typedef struct{
	double x;
	double y;
	char *id;
	char *corPreenchimento;
	char *corContorno;
	double especura_borda;
}semaforo;

Semaforo createSemaforo(double x, double y, char *id, double sw){
	semaforo *newSemaforo;
	newSemaforo = (semaforo*)malloc(sizeof(semaforo));
	newSemaforo->x = x;
	newSemaforo->y = y;
	newSemaforo->id = id;
	newSemaforo->especura_borda = sw;
	newSemaforo->corContorno = NULL;
	newSemaforo->corPreenchimento = NULL;
	return (Semaforo)newSemaforo;
}

double getSemaforoSW(Semaforo h){
	semaforo *newSemaforo = (semaforo*)h;
	return newSemaforo->especura_borda;
}

double getSemaforoX(Semaforo h){
	semaforo *newSemaforo = (semaforo*)h;
	return newSemaforo->x;
}

double getSemaforoY(Semaforo h){
	semaforo *newSemaforo = (semaforo*)h;
	return newSemaforo->y;
}

char *getSemaforoId(Semaforo h){
	semaforo *newSemaforo = (semaforo*)h;
	return newSemaforo->id;
}

char *getSemaforoCorPreenchimento(Semaforo h){
	semaforo *newSemaforo = (semaforo*)h;
	return newSemaforo->corPreenchimento;
}

char *getSemaforoCorContorno(Semaforo h){
	semaforo *newSemaforo = (semaforo*)h;
	return newSemaforo->corContorno;
}

void setSemaforoCorPreenchimento(Semaforo h, char *cor){
	semaforo *newSemaforo = (semaforo*)h;
	if (newSemaforo->corPreenchimento != NULL)
		free(newSemaforo->corPreenchimento);
	newSemaforo->corPreenchimento = cor;
}

void setSemaforoCorContorno(Semaforo h, char *cor){
	semaforo *newSemaforo = (semaforo*)h;
	if (newSemaforo->corContorno != NULL)
		free(newSemaforo->corContorno);
	newSemaforo->corContorno = cor;
}

void setSemaforoX(Semaforo s, double x){
	semaforo *newSemaforo = (semaforo*)s;
	newSemaforo->x += x;
}

void setSemaforoY(Semaforo s, double y){
	semaforo *newSemaforo = (semaforo*)s;
	newSemaforo->y += y;
}

int semaforoInternoRetangulo(FILE **txt, Semaforo s, Retangulo r){
	if (pontoInternoRetangulo(r, getSemaforoX(s), getSemaforoY(s)) == 1){
		if (*txt != NULL)		
			fprintf(*txt, "%s %f %f %s %s\n", getSemaforoId(s), getSemaforoX(s), getSemaforoY(s), getSemaforoCorPreenchimento(s), getSemaforoCorContorno(s));
		return 1;
	}
	return 0;
}

int semaforoInternoCirculo(FILE **txt, Semaforo s, Circulo c){
	if (pontoInternoCirculo(c, getSemaforoX(s), getSemaforoY(s)) == 1){
		if (*txt != NULL)
			fprintf(*txt, "%s %f %f %s %s\n", getSemaforoId(s), getSemaforoX(s), getSemaforoY(s), getSemaforoCorPreenchimento(s), getSemaforoCorContorno(s));
		return 1;
	}
	return 0;
}

void freeSemaforo(Semaforo s){
	semaforo *newSemaforo = (semaforo*)s;
	if (newSemaforo->corContorno != NULL)
		free(newSemaforo->corContorno);
	if (newSemaforo->corPreenchimento != NULL)
		free(newSemaforo->corPreenchimento);
	if (newSemaforo->id != NULL)
		free(newSemaforo->id);
}