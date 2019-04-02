#ifndef CATPROD_H
#define CATPROD_H

typedef struct catProd* CatProd;

CatProd newCatProd();
void catProdInsert(CatProd, char*, void*);
void* catProdLookup(CatProd, char*);

#endif