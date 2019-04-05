#include <gmodule.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

// Escreve a key(char*) de um CatCli num ficheiro (data = FILE*) 
gboolean writeCli(gpointer key, gpointer value, gpointer data){
	fprintf(data, "%s\n", (char*) key);
	return FALSE;
}

// Escreve os produtos contidos num catalogo para um ficheiro
void catCliToFile(CatCli cc, char* nome){

	FILE *fp;
    if ((fp = fopen(nome, "w")) == NULL)
    {
        fprintf(stderr, "Erro ao escrever %s!\n", nome);
        return;
    } 
    
    g_tree_foreach(cc->t, (GTraverseFunc)writeCli, fp);
    
    fclose(fp);
}

void freeCli(CatCli cli_list)
{
    g_tree_destroy(cli_list -> t);
}
