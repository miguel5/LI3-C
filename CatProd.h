#ifndef CATPROD_H
#define CATPROD_H

typedef struct catProd* CatProd;

CatProd newCatProd();
void catProdInsert(CatProd, void*, void*);
void* catProdLookup(CatProd, char*);
int catProdNodos(CatProd);
void catProdToFile(CatProd, char*);
void freeProd(CatProd);

#endif
