#include <string.h>
#include <stdlib.h>
#include "produto.h"

/*
* Struct de um produto
*/
struct produto
{
	char* prod_ref;
};

char* getProdRef(Produto p)
{
	return p->prod_ref;
}

Produto criaProd(char* prod_ref)
{
	Produto p = (Produto) malloc(sizeof(struct produto));
	p->prod_ref = strdup(prod_ref);

	return p;
}