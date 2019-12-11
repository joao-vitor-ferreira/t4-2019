#ifndef Vector_H
#define Vector_H

	typedef void *Vector;
	typedef void *Item;

Vector createVector(int n);
int getSizeVector(Vector vet);
int getQntd(Vector vet);
void setSizeVector(Vector vet, int size);
Item getObjVector(Vector vet, int n);
void addVector(Vector vet,	Item obj, int n, int i);
int getTypeObj(Vector vet, int posic);
int getQuantidadeVector(Vector vet);
void swap(Vector vet, int i, int j);
void freeVector(Vector vet);

#endif