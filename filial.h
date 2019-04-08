#ifndef FILIAL_H
#define FILIAL_H

typedef struct filial* Filial;

Filial newFilial();
void filialInsert(Filial, void*, void*);
int filialLookup(Filial, Venda);
void freeFilial(Filial f);
//void forEach1(Filial);

#endif
