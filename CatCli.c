#include <gmodule.h>
#include <string.h>
#include <stdlib.h>
#include "cliente.h"

/*
* Struct de um cliente
*/
struct cliente
{
    GTree* t;
};

// Funçao de criterio de inserçao na arvore
int compFunc_strcmp(char* a, char* b)
{
    return strcmp(a,b);
}

// Cria uma estrutura Filial vazia
Cliente newCliente(){
    Cliente c = (Cliente) malloc(sizeof(struct cliente));
    c -> t = g_tree_new((GCompareFunc) compFunc_strcmp);

    return c;
}

// Insere uma um valor(void*) com uma chave(char*) numa filal
void clienteInsert(Cliente c, char* key, void* value){
    g_tree_insert(c->t, key, value);
}

// Devolve o valor guardado no nodo com a chave dada
void* clienteLookup(Cliente c, char* key){
    return g_tree_lookup(c->t, key);
}