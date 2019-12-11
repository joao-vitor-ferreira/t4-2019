#ifndef PONTO_H
#define PONTO_H

    /* Um Ponto é uma coordenada no plano cartesiano bidimensional, nos eixos x e y */
    typedef void *Ponto;

Ponto createPonto(double x, double y);
double getPontoX(Ponto p);
double getPontoY(Ponto p);
// void *getPontoObj(Ponto p);
void setPontoX(Ponto p, double x);
void setPontoY(Ponto p, double y);
void freePonto(Ponto p);

#endif