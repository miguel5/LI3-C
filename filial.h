#ifndef FILIAL_H
#define FILIAL_H

typedef struct filial* Filial;

Filial newFilial();
void filialInsert(Filial, char*, void*);
void* filialLookup(Filial, char*);

#endif