#ifndef CATPROD_H
#define CATPROD_H

#include <gmodule.h>

typedef struct catProd* CatProd;

CatProd newCatProd();
void catProdInsert(CatProd, void*, void*);
void* catProdLookup(CatProd, char*);
int catProdNodos(CatProd);
void catProdToFile(CatProd, char*);
void freeProdTree(CatProd);
void setListaLetra(CatProd, char*);

#endif
