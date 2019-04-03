#include <gmodule.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "venda.h"
#include "filial.h"


/*
 * Struct de uma filial
*/
struct filial
{
	GTree* t;
};

// Cria uma estrutura Filial vazia
Filial newFilial(){
	Filial f = (Filial) malloc(sizeof(struct filial));
	f->t = g_tree_new((GCompareFunc) vendaCmp);

	return f;
}

// Insere uma um valor(void*) com uma chave(void*) numa filal
void filialInsert(Filial f, void* key, void* value){
	g_tree_insert(f->t, key, value);

	return;
}

// Devolve o valor guardado no nodo com a chave dada
int filialLookup(Filial f, Venda key){
	
	void* res = g_tree_lookup(f->t, key);

	if(res != NULL)
		return atoi(res);
	else
		return 0;
}

/*
gboolean iter_all(gpointer key, gpointer value, gpointer data) {
 printf("%s, %s\n", vendaToString(key), value);
 return FALSE;
}*/

// Teste
/*
void forEach1(Filial f){
	g_tree_foreach(f->t, (GTraverseFunc)iter_all, NULL);
	return;
}
*/