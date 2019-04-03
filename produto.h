#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct produto* Produto;

Produto criaProd(char*);

char* getProdRef(Produto);

int validaProduto(Produto);

#endif