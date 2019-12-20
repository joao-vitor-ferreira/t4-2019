#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Comandos.h"
#include "Lista.h"
#include "Quadra.h"
#include "Torre.h"
#include "Semaforo.h"
#include "Hidrante.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Calculos.h"
#include "Svg.h"
#include "Vector.h"
#include "Segmento.h"
#include "Vertice.h"
#include "Ponto.h"
#include "Ordenacao.h"
#include "TipoEC.h"
#include "Pessoa.h"
#include "Rbtree.h"
#include "Poligono.h"
#include "GrafoDirecionado.h"

void funcFree(char **a){
	if (a == NULL){
		printf("ERRO\n");
	} else{
		free(*a);
		*a = NULL;
	}
}

char *colocaBarra(char *str){
	if (str == NULL)
		return NULL;
	char *ret;
	if (str[strlen(str)-1] != '/'){
		ret = (char*)malloc(sizeof(char)*(strlen(str) +2));
		sprintf(ret, "%s/", str);
	} else {
		ret = (char*)malloc(sizeof(char)*(strlen(str) + 1));
		strcpy(ret, str);
	}
	return ret;
}

char *concatena(char *str1, char *str2){
	char *aux;

	if (str1 == NULL){
		if (str2 == NULL){
			return NULL;
		} else{
			aux = (char*)malloc(sizeof(char)*(strlen(str2) + 1));
			strcpy(aux, str2);
			return aux;
		}
	} else{
		if (str2 == NULL){
			aux = (char*)malloc(sizeof(char)*(strlen(str1) + 1));
			strcpy(aux, str1);
			return aux;
		} else{
			aux = (char*)malloc(sizeof(char)*(strlen(str1) + strlen(str2) +1));
			strcpy(aux, str1);
			strcat(aux, str2);
			return aux;
		}
	}
}

char *pegaParametro(int argc, char *argv[], char *str){
	int i;
	for (i = 0; i<argc; i++){
		if (strcmp(str, argv[i]) == 0){
			if(strcmp(argv[i], "-i") == 0)
				return argv[i];
			else
				return argv[i+1];
		}
	}
	return NULL;
}

void printSvgVector(Vector vetor, FILE *svg){
	int n, i;
	Circulo c1 = NULL;
	Retangulo r1 = NULL;
	for (i = 0; i < (getSizeVector(vetor)); i++){
		n = getTypeObj(vetor, i);
		if (n == 0){	
			c1 = getObjVector(vetor, i);
			printSvgCirculo(&svg, c1);
		} else if (n == 1){
			r1 = getObjVector(vetor, i);
			printSvgRetangulo(&svg, r1);
		}
	}
}

int countQry(char *str){
	int a, ret = 0;
	for (a=strlen(str)-1; a>=0; a--){
		if (str[a] != '/')
			ret++;
		else
			break;
	}
	return ret;
}

char *pegaNomeBase(char *str){
	int i, j, count;
	char *name;
	count = countQry(str);
	name = (char*)malloc(sizeof(char)*(count -3));
	for(i = strlen(str) - count, j = 0; i<(strlen(str)-4); i++, j++){
		name[j] = str[i];
	}
	name[j] = '\0';
	return name;
}


char *funcTxt(int argc, char **argv){
	int i;
	char *aux1 = NULL, *aux2 = NULL, *aux3 = NULL, *aux4 = NULL;
	aux2 = colocaBarra(pegaParametro(argc, argv, "-o"));
	aux1 = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	aux4 = pegaNomeBase(pegaParametro(argc, argv, "-q"));
	aux3 = (char*)malloc(sizeof(char)*(strlen(aux2) + strlen(aux1) + strlen(aux4) + 6));
	strcpy(aux3, aux2);
	strcat(aux3, aux1);
	strcat(aux3, "-");
	strcat(aux3, aux4);
	strcat(aux3, ".txt");
	funcFree(&aux2);
	funcFree(&aux1);
	funcFree(&aux4);
	return aux3;
}

char *funcSvgMain(int argc, char *argv[], char *str){
	char *ret = NULL, *dir = NULL, *uu;
	dir = colocaBarra(pegaParametro(argc, argv, "-o"));
	uu = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	ret = concatena(dir, uu);
	funcFree(&uu);
	uu = concatena(ret, ".svg");
	funcFree(&ret);
	funcFree(&dir);
	return uu;
}

char *funcSvg(int argc, char **argv){
	int i;
	char *aux = NULL, *strdir = NULL, *aux2 = NULL, *aux3 = NULL, *aux4 = NULL;
	strdir = colocaBarra(pegaParametro(argc, argv, "-o"));
	aux = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	aux2 = pegaNomeBase(pegaParametro(argc, argv, "-q"));
	aux3 = (char*)malloc(sizeof(char)*(strlen(strdir) + strlen(aux) + strlen(aux2) + 6));
	strcpy(aux3, strdir);
	funcFree(&strdir);
	strcat(aux3, aux);
	strcat(aux3, "-");
	strcat(aux3, aux2);
	strcat(aux3, ".svg");
	funcFree(&aux);
	funcFree(&aux2);
	return aux3;
}

int barraQry(char *str){
	int a, ret= -1;
	for (a=strlen(str)-1; a>=0; a--){
		if (str[a] == '/'){
			ret = a;
			break;
		}
	}
	return ret;
}

double modulo(double value){
	if (value<0)
		value *= -1;
	return value;
}

void cmpRet(Retangulo r1, double *xma, double *xme, double *yma, double *yme){
	if (*xme < 0)
		*xme = getRetanguloX(r1);
	if (*yme < 0)
		*yme = getRetanguloY(r1);
	if (getRetanguloX(r1) < *xme)
		*xme = getRetanguloX(r1);
	if (getRetanguloY(r1) < *yme)
		*yme = getRetanguloY(r1);
	if ((getRetanguloX(r1) + getRetanguloWidth(r1)) > *xma)
		*xma = getRetanguloX(r1) + getRetanguloWidth(r1);
	if ((getRetanguloY(r1) + getRetanguloHeight(r1)) > *yma)
		*yma = getRetanguloY(r1) + getRetanguloHeight(r1);
}

void cmpCir(Circulo c1, double *xma, double *xme, double *yma, double *yme){
	if (*xme < 0)
		*xme = getCirculoX(c1) - getCirculoRaio(c1);
	if (*yme < 0)
		*yme = getCirculoY(c1) - getCirculoRaio(c1);
	if ((getCirculoX(c1) - getCirculoRaio(c1)) < *xme)
		*xme = (getCirculoX(c1) - getCirculoRaio(c1));
	if ((getCirculoY(c1) - getCirculoRaio(c1)) < *yme)
		*yme = getCirculoY(c1) - getCirculoRaio(c1);
	if ((getCirculoX(c1) + getCirculoRaio(c1)) > *xma)
		*xma = getCirculoX(c1) + getCirculoRaio(c1);
	if ((getCirculoY(c1) + getCirculoRaio(c1)) > *yma)
		*yma = getCirculoY(c1) + getCirculoRaio(c1);
}

void svgCmpCirculo(double *svgH, double *svgW, double x, double y, double raio){
	if ((x+raio) > (*svgW))
		*svgW = x+raio;
	if ((y+raio) > (*svgH))
		*svgH = y+raio;
}

void svgCmpRetangulo(double *svgH, double *svgW, double x, double y, double height, double width){
	if ((x + width) > (*svgW))
		*svgW = x + width;
	if ((y+height) > (*svgH))
		*svgH = y + height;
}

void svgVwQ(Quadra q, ...){
	va_list ap1, *ap2, ap3;
	double *svgH, *svgW;
	va_start(ap1, q);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	svgW = va_arg(ap3, double*);
	svgH = va_arg(ap3, double*);
	svgCmpRetangulo(svgH, svgW, getQuadraX(q), getQuadraY(q), getQuadraHeight(q), getQuadraWidth(q));
}

void svgVwSem(Semaforo s, ...){
	double *svgH, *svgW;
	va_list ap1, *ap2, ap3;
	va_start(ap1, s);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	svgW = va_arg(ap3, double*);
	svgH = va_arg(ap3, double*);
	svgCmpCirculo(svgH, svgW, getSemaforoX(s), getSemaforoY(s), 1.0);
}

void svgVwHid (Hidrante h, ...){
	double *svgH, *svgW;
	va_list ap1, *ap2, ap3;
	va_start(ap1, h);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	svgW = va_arg(ap3, double*);
	svgH = va_arg(ap3, double*);
	svgCmpCirculo(svgH, svgW, getHidranteX(h), getHidranteY(h), 1.0);
}

void svgVwTor (Torre t, ...){
	double *svgH, *svgW;
	va_list ap1, *ap2, ap3;
	va_start(ap1, t);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	svgW = va_arg(ap3, double*);
	svgH = va_arg(ap3, double*);
	svgCmpCirculo(svgH, svgW, getTorreX(t), getTorreY(t), 1.0);
}

void svgVwFor (void *t, ...){
	double *svgH, *svgW;
	int type;
	va_list ap1, *ap2, ap3;
	va_start(ap1, t);
	type = va_arg(ap1, int);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	svgW = va_arg(ap3, double*);
	svgH = va_arg(ap3, double*);
	if (type){
		svgCmpRetangulo(svgH, svgW, getRetanguloX(t), getRetanguloY(t), getRetanguloHeight(t), getRetanguloWidth(t));
	} else {
		svgCmpCirculo(svgH, svgW, getCirculoX(t), getCirculoY(t), 1.0);
	}
	
}

void calcViewBoxSvg(Cidade city, double *svgW, double *svgH){
	throughCity(city, &svgVwQ, 'q', svgW, svgH);
	throughCity(city, &svgVwSem, 's', svgW, svgH);
	throughCity(city, &svgVwHid, 'h', svgW, svgH);
	throughCity(city, &svgVwTor, 't', svgW, svgH);
	throughCity(city, &svgVwFor, 'f', svgW, svgH);
}

// void segOfRet(Lista lseg, Vector vetVert, int pos, double xi, double yi, double xf, double yf){
// 	Vertice vIni, vFim;
// 	Segmento seg;
// 	seg = createSegmento(xi, yi, xf, yf);
// 	vIni = createVertice(xi, yi, "original", 'i', seg);
// 	vFim = createVertice(xf, yf, "original", 'f', seg);
// 	insertList(lseg, seg);
// 	addVector(vetVert, vIni, pos, 0);
// 	pos++;
// 	addVector(vetVert, vFim, pos, 0);
// 	pos++;
// }

void leituraGeo(int argc, char **argv, double *svgH, double *svgW, FILE *svgMain, Cidade *city){
	int NQ = 1000, NS = 10000, NH = 10000, NR = 10000, NF = 10000, NP = 10000, NM = 10000, i, type;
	*city = createCidade();
	FILE *entrada = NULL;
	Circulo c1 = NULL;
	PosicTree p1;
	Retangulo r1 = NULL;
	Quadra q1;
	Semaforo s1;
	Torre t1;
	Hidrante h1; 
	Predio pre;
	Muro mur;
	char face;
	char *line = NULL, *word = NULL, *cor1 = NULL, *cor2 = NULL, 
	*aux = NULL, *aux2 = NULL, *aux3 = NULL, *text = NULL, *cep, *cqf, *cqs, *chf, *chs, *crf, *crs, *csf, *css;
	double raio, x, y, height, width, sw, swc, swr, swq, swt, sws, swh, prof, mrg, frt, xa, ya;
	line = (char*)malloc(sizeof(char)*200);
	word =(char*)malloc(sizeof(char)*30);
	cor1 = (char*)malloc(sizeof(char)*20);
	cqf = (char*)malloc(sizeof(char)*20);
	cqs = (char*)malloc(sizeof(char)*20);
	chs = (char*)malloc(sizeof(char)*20);
	chf = (char*)malloc(sizeof(char)*20);
	crf = (char*)malloc(sizeof(char)*20);
	crs = (char*)malloc(sizeof(char)*20);
	css = (char*)malloc(sizeof(char)*20);
	csf = (char*)malloc(sizeof(char)*20);
	cep = (char*)malloc(sizeof(char)*20);
	cor2 = (char*)malloc(sizeof(char)*20);
	text = (char*)malloc(sizeof(char)*200);
	aux = colocaBarra(pegaParametro(argc, argv, "-e"));
	aux2 = concatena(aux, pegaParametro(argc, argv, "-f"));
	entrada = fopen(aux2, "r");
		if(entrada == NULL){
		printf("DIRETÓRIO OU ARQUIVO INVÁLIDOS\n");
		return;
	}
	funcFree(&aux);
	funcFree(&aux2);

	while(!feof(entrada)){
		fscanf(entrada, "%[^\n]\n", line);
		sscanf(line, "%s", word);
		if (strcmp(word, "sw") == 0){
			sscanf(line, "%s %lf %lf", word, &swc, &swr);
		}else if (strcmp(word, "nx") == 0){
			sscanf(line, "%s %d %d %d %d %d %d %d", word, &NF, &NQ, &NH, &NS, &NR, &NP, &NM);
			// *city = createCidade(NF, NQ, NH, NS, NR, NP, NM);
		}else if (strcmp(word, "cq") == 0){
			funcFree(&cqf);
			funcFree(&cqs);
			sscanf(line, "%s %s %s %lf", word, cor1, cor2, &swq);
			cqf = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			cqs = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(cqf, cor1);
			strcpy(cqs, cor2);
		}else if (strcmp(word, "cs") == 0){
			funcFree(&csf);
			funcFree(&css);
			sscanf(line, "%s %s %s %lf", word, cor1, cor2, &sws);
			csf = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			css = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(csf, cor1);
			strcpy(css, cor2);
		}else if (strcmp(word, "ch") == 0){
			funcFree(&chf);
			funcFree(&chs);
			sscanf(line, "%s %s %s %lf", word, cor1, cor2, &swh);
			chf = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			chs = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(chf, cor1);
			strcpy(chs, cor2);
		}else if (strcmp(word, "cr") == 0){
			funcFree(&crf);
			funcFree(&crs);
			sscanf(line, "%s %s %s %lf", word, cor1, cor2, &swt);
			crf = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			crs = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(crf, cor1);
			strcpy(crs, cor2);
		}else if (strcmp(word, "c") == 0){
			sscanf(line, "%s %d %lf %lf %lf %s %s", word, &i, &raio, &x, &y, cor1, cor2);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			c1 = creatCirculo(i, raio, x, y, aux2, aux, swc);
			addForma(*city, c1, 0);
			svgCmpCirculo(svgH, svgW, x, y, raio);
		}else if (strcmp(word, "r") == 0){
			sscanf(line, "%s %d %lf %lf %lf %lf %s %s", word, &i, &width, &height, &x, &y, cor1, cor2);
			aux = (char*)malloc(sizeof(char)*(strlen(cor1) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cor2) + 1));
			strcpy(aux, cor1);
			strcpy(aux2, cor2);
			r1 = creatRetangulo(i, width, height, x, y, aux2, aux, swr);
			addForma(*city, r1, 1);
			svgCmpRetangulo(svgH, svgW, x, y, height, width);
		} else if (strcmp(word, "t") == 0){
			sscanf(line, "%s %lf %lf %[^\n]", word, &x, &y, text);
			fprintf(svgMain, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%s</text>\n", x, y, text);
			svgCmpCirculo(svgH, svgW, x, y, 0.0);
		} else if (strcmp(word, "q") == 0){
			sscanf(line, "%s %s %lf %lf %lf %lf", word, cep, &x, &y, &width, &height);
			aux = (char*)malloc(sizeof(char)*(strlen(cqf) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(cqs) + 1));
			aux3 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, cqf);
			strcpy(aux2, cqs);
			strcpy(aux3, cep);
			q1 = createQuadra(x, y, width, height, aux3, swq);
			setQuadraCorContorno(q1, aux2);
			setQuadraCorPreenchimento(q1, aux);
			addQuadra(*city, q1);
			svgCmpRetangulo(svgH, svgW, x, y, height, width);
		} else if (strcmp(word, "rb") == 0){
			sscanf(line, "%s %s %lf %lf", word, cep, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(crf) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(crs) + 1));
			aux3 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, crf);
			strcpy(aux2, crs);
			strcpy(aux3, cep);
			t1 = createTorre(x, y, aux3, swt);
			setTorreCorContorno(t1, aux2);
			setTorreCorPreenchimento(t1, aux);
			addTorre(*city, t1);
			svgCmpCirculo(svgH, svgW, x, y, swt);
		} else if (strcmp(word, "s") == 0){
			sscanf(line, "%s %s %lf %lf", word, cep, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(csf) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(css) + 1));
			aux3 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, csf);
			strcpy(aux2, css);
			strcpy(aux3, cep);
			s1 = createSemaforo(x, y, aux3, sws);
			setSemaforoCorContorno(s1, aux2);
			setSemaforoCorPreenchimento(s1, aux);
			addSemaforo(*city, s1);
			svgCmpCirculo(svgH, svgW, x, y, sws);
		} else if (strcmp(word , "h")==0){
			sscanf(line, "%s %s %lf %lf", word, cep, &x, &y);
			aux = (char*)malloc(sizeof(char)*(strlen(chf) + 1));
			aux2 = (char*)malloc(sizeof(char)*(strlen(chs) + 1));
			aux3 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, chf);
			strcpy(aux2, chs);
			strcpy(aux3, cep);
			h1 = createHidrante(x, y, aux3, swt);
			setHidranteCorContorno(h1, aux2);
			setHidranteCorPreenchimento(h1, aux);
			addHidrante(*city, h1);
			svgCmpCirculo(svgH, svgW, x, y, swh);
		} else if (strcmp(word, "prd") == 0){
			sscanf(line, "%s %s %c %d %lf %lf %lf", word, cep, &face, &i, &frt, &prof, &mrg);
			aux = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			p1 = searchQuadra(*city, cep);
			q1 = getObjQuadra(*city, p1);
			pre = createPredio(face,i, frt, prof, mrg, q1);
			addPredio(*city, pre);
		} else if (strcmp(word, "mur") == 0){
			sscanf(line, "%s %lf %lf %lf %lf", word, &x, &y, &xa, &ya);
			Ponto p1, p2;
			p1 = createPonto(x, y);
			p2 = createPonto(xa, ya);
			mur = createMuro(p1, p2);
			addMuro(*city, mur);
		}
	}
		// printTree(getCidadeRbtree(*city, 't'));
		// printf("acabo arvore\n");
		// getchar();
	calcViewBoxSvg(*city, svgW, svgH);
	funcFree(&cep);
	funcFree(&cqf);
	funcFree(&cqs);
	funcFree(&chf);
	funcFree(&chs);
	funcFree(&crf);
	funcFree(&crs);
	funcFree(&csf);
	funcFree(&css);
	funcFree(&line);
	funcFree(&word);
	funcFree(&cor1);
	funcFree(&cor2);
	funcFree(&text);
	fclose(entrada);
}

void leituraEC(int argc, char **argv, Cidade *city){
	FILE *entrada;
	TipoEC tp1;
	Estab ec;
	int num;
	char face;
	char line[200], word[30], cep[20], suf[20], cnpj[20], cpf[20], codt[20], nome[20], *aux = NULL, *aux2 = NULL, *aux3 = NULL, *aux4 = NULL, *aux5 = NULL;
	double raio, x, y, height, width, sw, swc, swr, swq, swt, sws, swh, prof, mrg, frt, xa, ya;
	aux = colocaBarra(pegaParametro(argc, argv, "-e"));
	aux2 = concatena(aux, pegaParametro(argc, argv, "-ec"));
	entrada = fopen(aux2, "r");
		if(entrada == NULL){
		printf("DIRETÓRIO OU ARQUIVO INVÁLIDOS\n");
		return;
	}
	funcFree(&aux);
	funcFree(&aux2);
	while (!feof(entrada)){
		fscanf(entrada, "%[^\n]\n", line);
		sscanf(line, "%s", word);
		if (strcmp(word, "t") == 0)	{
			sscanf(line, "%s %s %s", word, cep, suf);
			aux = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux, cep);
			aux2 = (char*)malloc(sizeof(char)*(strlen(suf) + 1));
			strcpy(aux2, suf);
			tp1 = createTipoEc(aux, aux2);
			addTipoEC(*city, tp1);
		} else if  (strcmp(word, "e") == 0){
			sscanf(line, "%s %s %s %s %s %c %d %s", word, cnpj, cpf, codt, cep, &face, &num, nome);
			
			aux = (char*)malloc(sizeof(char)*(strlen(cnpj) + 1));
			strcpy(aux, cnpj);
			aux2 = (char*)malloc(sizeof(char)*(strlen(cpf) + 1));
			strcpy(aux2, cpf);
			aux3 = (char*)malloc(sizeof(char)*(strlen(codt) + 1));
			strcpy(aux3, codt);
			aux4 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux4, cep);
			aux5 = (char*)malloc(sizeof(char)*(strlen(nome) + 1));
			strcpy(aux5, nome);
			ec = createEstab(aux, aux2, aux3, aux4, face, num, aux5);

			addEstabCom(*city, ec);
		}
	}
	fclose(entrada);
}

void leituraPM(int argc, char **argv, Cidade *city){
	FILE *entrada;
	Pessoa ps1;
	Predio pr1;
	Morador mr1;
	Quadra q1;
	PosicTree p1, p2;
	int num;
	char face;
	char line[200], word[30], cep[20], suf[20], cnpj[20], cpf[20], codt[20], nome[20], sexo, nasc[20], *aux = NULL, *aux2 = NULL, *aux3 = NULL, *aux4 = NULL, *aux5 = NULL;
	double raio, x, y, height, width, sw, swc, swr, swq, swt, sws, swh, prof, mrg, frt, xa, ya;
	aux = colocaBarra(pegaParametro(argc, argv, "-e"));
	aux2 = concatena(aux, pegaParametro(argc, argv, "-pm"));
	entrada = fopen(aux2, "r");
		if(entrada == NULL){
		printf("DIRETÓRIO OU ARQUIVO INVÁLIDOS\n");
		return;
	}
	funcFree(&aux);
	funcFree(&aux2);
	while (!feof(entrada)){
		fscanf(entrada, "%[^\n]\n", line);
		sscanf(line, "%s", word);
		if (strcmp(word, "p") == 0)	{
			sscanf(line, "%s %s %s %s %c %s", word, cpf, nome, suf, &sexo, nasc);
			aux = (char*)malloc(sizeof(char)*(strlen(cpf) + 1));
			strcpy(aux, cpf);
			aux2 = (char*)malloc(sizeof(char)*(strlen(nome) + 1));
			strcpy(aux2, nome);
			aux3 = (char*)malloc(sizeof(char)*(strlen(suf) + 1));
			strcpy(aux3, suf);
			aux5 = (char*)malloc(sizeof(char)*(strlen(nasc) + 1));
			strcpy(aux5, nasc);
			ps1 = createPessoa(aux, aux2, aux3, sexo, aux5);
			addPessoa(*city, ps1);

		} else if  (strcmp(word, "m") == 0){
			sscanf(line, "%s %s %s %c %d %s", word, cpf, cep, &face, &num, suf);
			aux = (char*)malloc(sizeof(char)*(strlen(suf) + 1));
			strcpy(aux, suf);
			aux2 = (char*)malloc(sizeof(char)*(strlen(cpf) + 1));
			strcpy(aux2, cpf);
			aux3 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
			strcpy(aux3, cep);						
			ps1 = searchPessoaXCpf(*city, cpf);
			PosicTree pa1 = searchPredio(*city, cep, face, num);
			if (posicTreeVazio(getCidadeRbtree(*city, 'p'), pa1))
				pr1 = NULL;
			else
				pr1 = getObjPredio(*city, pa1);
			mr1 = createMorador(ps1, pr1, aux2, aux3, face, num, aux);
			p1 = searchQuadra(*city, cep);
			if (!posicTreeVazio(getTree(*city, 'q'), p1)){
				q1 = getObjQuadra(*city, p1);
				addQuadraMorador(q1, mr1);
			}
			addMorador(*city, mr1);
		}
	}
	fclose(entrada);
}

char *funcSvgBb(int argc, char **argv, char *suf){
	char *dir, *qry, *bb, *aux, *geo;
	dir = colocaBarra(pegaParametro(argc, argv, "-o"));
	qry = pegaNomeBase(pegaParametro(argc, argv, "-q"));
	geo = pegaNomeBase(pegaParametro(argc, argv, "-f"));
	aux = concatena(dir, geo);
	funcFree(&dir);
	bb = concatena(aux, "-");
	funcFree(&aux);
	aux = concatena(bb, qry);
	funcFree(&bb);
	bb = concatena(aux, "-");
	funcFree(&aux);
	aux = concatena(bb, suf);
	funcFree(&bb);
	bb = concatena(aux, ".svg");
	funcFree(&aux);
	funcFree(&qry);
	funcFree(&geo);
	return bb;
}

void bb(void *thing, ...){
	Retangulo r;
	Circulo c;
	va_list ap1, *ap2, ap3;
	char *cor;
	int type;
	FILE *arq;

	va_start(ap1, thing);
	type = va_arg(ap1, int);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	arq = va_arg(ap3, FILE*);
	cor = va_arg(ap3, char*);
	if (type == 1){
		r = (Retangulo)thing;
		fprintf(arq, "<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" style=\"fill:%s\" />\n", getRetanguloX(r) + getRetanguloWidth(r)/2, getRetanguloY(r) + getRetanguloHeight(r)/2, getRetanguloWidth(r)/2, getRetanguloHeight(r)/2, cor);
	} else {
		c = (Circulo)thing;
		fprintf(arq, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" />\n", getCirculoX(c) - getCirculoRaio(c), getCirculoY(c) - getCirculoRaio(c),getCirculoRaio(c)*2, getCirculoRaio(c)*2, cor, cor);
	}
	va_end(ap1);
	va_end(ap3);
}

void dqL1(Quadra q, ...){
	FILE *txt;
	va_list ap1, *ap2, ap3;
	double raio, x, y, dist;
	PosicTree p1;
	Cidade city;
	va_start(ap1, q);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	raio = va_arg(ap3, double);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	city = va_arg(ap3, Cidade);	
	txt = va_arg(ap3, FILE*);
	if (q == NULL){
		// printf("ja era\n");
	}
	dist = distPointsL1(x, y, getQuadraX(q), getQuadraY(q));
	if (dist <= raio){
		dist = distPointsL1(x, y, getQuadraX(q) + getQuadraWidth(q), getQuadraY(q));
		if (dist <=raio){
			dist = distPointsL1(x, y, getQuadraX(q) + getQuadraWidth(q), getQuadraY(q) + getQuadraHeight(q));
			if (dist <= raio){
				dist = distPointsL1(x, y, getQuadraX(q), getQuadraY(q) + getQuadraHeight(q));
				if (dist <= raio){
					fprintf(txt, "Equipamento Urbano %s\n", getQuadraCep(q));
					p1 = searchQuadra(city, getQuadraCep(q));
					removeQuadra(city, p1);
				}
			}
		}
	}
	va_end(ap1);
	va_end(ap3);
}

void dqL2(Quadra q, ...){
		FILE *txt;
	va_list ap1, *ap2, ap3;
	double raio, x, y, dist;
	PosicTree p1;
	Cidade city;
	va_start(ap1, q);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	raio = va_arg(ap3, double);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	city = va_arg(ap3, Cidade);	
	txt = va_arg(ap3, FILE*);
	if (q == NULL){
		// printf("ja era\n");
	}
	dist = distanciaEntrePontos(x, y, getQuadraX(q), getQuadraY(q));
	if (dist <= raio){
		dist = distanciaEntrePontos(x, y, getQuadraX(q) + getQuadraWidth(q), getQuadraY(q));
		if (dist <=raio){
			dist = distanciaEntrePontos(x, y, getQuadraX(q) + getQuadraWidth(q), getQuadraY(q) + getQuadraHeight(q));
			if (dist <= raio){
				dist = distanciaEntrePontos(x, y, getQuadraX(q), getQuadraY(q) + getQuadraHeight(q));
				if (dist <= raio){
					fprintf(txt, "Equipamento Urbano %s\n", getQuadraCep(q));
					p1 = searchQuadra(city, getQuadraCep(q));
					removeQuadra(city, p1);
				}
			}
		}
	}
	va_end(ap1);
	va_end(ap3);
}

void cbq(Quadra q, ...){
	double x, y, raio;
	FILE *txt;
	char *cor, *aux;
	va_list ap1, *ap2, ap3;
	va_start(ap1, q);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	raio = va_arg(ap3, double);
	cor = va_arg(ap3, char*);
	txt = va_arg(ap3, FILE*);
	if (retanguloInternoCirculo(getQuadraX(q), getQuadraY(q), getQuadraWidth(q), getQuadraHeight(q), x, y, raio)){
		fprintf(txt, "comando cbq\ncep: %s\n", getQuadraCep(q));
		aux = (char*)malloc(sizeof(char)*(strlen(cor) + 1));
		strcpy(aux, cor);
		setQuadraCorContorno(q, aux);
	}
	va_end(ap1);
	va_end(ap3);
}

void trnsQua(Quadra q, ...){
	double x, y, width, height, dx, dy;
	int i;
	FILE *txt;
	va_list ap1, *ap2, ap3;
	va_start(ap1, q);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	width = va_arg(ap3, double);
	height = va_arg(ap3, double);
	dx = va_arg(ap3, double);
	dy = va_arg(ap3, double);
	txt = va_arg(ap3, FILE*);
	i = retanguloInternoRetangulo(getQuadraX(q), getQuadraY(q), getQuadraWidth(q), getQuadraHeight(q), x, y, width, height);
	if (i){
		fprintf(txt, "Quadra cep: %s coordenadas antigas (%f, %f) coordenadas atualizadas (%f, %f)\n", getQuadraCep(q), getQuadraX(q), getQuadraY(q), getQuadraX(q) + dx, getQuadraY(q) + dy);
		setQuadraX(q, getQuadraX(q) + dx);
		setQuadraY(q, getQuadraY(q) + dy);
	}
}

void trnsSem(Semaforo s, ...){
	double x, y, width, height, dx, dy;
	int i;
	FILE *txt;
	va_list ap1, *ap2, ap3;
	va_start(ap1, s);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	width = va_arg(ap3, double);
	height = va_arg(ap3, double);
	dx = va_arg(ap3, double);
	dy = va_arg(ap3, double);
	txt = va_arg(ap3, FILE*);
	i = circuloInternoRetangulo(1.0, getSemaforoX(s), getSemaforoY(s), x, y, width, height);
	if (i){
		fprintf(txt, "Quadra cep: %s coordenadas antigas (%f, %f) coordenadas atualizadas (%f, %f)\n", getSemaforoId(s), getSemaforoX(s), getSemaforoY(s), getSemaforoX(s) + dx, getSemaforoY(s) + dy);
		setSemaforoX(s, getSemaforoX(s) + dx);
		setSemaforoY(s, getSemaforoY(s) + dy);
	}
}

void trnsHid(Hidrante h, ...){
	double x, y, width, height, dx, dy;
	int i;
	FILE *txt;
	va_list ap1, *ap2, ap3;
	va_start(ap1, h);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	width = va_arg(ap3, double);
	height = va_arg(ap3, double);
	dx = va_arg(ap3, double);
	dy = va_arg(ap3, double);
	txt = va_arg(ap3, FILE*);
	i = circuloInternoRetangulo(1.0, getHidranteX(h), getHidranteY(h), x, y, width, height);
	if (i){
		fprintf(txt, "Hidrante id: %s coordenadas antigas (%f, %f) coordenadas atualizadas (%f, %f)\n", getHidranteId(h), getHidranteX(h), getHidranteY(h), getHidranteX(h) + dx, getHidranteY(h) + dy);
		setHidranteX(h, getHidranteX(h) + dx);
		setHidranteY(h, getHidranteY(h) + dy);
	}
}

void trnsTor(Torre t, ...){
	double x, y, width, height, dx, dy;
	int i;
	FILE *txt;
	va_list ap1, *ap2, ap3;
	va_start(ap1, t);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	width = va_arg(ap3, double);
	height = va_arg(ap3, double);
	dx = va_arg(ap3, double);
	dy = va_arg(ap3, double);
	txt = va_arg(ap3, FILE*);
	i = circuloInternoRetangulo(1.0, getTorreX(t), getTorreY(t), x, y, width, height);
	if (i){
		fprintf(txt, "Hidrante id: %s coordenadas antigas (%f, %f) coordenadas atualizadas (%f, %f)\n", getTorreId(t), getTorreX(t), getTorreY(t), getTorreX(t) + dx, getTorreY(t) + dy);
		setTorreX(t, getTorreX(t) + dx);
		setTorreY(t, getTorreY(t) + dy);
	}
}

int cmpRaio(Vector vet, int indice, double raio){
	Distance d = getObjVector(vet, indice);
	return cmpDouble(raio, getDistanceDist(d));
}

void cmdFiSem(Semaforo s, ...){
	int *indice;
	Vector vet;
	double x, y, dist;
	va_list ap1, *ap2, ap3;
	va_start(ap1, s);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	vet = va_arg(ap3, Vector);
	indice = va_arg(ap3, int*);
	dist = distanciaEntrePontos(getSemaforoX(s), getSemaforoY(s), x, y);
	Distance distance = createDistance(dist, s);
	addVector(vet, distance, *indice, 0);
	(*indice)++;
	va_end(ap1);
}

void cmdFiHid(Hidrante h, ...){
	int k, *indice;
	Vector vet;
	double x, y, dist;
	va_list ap1, *ap2, ap3;
	va_start(ap1, h);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	x = va_arg(ap3, double);
	y = va_arg(ap3, double);
	vet = va_arg(ap3, Vector);
	indice = va_arg(ap3, int*);
	dist = distanciaEntrePontos(getHidranteX(h), getHidranteY(h), x, y);
	Distance distance = createDistance(dist, h);
	addVector(vet, distance, *indice, 0);
	(*indice)++;
	va_end(ap1);
}

Ponto endereco(Cidade city, char *cep, char face, int numero){
	PosicTree p1 = searchQuadra(city, cep);
	Quadra q1 = getObjQuadra(city, p1);
	double xq, yq, width, height, x, y;
	xq = getQuadraX(q1);
	yq = getQuadraY(q1);
	width = getQuadraWidth(q1);
	height = getQuadraHeight(q1);
	if (face == 'N')	{
		x = xq + numero;
		y = yq;
	} else if (face == 'S'){
		x = xq + numero;
		y = yq + height;
	} else if (face == 'O'){
		x = xq;
		y = yq + numero;
	} else if (face == 'L'){
		x = xq + width;
		y = yq + numero;
	}
	return createPonto(x, y);
}

void predioToVertice(Predio p, ...){
	int *count;
	Lista /*lVer,*/ lSeg;
	Cidade city;
	Vertice v1, v2, v3, v4;
	Segmento s1, s2, s3, s4;
	Ponto p1, p2, p3, p4, bomba; 
	Quadra q;
	va_list ap1, *ap2, ap3;
	va_start(ap1, p);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	// lVer = va_arg(ap3, Lista);
	lSeg = va_arg(ap3, Lista);
	bomba = va_arg(ap3, Ponto);
	count = va_arg(ap3, int*);
	(*count)++;
	//pegando os pontos do predio
	p1 = getPredioPoint(p, 1);
	p2 = getPredioPoint(p, 2);
	p3 = getPredioPoint(p, 3);
	p4 = getPredioPoint(p, 4);

	// printf("1 x %f y %f\n", getPontoX(p1), getPontoY(p1));
	// printf("2 x %f y %f\n", getPontoX(p2), getPontoY(p2));
	// printf("3 x %f y %f\n", getPontoX(p3), getPontoY(p3));
	// printf("4 x %f y %f\n", getPontoX(p4), getPontoY(p4));

	//criando segmentos a esquerda do ponto da bomba e vertices iniciais e finais
	s1 = criaSegmentoAEsquerda(p1, p2, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s1), 'o', 'i', s1);// pega-se o vertice do segmento mas como vimos na função criaSegmentoAEsquerda a verdade pega-se o ponto
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	// insertList(lVer, v1);
	v2 = createVertice(getSegmentoVerticeFinal(s1), 'o', 'f', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v2), bomba));
	// insertList(lVer, v2);
	setSegmentoVerticeInicial(s1, v1);
	setSegmentoVerticeFinal(s1, v2);

	s2 = criaSegmentoAEsquerda(p1, p3, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s2), 'o', 'i', s2);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	// insertList(lVer, v1);
	v2 = createVertice(getSegmentoVerticeFinal(s2), 'o', 'f', s2);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v2), bomba));
	// insertList(lVer, v2);
	setSegmentoVerticeInicial(s2, v1);
	setSegmentoVerticeFinal(s2, v2);

	s3 = criaSegmentoAEsquerda(p4, p2, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s3), 'o', 'i', s3);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	// insertList(lVer, v1);
	v2 = createVertice(getSegmentoVerticeFinal(s3), 'o', 'f', s3);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v2), bomba));
	// insertList(lVer, v2);
	setSegmentoVerticeInicial(s3, v1);
	setSegmentoVerticeFinal(s3, v2);	

	s4 = criaSegmentoAEsquerda(p4, p3, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s4), 'o', 'i', s4);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	// insertList(lVer, v1);
	v2 = createVertice(getSegmentoVerticeFinal(s4), 'o', 'f', s4);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v2), bomba));
	// insertList(lVer, v2);
	setSegmentoVerticeInicial(s4, v1);
	setSegmentoVerticeFinal(s4, v2);	

	// adiciona os 4 segmento na lista de segmentos lSeg

	insertList(lSeg, s1);
	insertList(lSeg, s2);
	insertList(lSeg, s3);
	insertList(lSeg, s4);
	va_end(ap1);
}

void muroToVertice(Muro m, ...){
	Lista /*lVer,*/ lSeg;
	Vertice v1, v2;
	Segmento s1, s2, s3, s4;
	Ponto p1, p2, p3, p4, bomba;
	va_list ap1, *ap2, ap3;
	va_start(ap1, m);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	// lVer = va_arg(ap3, Lista);
	lSeg = va_arg(ap3, Lista);
	bomba = va_arg(ap3, Ponto);

	s1 = criaSegmentoAEsquerda(getMuroPontoInicial(m), getMuroPontoFinal(m), bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s1), 'o', 'i', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	// insertList(lVer, v1);
	v2 = createVertice(getSegmentoVerticeFinal(s1), 'o', 'f', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v2), bomba));
	// insertList(lVer, v2);
	setSegmentoVerticeInicial(s1, v1);
	setSegmentoVerticeFinal(s1, v2);	

	insertList(lSeg, s1);
	va_end(ap1);
}

int verticeEncoberto(Segmento raio, Segmento *aSeg, int tamanho_aSeg, Ponto pI){
	int i;
	for (i = 0; i < tamanho_aSeg; i++){
		if (interseccaoSegmento(raio, aSeg[i], pI)){
			return 1;
		} else {
			setPontoX(pI, 0);
			setPontoY(pI, 0);			
			return 0;
		}
	}
}

void desativaSegmento(Lista lSegAtivo, Segmento s){ // aki
	Posic pos;
	int i;
	for (pos = getFirst(lSegAtivo); pos >=0; pos = getNext(lSegAtivo, pos)){
		if (getSegmentoId(s) == getSegmentoId(getObjList(lSegAtivo, pos))) {
			printf("acho\n");
			removeList(lSegAtivo, pos);
			break;
		}
	}
}

Segmento segmentoAtivoMaisProximo(Lista lSegAtivo){
	Posic pos1;
	pos1 = getLast(lSegAtivo);
	Segmento s = getObjList(lSegAtivo, pos1);
	removeList(lSegAtivo, pos1);
}

Ponto *detonaBomba(Cidade city, double x, double y, double *svgH, double *svgW){
	int count = 0, i;
	Segmento s1, R4i0, s2, s3;
	Vertice v1, vRi, vRf, bomba_ver;
	Ponto bomba = createPonto(x, y), p1, p2, p3, p4, pRi, pRf, pI;
	Lista lVer = createList(qtdList(getList(city, 'p'))*8 + qtdList(getList(city, 'm'))*2 + 8);
	Lista lSeg = createList(qtdList(getList(city, 'p'))*8 + qtdList(getList(city, 'm')) + 4);
	throughCity(city, &predioToVertice, 'p', /*lVer,*/ lSeg, bomba, &count);

	throughCity(city, &muroToVertice, 'm',/* lVer,*/ lSeg, bomba);

	// calculo do retangulo da borda
	svgCmpCirculo(svgH, svgW, x, y, 1.0);

	p1 = createPonto(1, 1);
	p2 = createPonto(*svgW - 1, 1);
	p3 = createPonto(1, *svgH - 1);
	p4 = createPonto(*svgW - 1, *svgH - 1);

	s1 = criaSegmentoAEsquerda(p1, p2, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s1), 'r', 'i', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeInicial(s1, v1);			
	// insertList(lVer, v1);
	v1 = createVertice(getSegmentoVerticeFinal(s1), 'r', 'f', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeFinal(s1, v1);			
	// insertList(lVer, v1);		
	insertList(lSeg, s1);

	s1 = criaSegmentoAEsquerda(p1, p3, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s1), 'r', 'i', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeInicial(s1, v1);			
	// insertList(lVer, v1);
	v1 = createVertice(getSegmentoVerticeFinal(s1), 'r', 'f', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeFinal(s1, v1);			
	// insertList(lVer, v1);
	insertList(lSeg, s1);

	s1 = criaSegmentoAEsquerda(p4, p2, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s1), 'r', 'i', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeInicial(s1, v1);			
	// insertList(lVer, v1);
	v1 = createVertice(getSegmentoVerticeFinal(s1), 'r', 'f', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeFinal(s1, v1);			
	// insertList(lVer, v1);			
	insertList(lSeg, s1);		

	s1 = criaSegmentoAEsquerda(p4, p3, bomba);
	v1 = createVertice(getSegmentoVerticeInicial(s1), 'r', 'i', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeInicial(s1, v1);			
	// insertList(lVer, v1);
	v1 = createVertice(getSegmentoVerticeFinal(s1), 'r', 'f', s1);
	setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
	setSegmentoVerticeFinal(s1, v1);
	// insertList(lVer, v1);			
	insertList(lSeg, s1);

	// vamos definir o raio R (Segmento raio) até a borda

	pRi = createPonto(x, y);
	pRf = createPonto(*svgW - 1, y);
	R4i0 = createSegmento(NULL, NULL);
	vRi = createVertice(pRi, 'a', 'i', R4i0);
	vRf = createVertice(pRf, 'a', 'f', R4i0);
	setSegmentoVerticeInicial(R4i0, vRi);
	setSegmentoVerticeFinal(R4i0, vRf);			
	Lista lSegInt = createList(qtdList(lSeg));
	Lista lVerNew = createList(qtdList(lSeg)*2);
	Posic pos1, pos2;
	for(pos1 = getFirst(lSeg); pos1 >= 0; pos1 = getNext(lSeg, pos1)){
		s1 = getObjList(lSeg, pos1);
		pI = createPonto(0, 0);
		i = interseccaoSegmento(R4i0, s1, pI);
		
		// fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1.1\" stroke=\"red\" />\n", getPontoX(getVerticePonto(getSegmentoVerticeInicial(R4i0))), getPontoY(getVerticePonto(getSegmentoVerticeInicial(R4i0))), getPontoX(getVerticePonto(getSegmentoVerticeFinal(R4i0))), getPontoY(getVerticePonto(getSegmentoVerticeFinal(R4i0))));
		if (i == 1){
			// fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1.1\" stroke=\"red\" />\n", getPontoX(getVerticePonto(getSegmentoVerticeInicial(s1))), getPontoY(getVerticePonto(getSegmentoVerticeInicial(s1))), getPontoX(getVerticePonto(getSegmentoVerticeFinal(s1))), getPontoY(getVerticePonto(getSegmentoVerticeFinal(s1))));
			// fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"3\" fill = \"blue\" stroke=\"blue\" stroke-width=\"1.1\" fill-opacity = \"1\"/>\n", getPontoX(pI), getPontoY(pI));
			// fprintf(svgQry, "</svg>");
			// vamos dividir o segmento s1 em dois segmento
			//esse segmento a ser feito será o segmento a esquerda do raio
			p1 = createPonto(getPontoX(pI), getPontoY(pI));
			v1 = createVertice(p1, 'a', 'f', NULL);
			setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
			s2 = createSegmento(getSegmentoVerticeInicial(s1), v1);
			setVerticeSegmento(v1, s2);
			setVerticeSegmento(getSegmentoVerticeInicial(s1), s2);
			insertList(lVer, getSegmentoVerticeInicial(s1));
			insertList(lVerNew, v1);
			insertList(lSegInt, s2);
			// segmento a direita do raio
			p1 = createPonto(getPontoX(pI), getPontoY(pI));
			v1 = createVertice(p1, 'a', 'f', NULL);
			setVerticeAngulo(v1, anguloPonto(getVerticePonto(v1), bomba));
			s2 = createSegmento(p1, getSegmentoVerticeFinal(s1));
			setVerticeSegmento(v1, s2);
			setVerticeSegmento(getSegmentoVerticeFinal(s1), s2);
			insertList(lVer, getSegmentoVerticeFinal(s1));
			insertList(lVerNew, v1);
			insertList(lSegInt, s2);
			//remover segmento s1 da lista lSeg
			pos2 = pos1;
			pos1 = getPrevious(lSeg, pos2);
			removeList(lSeg, pos2);
			freeSegmento(s1);
		} else {
			insertList(lVer, getSegmentoVerticeInicial(s1));
			insertList(lVer, getSegmentoVerticeFinal(s1));
		}
		freePonto(pI);
	}
	
	//juntar lista lVer com lVerNew, ou seja, os vertices novos com os vertice ja calculados
	int tamanho_aVer = qtdList(lVer) + qtdList(lVerNew);
	Vertice *aVer = (Vertice*)malloc(sizeof(Vertice)*tamanho_aVer);

	for (pos1 = getFirst(lVer), i = 0; pos1 >=0; pos1 = getNext(lVer, pos1), i++){
		aVer[i] = getObjList(lVer, pos1);
	}
	deleteList(lVer);

	for (pos1 = getFirst(lVerNew); pos1 >=0; pos1 = getNext(lVerNew, pos1), i++){
		aVer[i] = getObjList(lVerNew, pos1);
	}
	deleteList(lVerNew);
	//juntar lSeg com lSegInt
	int tamanho_aSeg = qtdList(lSeg) + qtdList(lSegInt);
	Segmento *aSeg = (Segmento*)malloc(sizeof(Segmento)*tamanho_aSeg);

	for (pos1 = getFirst(lSeg), i = 0; pos1 >= 0; pos1 = getNext(lSeg, pos1), i++){
		aSeg[i] = (Segmento)getObjList(lSeg, pos1);
	}
	deleteList(lSeg);

	for (pos1 = getFirst(lSegInt); pos1 >= 0; pos1 = getNext(lSegInt, pos1), i++){
		aSeg[i] = (Segmento)getObjList(lSegInt, pos1);
	}

	deleteList(lSegInt);

	//ordenação dos vetores

	qsort(aVer, tamanho_aVer, sizeof(Vertice), comparaVertice);

	// começa o processamento dos vertices
	Segmento Raio = createSegmento(NULL, NULL);
	Lista lSegAtv = createList(tamanho_aSeg);
	Lista lSegResposta = createList(7000);
	
	p1 = createPonto(getPontoX(aVer[0]), getPontoY(aVer[0]));
	// Vertice biombo = createVertice(p1, getVerticeCodigo(aVer[0]), getVerticeTipo(aVer[0]), getVerticeSegmento(aVer[0]));
	Vertice biombo = aVer[0];
	bomba_ver = createVertice(bomba, 'a', 'n', NULL);
	pI = createPonto(0, 0);
	int id_seg = 0, indice_lSegRes = 0;
	for (i = 0; i < tamanho_aVer; i++){
		// printf("%c\n", getVerticeTipo(aVer[i]));
		if (getVerticeTipo(aVer[i]) == 'i'){
			// printf("%c\n", getVerticeCodigo(aVer[i]));
			if (getVerticeCodigo(aVer[i]) != 'a'){
				setSegmentoId(getVerticeSegmento(aVer[i]), id_seg);
				id_seg++;
				insertList(lSegAtv, getVerticeSegmento(aVer[i]));
			}
			setSegmentoVerticeInicial(Raio, bomba_ver);
			setSegmentoVerticeFinal(Raio, aVer[i]);
			if(!verticeEncoberto(Raio, aSeg, tamanho_aSeg, pI)){
				s1 = segmentoAtivoMaisProximo(lSegAtv);
				//pI é definido na função verticeEncoberto
				p1 = createPonto(getPontoX(getVerticePonto(biombo)), getPontoY(getVerticePonto(biombo)));
				p2 = createPonto(getPontoX(pI), getPontoY(pI));
				s2 = createSegmento(p1, p2);
				p1 = createPonto(getPontoX(pI), getPontoY(pI));
				p2 = createPonto(getPontoX(getVerticePonto(aVer[i])), getPontoY(getVerticePonto(aVer[i])));
				s3 = createSegmento(p1, p2);
				biombo = aVer[i];
				insertList(lSegResposta, s2);
				insertList(lSegResposta, s3);
			}
		} else {
			setSegmentoVerticeInicial(Raio, bomba_ver);
			setSegmentoVerticeFinal(Raio, aVer[i]);					
			if (verticeEncoberto(Raio, aSeg, tamanho_aSeg, pI)){
				desativaSegmento(lSegAtv, getVerticeSegmento(aVer[i]));
			} else {
				desativaSegmento(lSegAtv, getVerticeSegmento(aVer[i]));
				p1 = createPonto(getPontoX(getVerticePonto(biombo)), getPontoY(getVerticePonto(biombo)));
				p2 = createPonto(getPontoX(getVerticePonto(aVer[i])), getPontoY(getVerticePonto(aVer[i])));
				s2 = createSegmento(p1, p2);
				p1 = createPonto(getPontoX(getVerticePonto(aVer[i])), getPontoY(getVerticePonto(aVer[i])));
				p2 = createPonto(getPontoX(pI), getPontoY(pI));
				createSegmento(p1, p2);
				biombo = createVertice(createPonto(getPontoX(pI), getPontoY(pI)), 'a', 'z', NULL);
				insertList(lSegResposta, s2);
				insertList(lSegResposta, s3);
			}
		}
	}
}

int cmd_M(Rbtree tree, PosicTree p1, FILE *txt){
	if (posicTreeVazio(tree, p1))
		return -1;
	cmd_M(tree, getRbtreeLeft(tree, p1), txt);
	cmd_M(tree, getRbtreeRight(tree, p1), txt);
	Morador m1 = getObjRbtree(tree, p1);
	fprintf(txt, "Comando m?\nNome %s cpf %s cep %s face %c numero %d complemento %s", getPessoaCpf(getMoradorPessoa(m1)), getMoradorCpf(m1), getMoradorCep(m1), getMoradorFace(m1), getMoradorNumero(m1), getMoradorCompl(m1));
	return 0;
}

void mmplg(Morador m, ...){
	int i;
	va_list ap1, *ap2, ap3;
	va_start(ap1, m);
	ap2 = va_arg(ap1, va_list*);
	va_copy(ap3, *ap2);
	Poligono pol = va_arg(ap3, Poligono);
	FILE svg = va_arg(ap3, FILE);
	Predio p = getMoradorPredio(m);
	if (p == NULL)
		return;
	Ponto p1 = getPredioPoint(p, 1);
	i = pontoInternoPoligono(pol, p1);
	if (i){
		freePonto(p1);
		Ponto p1 = getPredioPoint(p, 2);
		i = pontoInternoPoligono(pol, p1);
		if (i)		{
			freePonto(p1);
			Ponto p1 = getPredioPoint(p, 3);
			i = pontoInternoPoligono(pol, p1);			
			if (i){
				freePonto(p1);
				Ponto p1 = getPredioPoint(p, 4);
				i = pontoInternoPoligono(pol, p1);
				if (i){
					Quadra q1 = getPredioQuadra(p);
					setQuadraSW(q1, getQuadraSW(q1) + 2);
				}
			}
		}
	}
}

void leituraVia(int argc, char **argv, Cidade *city){
	FILE *arq_via;
	char id[20], id2[20], ldir[20], lesq[20], nome[20], line[100], word[20], *aux1, *aux2, *aux3, *aux4, *aux5;
	double x, y, comprimento, vel_med;
	aux1 = colocaBarra(pegaParametro(argc, argv, "-e"));
	aux2 = concatena(aux1, pegaParametro(argc, argv, "-v"));
	arq_via = fopen(aux2, "r");
	funcFree(&aux1);
	funcFree(&aux2);
	if (arq_via == NULL)
		return;
	while(!feof(arq_via)){
		fscanf(arq_via, "%[^\n]\n", line);
		sscanf(line, "%s", word);
		if (strcmp(word, "v") == 0){
			sscanf(line, "%s %s %lf %lf", word, id, &x, &y);
			aux1 = (char*)malloc(sizeof(char)*(strlen(id) + 1));
			strcpy(aux1, id);
			VerticeG v1 = createVerticeGrafo(aux1, x, y);
			insertVerticeDoGrafo(getGrafo(*city), v1);
		} else if (strcmp(word, "e") == 0){
			sscanf(line, "%s %s %s %s %s %lf %lf %s", word, id, id2, ldir, lesq, &comprimento, &vel_med, nome);
			// aux1 = (char*)malloc(sizeof(char)*(strlen(id) + 1));
			// strcpy(aux1, id);
			// aux2 = (char*)malloc(sizeof(char)*(strlen(id2) + 1));
			// strcpy(aux2, id2);
			aux3 = (char*)malloc(sizeof(char)*(strlen(ldir) + 1));
			strcpy(aux3, ldir);											
			aux4 = (char*)malloc(sizeof(char)*(strlen(lesq) + 1));
			strcpy(aux4, lesq);
			aux5 = (char*)malloc(sizeof(char)*(strlen(nome) + 1));
			strcpy(aux5, nome);			
			Aresta a = createAresta(id, id2, aux3, aux4, comprimento, vel_med, aux5, getGrafo(*city));
			// funcFree(&aux1);
			// funcFree(&aux2);
		}
	}
	fclose(arq_via);
}

int verificaRegistrador(char *str){
	if (strcmp(str, "R0") == 0)
		return 0;
	else if (strcmp(str, "R1") == 0)
		return 1;
	else if (strcmp(str, "R2") == 0)
		return 2;
	else if (strcmp(str, "R3") == 0)
		return 3;
	else if (strcmp(str, "R4") == 0)
		return 4;
	else if (strcmp(str, "R5") == 0)
		return 5;								
	else if (strcmp(str, "R7") == 0)
		return 7;
	else if (strcmp(str, "R8") == 0)
		return 8;
	else if (strcmp(str, "R9") == 0)
		return 9;
	else if (strcmp(str, "R10") == 0)
		return 10;
	return 0;												
}

void leituraQry(int argc, char **argv, double *svgH, double *svgW, FILE *svgQry, Cidade *city){
	FILE *entrada = NULL, *txt = NULL, *svgBb;
	Item it;
	int i, j, var, tipo1, tipo2;
	Circulo c1 = NULL, c2 = NULL;
	Retangulo r1 = NULL, r2 = NULL;
	Hidrante h1, h2;
	Quadra q1, q2;
	Semaforo s1, s2;
	Torre t1, t2;
	PosicTree p1, p2;
	PosicTree pa, pb;
	Ponto *registrador = (Ponto*)malloc(sizeof(Ponto)*11);
	for (i = 0; i < 11; i++){
		registrador[i] = createPonto(0.0, 0.0);
	}
	char *line = NULL, *word = NULL, *cor = NULL, *suf = NULL, 
	*aux = NULL, *aux2 = NULL, *aux3 = NULL, *text = NULL, *id = NULL, cpf[20], cnpj[20], compl[20], face, cep[20], regis[4];
	double raio, x, y, height, width, dx, dy;
	id = (char*)malloc(sizeof(char)*20);
	line = (char*)malloc(sizeof(char)*200);
	word =(char*)malloc(sizeof(char)*30);
	cor = (char*)malloc(sizeof(char)*20);
	suf = (char*)malloc(sizeof(char)*20);
	aux = colocaBarra(pegaParametro(argc, argv, "-e"));
	aux2 = concatena(aux, pegaParametro(argc, argv, "-q"));
	entrada = fopen(aux2, "r");
	if(entrada == NULL){
		printf("DIRETÓRIO OU ARQUIVO INVÁLIDOS\n");
		return;
	}
	funcFree(&aux);
	funcFree(&aux2);
	while(!feof(entrada)){
		fscanf(entrada, "%[^\n]\n", line);
		if (feof(entrada) && strlen(line) == 0)
			break;
		sscanf(line, "%s", word);
		if (strcmp(word, "i?") == 0){
			var = 0;
			sscanf(line, "%s %d %lf %lf", word, &j, &x, &y);
			pa = searchForma(*city, j, &i);
			if (i == 1){
				r1 = (Retangulo)getObjForma(*city, pa);
				if (r1 != NULL)
					var = pontoInternoRetangulo(r1, x, y);
				else
					var = -1;
			} else if(i == 0){
				c1 = (Circulo)getObjForma(*city, pa);
				if (c1 != NULL)
					var = pontoInternoCirculo(c1, x, y);
				else
					var = -1;
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			if(*svgW < x)
				*svgW = x;
			if (*svgH < y)
				*svgH = y;
			if (var == 0){
				fprintf(txt, "%s\nNÃO\n", line);
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"3\" fill = \"red\" stroke=\"red\" stroke-width=\"1\" />\n", x, y);
			} else{
				fprintf(txt, "%s\nSIM\n", line);
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"3\" fill = \"green\" stroke=\"green\" stroke-width=\"1\" />\n", x, y);
			}
		} else if (strcmp(word, "o?") == 0){
			double xma, yma, xme, yme;
			var = 0;
			xma = 0.0;
			yma = 0.0;
			xme = -1.0;
			yme = -1.0;
			sscanf(line, "%s %d %d", word, &i, &j);
			pa = searchForma(*city, i, &tipo1);
			if (posicTreeVazio(getTree(*city, 'f'), pa)){
				printf("Não achei %d", i);
				break;
			}
			pb = searchForma(*city, j, &tipo2);
			if (posicTreeVazio(getTree(*city, 'f'), pb)){
				printf("Não achei %d", j);
				break;
			}
			if (tipo1 == 1){
				if (tipo2 == 1){
					r1 = getObjForma(*city, pa);
					r2 = getObjForma(*city, pb);
					var = sobreposicaoRetanguloRetangulo(r1, r2);
					cmpRet(r1, &xma, &xme, &yma, &yme);
					cmpRet(r2, &xma, &xme, &yma, &yme);
				} else{
					r1 = getObjForma(*city, pa);
					c1 = getObjForma(*city, pb);
					var = sobreposicaoCirculoRetangulo(c1, r1);
					cmpRet(r1, &xma, &xme, &yma, &yme);
					cmpCir(c1, &xma, &xme, &yma, &yme);
				}
			} else{
				if (tipo2 == 1){
					c1 = getObjForma(*city, pa);
					r1 = getObjForma(*city, pb);
					var = sobreposicaoCirculoRetangulo(c1, r1);
					cmpRet(r1, &xma, &xme, &yma, &yme);
					cmpCir(c1, &xma, &xme, &yma, &yme);
					
				} else{
					c1 = getObjForma(*city, pa);
					c2 = getObjForma(*city, pb);
					var  = sobreposicaoCirculoCirculo(c1, c2);
					cmpCir(c1, &xma, &xme, &yma, &yme);
					cmpCir(c2, &xma, &xme, &yma, &yme);
				}
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			if (var == 0){
				fprintf(txt, "%s\nNÃO\n", line);
				fprintf(svgQry, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" stroke=\"black\" stroke-width=\"4\" fill-opacity = \"0.000\"/>\n", xme, yme, (xma - xme), (yma - yme));
			} else{
				fprintf(txt, "%s\nSIM\n", line);
				fprintf(svgQry, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" stroke=\"black\" stroke-width=\"4\" fill-opacity = \"0.000\" stroke-dasharray = \"5,5,5\"/>\n", xme, yme, (xma - xme), (yma - yme));
			}
			if ((xme + (xma -xme)) > *svgW)
				*svgH = xme + (xma -xme);
			if ((yme + (yma - yme)) > *svgH)
				*svgH = yme + (yma - yme);
		} else if (strcmp(word, "d?") == 0){
			sscanf(line, "%s %d %d", word, &i, &j);
			pa = searchForma(*city, i, &tipo1);
			pb = searchForma(*city, j, &tipo2);
			if (tipo1 == 0){
				if (tipo2 == 0){
					c1 = getObjForma(*city, pa);
					c2 = getObjForma(*city, pb);
					x = distanciaEntrePontos(getCirculoX(c1), getCirculoY(c1), getCirculoX(c2), getCirculoY(c2));
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getCirculoX(c1), getCirculoY(c1), getCirculoX(c2), getCirculoY(c2));
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n", (getCirculoX(c1) + getCirculoX(c2))/2, (getCirculoY(c1) + getCirculoY(c2))/2, x);
				}else{
					c1 = getObjForma(*city, pa);
					r1 = getObjForma(*city, pb);
					x = distanciaEntrePontos(getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n",(getCirculoX(c1) + (getRetanguloX(r1) + getRetanguloWidth(r1)/2))/2, (getCirculoY(c1) + (getRetanguloY(r1) + getRetanguloHeight(r1)/2))/2, x);

				}
			} else{
				if (tipo2==0){
					r1 = getObjForma(*city, pa);
					c1 = getObjForma(*city, pb);
					x = distanciaEntrePontos(getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) - getRetanguloWidth(r1)/2, getRetanguloY(r1) - getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getCirculoX(c1), getCirculoY(c1), getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n",(getCirculoX(c1) + (getRetanguloX(r1) + getRetanguloWidth(r1)/2))/2, (getCirculoY(c1) + (getRetanguloY(r1) + getRetanguloHeight(r1)/2))/2, x);
				}else{
					r1 = getObjForma(*city, pa);
					r2 = getObjForma(*city, pb);
					x = distanciaEntrePontos(getRetanguloX(r1) - getRetanguloWidth(r1)/2, getRetanguloY(r1) - getRetanguloHeight(r1)/2, getRetanguloX(r2) - getRetanguloWidth(r2)/2, getRetanguloY(r2) - getRetanguloHeight(r2)/2);
					fprintf(svgQry, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"2\" stroke=\"brown\" />", getRetanguloX(r2) + getRetanguloWidth(r2)/2, getRetanguloY(r2) + getRetanguloHeight(r2)/2, getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2);
					fprintf(svgQry, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%f</text>\n",((getRetanguloX(r2) + getRetanguloWidth(r2)/2) + (getRetanguloX(r1) + getRetanguloWidth(r1)/2))/2, ((getRetanguloY(r2) + getRetanguloHeight(r2)/2) + (getRetanguloY(r1) + getRetanguloHeight(r1)/2))/2, x);
				}
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			fprintf(txt, "%s\n%.10f\n", line, x);
		} else if (strcmp(word, "bb") == 0){
			sscanf(line, "%s %s %s", word, suf, cor);
			aux = funcSvgBb(argc, argv, cor);
			svgBb = fopen(aux, "w");
			funcFree(&aux);
			fprintf(svgBb, "<svg width = \"%f\" height = \"%f\">\n", *svgW, *svgH);
			throughCity(*city, &bb, 'f', svgBb, cor);

			// Lista list = getList(*city, 'f');
			// int position = 	getFirst(list);
			// for (; position < 0; position = getNext(list,position)){
			// 	j = getTypeObj(vetor, i);
			// 	if (j == 0){
			// 		c1 = getObjVector(vetor, i);
			// 		fprintf(svgBb, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" />\n", getCirculoX(c1) - getCirculoRaio(c1), getCirculoY(c1) - getCirculoRaio(c1),getCirculoRaio(c1)*2, getCirculoRaio(c1)*2, cor, cor);
			// 		printSvgCirculo(&svgBb, c1);
			// 	} else if (j == 1){
			// 		r1 = getObjVector(vetor, i);
			// 		fprintf(svgBb, "<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" style=\"fill:%s\" />", getRetanguloX(r1) + getRetanguloWidth(r1)/2, getRetanguloY(r1) + getRetanguloHeight(r1)/2, getRetanguloWidth(r1)/2, getRetanguloHeight(r1)/2, cor);
			// 		printSvgRetangulo(&svgBb, r1);
			// 	}
			// }
			fprintf(svgBb, "</svg>");
			fclose(svgBb);
		} else if (strcmp(word, "dq") == 0){
			sscanf(line, "%s %s %s %lf", word, suf, id, &raio);
			char type, *cepQ, *idE;
			double raioDeAlcance;
			p1 = searchEquipUrban(*city, id, &type);
			if (type == 'h'){
				h1 = getObjHidrante(*city, p1);
				x = getHidranteX(h1);
				y = getHidranteY(h1);
				idE = getHidranteId(h1);
			} else if (type == 's'){
				s1 = getObjSemaforo(*city, p1);
				x = getSemaforoX(s1);
				y = getSemaforoY(s1);
				idE = getSemaforoId(s1);
			} else if (type == 't'){
				t1 = getObjTorre(*city, p1);
				x = getTorreX(t1);
				y = getTorreY(t1);
				idE = getTorreId(t1);
			} else{
				// printf("não encontrado\n");
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			fprintf(txt, "Equipamento Urbano %s\n", idE);
			fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"10\" fill = \"white\" stroke=\"#ff8800\" stroke-width=\"2\" fill-opacity = \"0.1\"/>\n", x, y);
			fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"12\" fill = \"white\" stroke=\"black\" stroke-width=\"2\" fill-opacity = \"0.1\"/>\n", x, y);
			if (strcmp(suf, "L1") == 0){
				throughCity(*city, &dqL1, 'q', raio, x, y, *city, txt);
			} else{
				throughCity(*city, &dqL2, 'q', raio, x, y, *city, txt);
			}
		} else if (strcmp(word, "del") == 0){
			sscanf(line, "%s %s", word, id);
			char type;
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			p1 = searchEquipUrban(*city, id, &type);
			if (p1 < 0){
				p1 = searchQuadra(*city, id);
				if (p1 >=0)
					type = 'q';
			}
			if (type == 's'){
				removeSemaforo(*city, p1);
				fprintf(txt, "id: %s foi removido\n", id);
			} else if (type == 't'){
				removeTorre(*city, p1);
				fprintf(txt, "id: %s foi removido\n", id);
			} else if (type == 'h'){
				removeHidrante(*city, p1);
				fprintf(txt, "id: %s foi removido\n", id);
			} else if (type == 'q'){
				removeQuadra(*city, p1);
				fprintf(txt, "id: %s foi removido\n", id);
			}
		} else if (strcmp(word, "cbq") == 0){
			sscanf(line, "%s %lf %lf %lf %s", word, &x, &y, &raio, suf);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			throughCity(*city, &cbq, 'q', x, y, raio, suf, txt);
		} else if (strcmp(word, "crd?") == 0){
			sscanf(line, "%s %s", word, id);
			char type;
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			p1 = searchEquipUrban(*city, id, &type);
			if (p1 < 0){
				p1 = searchQuadra(*city, id);
				if (p1 >=0)
					type = 'q';
			}
			if (type == 's'){
				s1 = getObjSemaforo(*city, p1);
				fprintf(txt, "id: %s coordenadas (%f, %f)\n", id, getSemaforoX(s1), getSemaforoY(s1));
			} else if (type == 't'){
				t1 = getObjTorre(*city, p1);
				fprintf(txt, "id: %s coordenadas (%f, %f)\n", id, getTorreX(t1), getTorreY(t1));
			} else if (type == 'h'){
				h1 = getObjHidrante(*city, p1);
				fprintf(txt, "id: %s coordenadas (%f, %f)\n", id, getHidranteX(h1), getHidranteY(h1));
			} else if (type == 'q'){
				q1 = getObjQuadra(*city, p1);
				fprintf(txt, "id: %s coordenadas (%f, %f)\n", id, getQuadraX(q1), getQuadraY(q1));
			} else{
				fprintf(txt, "%s não existe\n", id);
			}
		} else if (strcmp(word, "trns") == 0){
			sscanf(line, "%s %lf %lf %lf %lf %lf %lf", word, &x, &y, &width, &height, &dx, &dy);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			throughCity(*city, &trnsQua, 'q', x, y, width, height, dx, dy, txt);
			throughCity(*city, &trnsSem, 's', x, y, width, height, dx, dy, txt);
			throughCity(*city, &trnsHid, 'h', x, y, width, height, dx, dy, txt);
			throughCity(*city, &trnsTor, 't', x, y, width, height, dx, dy, txt);
		} else if (strcmp(word, "fi") == 0){
			sscanf(line, "%s %lf %lf %d %lf", word, &x, &y, &var, &raio);
			int indice = 0, qtd = getQtdRbtree(getTree(*city, 's'));
			Vector vet1 = createVector(qtd), vet2;
			qtd = qtdList(getList(*city, 'h'));
			vet2 = createVector(qtd);
			Distance d1;
			throughCity(*city, &cmdFiSem, 's', x, y, vet1, &indice);
			knn(vet1, cmpDistance, var);
			// for (i = 0; i < getQuantidadeVector(vet1);i++){
			// 	d1 = getObjVector(vet1, i);
			// 	printf("dist: %f\n", getDistanceDist(d1));
			// }
			indice = 0;
			throughCity(*city, &cmdFiHid, 'h', x, y, vet2, &indice);
			indice = knnr(vet2, cmpDistance, raio);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			for (i = var, j = getQuantidadeVector(vet1) - 1; i > 0 && i <= j; i--, j--){
				d1 = getObjVector(vet1, j);
				s1 = getDistanceObj(d1);
				fprintf(txt, "O semaforo %s foi alterado\n", getSemaforoId(s1));
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"%f\" fill-opacity = \"0.0\"/>\n", getSemaforoX(s1), getSemaforoY(s1), 8.0, "white", "yellow", getSemaforoSW(s1));
				printSvgLine(&svgQry, x, y, getSemaforoX(s1), getSemaforoY(s1));
				freeDistance(d1);
			}
			freeVector(vet1);
			for (i = indice; i < getQuantidadeVector(vet2); i++){
				d1 = getObjVector(vet2, i);
				h1 = getDistanceObj(d1);
				fprintf(txt, "O hidrante %s foi ativado\n", getHidranteId(h1));
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"%f\" fill-opacity = \"0.0\"/>\n", getHidranteX(h1), getHidranteY(h1), 8.0, "white", "#ff0", getHidranteSW(h1));
				printSvgLine(&svgQry, x, y, getHidranteX(h1), getHidranteY(h1));
				freeDistance(d1);
			}
			freeVector(vet2);
		} else if (strcmp(word, "fh") == 0){
			char face;
			sscanf(line, "%s %d %s %c %d", word, &var, suf, &face, &i);
			int indice = 0, qtd = getQtdRbtree(getTree(*city, 'h'));
			Vector vet = createVector(qtd);
			Distance d1;
			Ponto point = endereco(*city, suf, face, i);
			throughCity(*city, &cmdFiHid, 'h', getPontoX(point), getPontoY(point), vet, &indice);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}			
			if (var >= 0)
				knf(vet, &cmpDistance, var);				
			else {
				var = funcAbs(var);
				knn(vet, &cmpDistance, var);
			}
			for (i = var, j = getQuantidadeVector(vet) - 1; i > 0 && i <= j; i--, j--){
				d1 = getObjVector(vet, j);
				h1 = getDistanceObj(d1);
				fprintf(txt, "comando fh: %s\n", getHidranteId(h1));
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"%f\" fill-opacity = \"0.0\"/>\n", getHidranteX(h1), getHidranteY(h1), 8.0, "white", "yellow", getHidranteSW(h1));
				printSvgLine(&svgQry, getPontoX(point), getPontoY(point), getHidranteX(h1), getHidranteY(h1));
				freeDistance(d1);
			}
			freeVector(vet);
			freePonto(point);
		} else if (strcmp(word, "fs") == 0){
			char face;
			sscanf(line, "%s %d %s %c %d", word, &var, suf, &face, &i);
			int indice = 0, qtd = getQtdRbtree(getTree(*city, 's'));			
			Vector vet = createVector(qtd);
			Distance d1;
			Ponto point = endereco(*city, suf, face, i);		
			throughCity(*city, &cmdFiSem, 's', getPontoX(point), getPontoY(point), vet, &indice);
			knn(vet, &cmpDistance, var);
			// for (i = 0; i < getQuantidadeVector(vet); i++){
			// 	printf("distance: %f\n", getDistanceDist(getObjVector(vet, i)));
			// }
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}			
			for (i = var, j = getQuantidadeVector(vet) - 1; i > 0 && i <= j; i--, j--){
				d1 = getObjVector(vet, j);
				s1 = getDistanceObj(d1);
				fprintf(txt, "comando fh: %s\n", getSemaforoId(s1));
				fprintf(svgQry, "<circle cx = \"%f\" cy = \"%f\" r = \"%f\" fill = \"%s\" stroke=\"%s\" stroke-width=\"%f\" fill-opacity = \"0.0\"/>\n", getSemaforoX(s1), getSemaforoY(s1), 8.0, "white", "yellow", getSemaforoSW(s1));
				printSvgLine(&svgQry, getPontoX(point), getPontoY(point), getSemaforoX(s1), getSemaforoY(s1));
				freeDistance(d1);
			}
			freeVector(vet);
			freePonto(point);
		} else if (strcmp(word, "brll") == 0){ // comando te alteração
			calcViewBoxSvg(*city, svgW, svgH);
			sscanf(line, "%s %lf %lf", word, &x, &y);

		} else if (strcmp(word, "dm?") == 0){
			sscanf(line, "%s %s", word, suf);
			Morador mr1 = searchMoradorCpf(*city, suf);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}	
			fprintf(txt, "Nome: %s | Cpf: %s | Sexo: %c | Data de Nascimento: %s\n", getPessoaNome(getMoradorPessoa(mr1)), getMoradorCpf(mr1), getPessoaSexo(getMoradorPessoa(mr1)), getPessoaNasc(getMoradorPessoa(mr1)));
		} else if (strcmp(word, "de?") == 0){
			sscanf(line, "%s %s", word, suf);
			Estab ec = searchEstabCom(*city, suf);
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			if (ec != NULL){
				fprintf(txt, "Nome: %s | Cnpj: %s | Tipo: %s | Cep: %s | Face: %c | Numero: %d",
				getEstabNome(ec), getEstabCNPJ(ec), getEstabTipo(ec), getEstabCep(ec), getEstabFace(ec), getEstabNum(ec));				
			}
		} else if (strcmp(word, "mud") == 0){
			sscanf(line, "%s %s %s %c %d %s", word, cpf, cep, &face, &i, compl);
			Pessoa ps1 = searchPessoaXCpf(*city, cpf);
			Morador mr1 = searchMoradorCpf(*city, cpf);
			PosicTree pos1 = searchPredio(*city, cep, face, i);
			Predio pr1 = NULL;
			if (posicTreeVazio(getCidadeRbtree(*city, 'p'), pos1) == 0){
				pr1 = getObjPredio(*city, pos1);
			}
			if (mr1 != NULL){
				if (pr1 == NULL){
					// printf("Endereço sem predio\n");
				} else {
					fprintf(txt, "Comando \"mud\"\nNome: %s Cpf: %s\nEndereço antigo\nCep: %s Face: %c numero: %d\n", getPessoaNome(ps1), getPessoaCpf(ps1), getMoradorCep(mr1), getMoradorFace(mr1), getMoradorNumero(mr1));
					setMoradorPredio(mr1, pr1, cep, compl, face, i);
				}
			} else {
				aux = (char*)malloc(sizeof(char)*(strlen(cpf) + 1));
				strcpy(aux, cpf);
				aux2 = (char*)malloc(sizeof(char)*(strlen(cep) + 1));
				strcpy(aux, cep);
				aux3 = (char*)malloc(sizeof(char)*(strlen(compl) + 1));
				strcpy(aux, compl);						
				mr1 = createMorador(ps1, pr1, aux, aux2, face, i, aux3);
			}
			if (txt == NULL){
				aux = funcTxt(argc, argv);
				txt = fopen(aux, "a");
				funcFree(&aux);
			}
			if (ps1 != NULL)
				fprintf(txt, "Comando \"mud\"\nNome: %s Cpf: %s\nEndereço novo\nCep: %s Face: %c numero: %d\n", getPessoaNome(ps1), getPessoaCpf(ps1), cep, face, i);
		} else if (strcmp(word, "mplg?") == 0){
			sscanf(line, "%s %s", word, suf);

			aux = colocaBarra(pegaParametro(argc, argv, "-e"));
			aux2 = concatena(aux, suf);
			funcFree(&aux);
			FILE *arq_pol = fopen(aux2, "r");
			Poligono pol1 = createPoligono(arq_pol);
			// throughCity(*city, mplg, 'p', pol1, arq_pol);
			fclose(arq_pol);
			// i = pontoInternoPoligono(pol1, p1);
			printf("i %d\n", i);
			getchar();
			printPoligono(svgQry, pol1);
		} else if (strcmp(word, "m?") == 0){
			sscanf(line, "%s %s", word, cep);
			p1 = searchQuadra(*city, cep);
			if (!posicTreeVazio(getTree(*city, 'q'), p1)){
				q1 = getObjQuadra(*city, p1);
				if (txt == NULL){
					aux = funcTxt(argc, argv);
					txt = fopen(aux, "a");
					funcFree(&aux);
				}			
				cmd_M(getQuadraArvoreMorador(q1), getRoot(getQuadraArvoreMorador(q1)), txt);
			}
		} else if (strcmp(word, "dmprbt") == 0){
			char tipo;
			sscanf(line, "%s %c %s", word, &tipo, suf);
			aux = colocaBarra(pegaParametro(argc, argv, "-o"));
			aux2 = concatena(aux, suf);
			FILE *svg = fopen(aux2, "w");
			fprintf(svg, "<svg>");
			funcFree(&aux);
			funcFree(&aux2);
			if (tipo == 'q')
				printTreeSvg(svg, getTree(*city, 'q'), getQuadraCep);
			else if (tipo == 'h')
				printTreeSvg(svg, getTree(*city, 'h'), getHidranteId);
			else if (tipo == 't')
				printTreeSvg(svg, getTree(*city, 't'), getTorreId);
			else if (tipo == 's')
				printTreeSvg(svg, getTree(*city, 's'), getSemaforoId);
			else if (tipo == 'm')
				printTreeSvg(svg, getTree(*city, 'm'), NULL);
			else if (tipo == 'p')
				printTreeSvg(svg, getTree(*city, 'p'), getPredioCep);
			fprintf(svg, "</svg>");
			fclose(svg);
		} else if (strcmp(word, "@m?") == 0){
			sscanf (line, "%s %s %s", word, regis, cpf);
			i = verificaRegistrador(regis);
			Morador mor = searchMoradorCpf(*city, cpf);
			if (mor != NULL){
					Ponto pt = endereco(*city, getMoradorCep(mor), getMoradorFace(mor), getMoradorNumero(mor));
					setPontoX(registrador[i], getPontoX(pt));
					setPontoY(registrador[i], getPontoY(pt));
					freePonto(pt);
			} else
				printf("sem morador\n");
		} else if (strcmp(word, "@e?") == 0){
			sscanf(line, "%s %s %s %c %d", word, regis, cep, &face, &j);
			i = verificaRegistrador(regis);
			Ponto pt = endereco(*city, cep, face, j);
			if (pt != NULL){
				setPontoX(registrador[i], getPontoX(pt));
				setPontoY(registrador[i], getPontoY(pt));
				freePonto(pt);				
			} else 
				printf("sem ponto\n");
		} else if (strcmp(word, "@g?") == 0){
			sscanf(line, "%s %s %s", word, regis, cep);
			i = verificaRegistrador(regis);
			face = 'b';
			pa = searchEquipUrban(*city, cep, &face);
			if (face == 't' && !posicTreeVazio(getTree(*city, 't'), pa)){
				t1 = getObjTorre(*city, pa);
				setPontoX(registrador[i], getTorreX(t1));
				setPontoY(registrador[i], getTorreY(t1));
			} else if (face == 'h' && !posicTreeVazio(getTree(*city, 't'), pa)){
				h1 = getObjHidrante(*city, pa);
				setPontoX(registrador[i], getHidranteX(h1));
				setPontoY(registrador[i], getHidranteY(h1));
			} else if (face == 's' && !posicTreeVazio(getTree(*city, 't'), pa)){
				s1 = getObjSemaforo(*city, pa);
				setPontoX(registrador[i], getSemaforoX(s1));
				setPontoY(registrador[i], getSemaforoY(s1));
			} else
				printf("não acho\n");
		} else if (strcmp(word, "@xy?") == 0){
			sscanf(line, "%s %s %lf %lf", word, regis, &x, &y);
			i = verificaRegistrador(regis);
			setPontoX(registrador[i], x);
			setPontoY(registrador[i], y);			
		} else if (strcmp(word, "p?") == 0){
			sscanf(line, "%s %s %d %d %s %s", word, suf, &i, &j, cor, compl);
			PosicLD p1, p2;
			VerticeG v_origem, v_destino, v1, v2;
			GrafoD graph = getGrafo(*city);
			v_origem = findNearestVertice(graph, registrador[i]);
			v_destino = findNearestVertice(graph, registrador[j]);
			ListaDinamica mais_curto = dijkstra(getGrafo(*city), v_origem, v_destino, 'c');
			ListaDinamica mais_rapido = dijkstra(getGrafo(*city), v_origem, v_destino, 'v');
			aux = colocaBarra(pegaParametro(argc, argv, "-o"));
			aux2 = concatena(aux, "cmd_p.svg");
			printf("%s\n", aux2);
			getchar();
			FILE *svg_p = fopen(aux2, "w");
			fprintf(svg_p, "<svg>\n");
			printSvgCidade(*city, svg_p);
			printf("%d\n", DinamicListlength(mais_curto));
			for (p1 = getFirstDinamicList(mais_curto); p1 != NULL; p1 = getNextDinamicList(p1)){
				p2 = getPreviousDinamicList(p1);
				v1 = getObjtDinamicList(p1);
				if (p2 != NULL){
					v2 = getObjtDinamicList(p2);
					fprintf(svg_p, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"5\"  />\n", getVerticePosicX(v1)-2, getVerticePosicY(v1)-2, getVerticePosicX(v2)-2, getVerticePosicY(v2)-2, cor);
				}
			}
			printf("%d\n", DinamicListlength(mais_rapido));
			for (p1 = getFirstDinamicList(mais_rapido); p1 != NULL; p1 = getNextDinamicList(p1)){
				p2 = getPreviousDinamicList(p1);
				v1 = getObjtDinamicList(p1);
				if (p2 != NULL){
					v2 = getObjtDinamicList(p2);
					fprintf(svg_p, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"5\"  />\n", getVerticePosicX(v1)+2, getVerticePosicY(v1)+2, getVerticePosicX(v2)+2, getVerticePosicY(v2)+2, compl);
				}
			}			
			fprintf(svg_p, "</svg>\n");
			printf("calmae");
			getchar();
		}
	}
	calcViewBoxSvg(*city, svgW, svgH);
	if (txt!= NULL)
		fclose(txt);
	funcFree(&id);
	funcFree(&line);
	funcFree(&word);
	funcFree(&cor);
	funcFree(&suf);
	fclose(entrada);
}

void leituraInterativa(int argc, char **argv, double *svgH, double *svgW, FILE *svgQry, Cidade *city){
	// char *line = NULL,*word = NULL,*arq=NULL;
	// char tipo;
	// Rbtree tree;
	// PosicTree root;
	// FILE *svg = NULL;
	// line = (char*)malloc(sizeof(char)*200);
	// word =(char*)malloc(sizeof(char)*30);
	// arq =(char*)malloc(sizeof(char)*30);

	// while(strcmp(line,"sai") != 0){
	// 	printf("Entre com um comando: ");
	// 	scanf("%[^\n]",line);
	// 	getchar();
	// 	if(strcmp(line,"sai") == 0 ){ // sai da execução 
	// 		return;
	// 	}
	// 	sscanf(line, "%s", word);
	// 	if(strcmp(word, "nav") == 0){ // nav t (navega pela arvore t (t indica qual arvore vai ser navegada))
	// 		sscanf(line, "%s", word);
    //         if(strcmp(word, "t") == 0){
	// 			printf("entrou no t");
    //             tree = getTree(city,'t');
    //         }
    //         else if(strcmp(word, "q") == 0){
    //             tree = getTree(city,'q');
    //         }
    //         else if(strcmp(word, "s") == 0){
    //             tree = getTree(city,'s');
    //         }
    //         else if(strcmp(word, "h") == 0){
    //             tree = getTree(city,'h');
    //         }
    //         else if(strcmp(word, "f") == 0){
    //             tree = getTree(city,'f');
    //         }
    //         else if(strcmp(word, "p") == 0){
    //             tree = getTree(city,'p');
    //         }
    //         else if(strcmp(word, "m") == 0){
    //             tree = getTree(city,'m');
    //         }
    //         root = getRoot(tree);
	// 		while(strcmp(line,"x") != 0){
	// 			printf("Entre com um comando de navegação: ");
	// 			scanf("%s",line);
	// 			getchar();
	// 			sscanf(line, "%s", word);

	// 			if(strcmp(word,"e") != 0){  // Desce para sub-árvore esquerda. Imprime dados do nó.
	// 				root = getRbtreeLeft(tree,root);
	// 			}
	// 			else if(strcmp(word,"d") != 0){ // Desce para sub-árvore direita.
	// 				root = getRbtreeRight(tree,root);
	// 			}
	// 			else if(strcmp(word,"p") != 0){ // Volta para o pai.
    //                 root = getRbtreeParent(tree,root);
	// 			}
	// 			else if(strcmp(word,"x") != 0){ // Sai da navegação
	// 				break;
	// 			}
    //             if(root != NULL){
    //                 printf("Valores da arvore\n");
	// 					// printf("X: %lf\n",root->x);
	// 					// printf("Y: %lf\n",root->y);
	// 					// printf("Cor: %c\n\n",root->color);
    //             }
    //             else{
    //                 printf("Valor nulo\n\n");
    //             }
	// 		}
	// 	}
	// 	else if(strcmp(word, "d") == 0){ // dmprbt t arq: imprime o estado atual da arvore t no arq.svg
	// 		sscanf(line, "%s", word);
	// 		if(strcmp(word, "t") == 0){
	// 			root = getCidadeRbtree(city,'t');
    //         }
    //         else if(strcmp(word, "q") == 0){
	// 			root = getCidadeRbtree(city,'q');
    //         }
    //         else if(strcmp(word, "s") == 0){
	// 			root = getCidadeRbtree(city,'s');

    //         }
    //         else if(strcmp(word, "h") == 0){
	// 			root = getCidadeRbtree(city,'h');

    //         }
    //         else if(strcmp(word, "f") == 0){
	// 			root = getCidadeRbtree(city,'f');

    //         }
    //         else if(strcmp(word, "p") == 0){
	// 			root = getCidadeRbtree(city,'p');

    //         }
    //         else if(strcmp(word, "m") == 0){
	// 			root = getCidadeRbtree(city,'m');

    //         }
	// 		sscanf(line, "%s", word);
	// 		arq = word;
	// 		svg = fopen(arq,"w");
	// 		// printTreeSvg(svg, )
	// 		fclose(svg);
	// 	}
	// 	else if(strcmp(word, "q") == 0){ // q arq.qry: lê e executa o arquivo de consultas arq.qry 
	// 		sscanf(line, "%s", word);
    //         // leituraQry(argc, argv, &svgH, &svgW, svgQry, &city); tem que arrumar
	// 	}
	// }
}