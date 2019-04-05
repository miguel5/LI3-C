#include <gmodule.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

// Cria uma estrutura CatProd vazia
CatProd newCatProd(){
	CatProd cp = (CatProd) malloc(sizeof(struct catProd));
	cp->t = g_tree_new((GCompareFunc) compFunc_catProd);

	return cp;
}

// Insere uma um valor(void*) com uma chave(char*) numa filal
void catProdInsert(CatProd cp, void* key, void* value){
	g_tree_insert(cp->t, key, value);

	return;
}

// Devolve o valor guardado no nodo com a chave dada
void* catProdLookup(CatProd cp, char* key){
	return g_tree_lookup(cp->t, key);
}

// Devolve o numero de produtos do catalogo
int catProdNodos(CatProd cp){
	return g_tree_nnodes(cp->t);
}

gboolean writeProd(gpointer key, gpointer value, gpointer data){
	fprintf(data, "%s\n", (char*) key);
	return FALSE;
}

// Escreve os produtos contidos num catalogo para um ficheiro
void catProdToFile(CatProd cp, char* nome){

	FILE *fp;
    if ((fp = fopen(nome, "w")) == NULL)
    {
        fprintf(stderr, "Erro ao escrever %s!\n", nome);
        return;
    } 
    
    g_tree_foreach(cp->t, (GTraverseFunc)writeProd, fp);
    
    fclose(fp);
}

void freeProd(CatProd prod_list)
{
    g_tree_destroy(prod_list -> t);
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
