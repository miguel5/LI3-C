#include <string.h>
#include <stdlib.h>
#include "cliente.h"

/*
* Struct de um cliente
*/
struct cliente
{
	char* cli_ref;
};

char* getCliRef(Cliente p)
{
	return p->cli_ref;
}

Cliente criaCliente(char* cli_ref)
{
	Cliente c = (Cliente) malloc(sizeof(struct cliente));
	c->cli_ref = strdup(cli_ref);

	return c;
}