#include <stdio.h>
#include <stdlib.h>
#include "venda.h"

/*
Compilar com "make exemplo"
*/
int main(){

	Venda v = malloc(sizeof(Venda));
	setMes(5, v);

	printf("%d\n", getMes(v));


	return 0;
}