#ifndef RETANGULO_H
#define RETANGULO_H
#include <stdio.h>

	typedef void *Retangulo;

Retangulo creatRetangulo(int id, double width, double height, double x, double y, char *corPreenchimento, char *corContorno, double sw);
int getRetanguloId(Retangulo r);
double getRetanguloSW(Retangulo r);
double getRetanguloWidth(Retangulo r);
double getRetanguloHeight(Retangulo r);
double getRetanguloX(Retangulo r);
double getRetanguloY(Retangulo r);
char *getRetanguloCorPreenchimento(Retangulo r);
char *getRetanguloCorContorno(Retangulo r);
void freeCor(Retangulo r);
void freeRetangulo(Retangulo r);

#endif