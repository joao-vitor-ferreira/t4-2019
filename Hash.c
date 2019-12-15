#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Hash.h"
#include "ListaDinamica.h"

typedef struct {
    int size;
    ListaDinamica *vet;
}hash;

typedef struct{
    void *key; //elemento correspondente à id dada
    char *id; //identificacao
}hashElement;

Hash createHash(int TABLE_SIZE){
    hash *newHash;
    newHash = (hash*)malloc(sizeof(hash));
    newHash->vet = (ListaDinamica*)malloc(TABLE_SIZE * sizeof(ListaDinamica));
    newHash->size = TABLE_SIZE;
    ListaDinamica list;
    for(int i = 0; i<TABLE_SIZE; i++){
        list = createDinamicList();
        newHash->vet[i] = list;
    }
    return newHash; 
}

int functionHash(char *str, int table_size){
    int i, x;
    int a = 11;
    unsigned int h = 0;
    for(i = 0; str[i] != '\0'; i++){
        h = (a*h + str[i])/2;
    }
    return h%table_size;
}

void addHash(Hash ha, void *hashElement, char *id){
    hash *newHash = (hash*)ha;
    int key;
    key = functionHash(id, newHash->size);
    insertDinamicList(newHash->vet[key], hashElement);
}

void deleteHashElement(Hash ha, char *id, ID func){
    hash *newHash = (hash*)ha;
    PosicLD p;
    int key = functionHash(id, newHash->size);
    if (DinamicListlength(newHash->vet[key]) == 0){
        return;
    } else {
        for(p = getFirstDinamicList(newHash->vet[key]); p!=NULL; p = getNextDinamicList(p)){
            if (strcmp(id, func(getObjtDinamicList(p))) == 0)
                removeDinamicList(newHash->vet[key], p);
        }
    }
}

void *searchHash(Hash ha, char *id, ID func){
    hash *newHash = (hash*)ha;
        PosicLD p;
        int key = functionHash(id, newHash->size), i;
        if (DinamicListlength(newHash->vet[key]) == 0){
            return NULL;
        } 
        else {
            for(p = getFirstDinamicList(newHash->vet[key]), i = 0; p!=NULL && i < DinamicListlength(newHash->vet[key]); p = getNextDinamicList(p)){
                if (func(getObjtDinamicList(p)) == NULL)
                    printf("fffffff\n");
                if (strcmp(id, func(getObjtDinamicList(p))) == 0)
                    return getObjtDinamicList(p);
            }  
        }
        return NULL;
}

HashElement createHashElement (char *id, void *key) {
    hashElement *newHashElement;
    newHashElement = (hashElement*)malloc(sizeof(hashElement));
    newHashElement->id = id;
    newHashElement->key = key;
    return (HashElement) newHashElement;
}

char *getHashElementId (HashElement h){
    hashElement *newHashElement = (hashElement*) h;
    return newHashElement->id;
}

void *getHashElementKey (HashElement h){
    hashElement *newHashElement = (hashElement*) h;
    return newHashElement->key;
}

void freeHashAll(Hash ha){
    hash *newHash = (hash*)ha;
    int size = newHash->size;
    for (int i = 0; i<size; i++){
        deleteDinamicListComplete(newHash->vet[i], NULL);
    }
    if (newHash->vet != NULL)
        free(newHash->vet);
    if (newHash != NULL)
        free(newHash);
}