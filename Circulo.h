#ifndef CIRCULO_H
#define CIRCULO_H

	typedef void *Circulo;

Circulo creatCirculo(int id, double raio, double x, double y, char *corPreenchimento, char *corContorno, double sw);
double getCirculoX(Circulo c);
double getCirculoSW(Circulo c);
double getCirculoY(Circulo c);
double getCirculoRaio(Circulo c);
int getCirculoId(Circulo c);
char *getCirculoCorPreenchimento(Circulo c);
char *getCirculoCorContorno(Circulo c);
void freeCirculo(Circulo c);
#endif