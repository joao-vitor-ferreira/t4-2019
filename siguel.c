#include <stdio.h>
#include <stdlib.h>
#include "Retangulo.h"
#include "Cidade.h"
#include "Circulo.h"
#include "Comandos.h"
#include "Calculos.h"
#include "Svg.h"
#include "Vector.h"
#include "Vertice.h"

int main (int argc, char **argv){
	FILE *svgMain, *svgQry;
	Cidade city;
	Item obj;
	Circulo c;
	Lista lseg;
	Retangulo r;
	Vector *vetVert;
	int a, b;
	double  svgW, svgH;
	char *str = NULL, *str2 = NULL;	
	svgMain = NULL; 
	svgW = 0.0;
	svgH = 0.0;
	str = pegaParametro(argc, argv, "-o");
	if (str == NULL){
		printf("Diretório de saída não informado\n");
		return 0;
	}
	str = pegaParametro(argc, argv, "-f");
	if (str == NULL){
		printf("Arquivo de entrada não informado\n");
		return 0;
	}
	str = funcSvgMain(argc, argv, "-f");
	svgMain = fopen(str, "w");
	funcFree(&str);
	fprintf(svgMain, "                                                                  ");
	leituraGeo(argc, argv, &svgH, &svgW, svgMain, &city, lseg, vetVert);
	printSvgCidade(city, svgMain);
	funcFree(&str);
	fprintf(svgMain, "</svg>");
	rewind(svgMain);
	svgH += 10.0;
	svgW += 100.0;
	fprintf(svgMain, "<svg width=\"%f\" height=\"%f\">\n", svgW, svgH);
	fclose(svgMain);
	str = pegaParametro(argc, argv, "-q");
	if (str != NULL){
		str = funcSvg(argc, argv);
		svgQry = fopen(str, "w");
		funcFree(&str);
		fprintf(svgQry, "                                                                  ");
		leituraQry(argc, argv, &svgH, &svgW, svgQry, &city, lseg, vetVert);
		printSvgCidade(city, svgQry);
		fprintf(svgQry, "</svg>");
		rewind(svgQry);
		svgH += 10.0;
		svgW += 100.0;
		fprintf(svgQry, "<svg width=\"%f\" height=\"%f\">\n", svgW, svgH);
		fclose(svgQry);
	}
	freeCidade(city);
}