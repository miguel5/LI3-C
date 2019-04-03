#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

// Funções de validação
int isUpperN1(char letters[], int n)
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

int validaProduto(Produto p){

	char* prod = strdup(getProdRef(p));
	int pnumber = atoi(&prod[2]);
	
	if( strlen(prod) <= 6 &&
		isUpperN1(prod, 2) &&
		pnumber >= 1000 && pnumber <= 9999)
		return 1;
	else
		return 0;
}