#ifndef HASH_H
#define HASH_H
    typedef void *Hash;
    typedef void *HashString;
    typedef void *HashElement;
    typedef char *((*ID)(void*));
Hash createHash(int TABLE_HASH);
/*Cria uma tabela de espalhamento de tamanho TABLE_HASh*/
int functionHash(char *str, int table_size);
/*define o indice do vetor na hash aonde vai determinado dado*/
void addHash(Hash ha, void *thing, char *id);
/*função que define aonde vai determinado dado*/
void *searchHash(Hash ha, char *id, ID func);
/*função de busca da Hash por id*/
void deleteHashElement(Hash ha, char *id, ID func);
//deleta um elemento da hash ha
void freeHashAll(Hash ha);
//dá free na hash ha
HashElement createHashElement (char *id, void *key);
//cria um elemento para a hash
char *getHashElementId (HashElement h);
//retorna id do elemento
void *getHashElementKey (HashElement h);
//retorna (void pointer)key do elemento
#endif