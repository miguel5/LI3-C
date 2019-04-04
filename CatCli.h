#ifndef CATCLI_H
#define CATCLI_H

typedef struct catCli* CatCli;

CatCli newCatCli();
void catCliInsert(CatCli, void*, void*);
void* catCliLookup(CatCli, char*);
int catCliNodos(CatCli);
void catCliToFile(CatCli, char*);

#endif