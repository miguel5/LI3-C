#include <gmodule.h>
#include <string.h>
#include <stdlib.h>
#include "CatProd.h"

// Struct de um catalogo de produtos
struct catProd
{
	GTree* t;
};

// Funçao de criterio de insereçao na arvore
int compFunc_catProd(char* a, char* b)
{
	return strcmp(a,b);
}

// Cria uma estrutura Filial vazia
CatProd newCatProd(){
	CatProd cp = (CatProd) malloc(sizeof(struct catProd));
	cp->t = g_tree_new((GCompareFunc) compFunc_catProd);

	return cp;
}

// Insere uma um valor(void*) com uma chave(char*) numa filal
void catProdInsert(CatProd cp, char* key, void* value){
	g_tree_insert(cp->t, key, value);

	return;
}

// Devolve o valor guardado no nodo com a chave dada
void* catProdLookup(CatProd cp, char* key){
	return g_tree_lookup(cp->t, key);
}