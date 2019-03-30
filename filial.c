#include <gmodule.h>
#include <stdlib.h>
#include <string.h>
#include "filial.h"

/*
 * Struct de uma filial
*/
struct filial
{
	GTree* t;
};

// Funçao de criterio de insereçao na arvore
int compFunc_strcmp(char* a, char* b)
{
	return strcmp(a,b);
}

// Cria uma estrutura Filial vazia
Filial newFilial(){
	Filial f = (Filial) malloc(sizeof(struct filial));
	f->t = g_tree_new((GCompareFunc) compFunc_strcmp);

	return f;
}

// Insere uma um valor(void*) com uma chave(char*) numa filal
void filialInsert(Filial f, char* key, void* value){
	g_tree_insert(f->t, key, value);

	return;
}

// Devolve o valor guardado no nodo com a chave dada
void* filialLookup(Filial f, char* key){
	return g_tree_lookup(f->t, key);
}