#include <gmodule.h>
#include <stdlib.h>
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

Filial newFilial(){
	Filial f = (Filial) malloc(sizeof(struct filial));
	f->t = g_tree_new((GCompareFunc) compFunc_strcmp);

	return f;
}