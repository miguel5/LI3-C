#include <gmodule.h>
#include <string.h>
#include <stdlib.h>
#include "CatCli.h"

//Struct de um cliente
struct catCli
{
    GTree* t;
};

// Funçao de criterio de inserçao na arvore
int compFunc_catCli(char* a, char* b)
{
    return strcmp(a,b);
}

// Cria uma estrutura CatCli vazia
CatCli newCatCli(){
    CatCli cc = (CatCli) malloc(sizeof(struct catCli));
    cc->t = g_tree_new((GCompareFunc) compFunc_catCli);

    return cc;
}

// Insere uma um valor(void*) com uma chave(char*) num Catálogo de Clientes
void catCliInsert(CatCli cc, void* key, void* value){
    g_tree_insert(cc->t, key, value);

    return;
}

// Devolve o valor guardado no nodo com a chave dada
void* catCliLookup(CatCli cc, char* key){
    return g_tree_lookup(cc->t, key);
}

int catCliNodos(CatCli cc){
	return g_tree_nnodes(cc->t);
}