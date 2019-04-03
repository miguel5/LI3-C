#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

// Funções de validação
int isUpperN2(char letters[], int n)
{
    int i = 0;

    while (i < n)
    {
        if (!isupper(letters[i]))
        	return 0;
        i++;
    } 


    return 1;
}

int validaCliente(Cliente c){

	char* cli = strdup(c->cli_ref);
	int cnumber = atoi(&cli[1]);

	if( strlen(cli) <= 5 &&
		isUpperN2(cli, 1) &&
		cnumber >= 1000 && cnumber <= 5000)
		return 1;
	else
		return 0;
}