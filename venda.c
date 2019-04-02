#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "venda.h"


/*Struct de vendas*/
struct venda
{
    char* tipoCompra;
    char* cliente;
    char* produto;
    double preco;
    int quantidade;
    int mes;
    int filial;
};

/*
* Getters
*/

char* getTipoCompra(Venda v){
	return v->tipoCompra;
}

char* getCliente(Venda v){
	return v->cliente;
}

char* getProduto(Venda v){
	return v->produto;
}

int getQuantidade(Venda v){
	return v->quantidade;
}

double getPreco(Venda v){
	return v->preco;
}

int getMes(Venda v){
	return v->mes;
}

int getFilial(Venda v){
	return v->filial;
}

/*
* Setters
*/

void setTipoCompra(char* tipoCompra, Venda v){
	v->tipoCompra = tipoCompra;
}

void setCliente(char* cliente, Venda v){
	v->cliente = cliente;
}

void setProduto(char* produto, Venda v){
	v->produto = produto;
}

void setQuantidade(int quantidade, Venda v){
	v->quantidade = quantidade;
}

void setPreco(double preco, Venda v){
	v->preco = preco;
}

void setMes(int mes, Venda v){
	v->mes = mes;
}

void setFilial(int filial, Venda v){
	v->filial = filial;
}

Venda novaVenda(char* tipoCompra, char* cliente, char* produto, double preco, int qtd, int mes, int filial){
	
	Venda v = (Venda) malloc(sizeof(struct venda));

	v->tipoCompra = strdup(tipoCompra);
	v->cliente = strdup(cliente);
	v->produto = strdup(produto);
	v->quantidade = qtd;
	v->preco = preco;
	v->mes = mes;
	v->filial = filial;

	return v;
}

Venda cloneVenda(Venda v){
	Venda clone = (Venda) malloc(sizeof(struct venda));

	clone->tipoCompra = v->tipoCompra;
	clone->cliente = v->cliente;
	clone->produto = v->produto;
	clone->quantidade = v->quantidade;
	clone->preco = v->preco;
	clone->mes = v-> mes;
	clone->filial = v->filial;

	return clone;
}

int vendaCmp(Venda v1, Venda v2){
	
	if( strcmp(v1->tipoCompra, v2->tipoCompra) == 0 &&
		strcmp(v1->cliente, v2->cliente) == 0 &&
		strcmp(v1->produto, v2->produto) == 0 &&
		v1->quantidade == v2->quantidade &&
		v1->preco == v2->preco &&
		v1->mes == v2->mes &&
		v1->filial == v2->filial)
		return 0;
	else
		return strcmp(v1->produto, v2->produto);
}

char* vendaToString(Venda v){
	char* str = malloc(sizeof(char)*100);

	sprintf(str, "%s %f %d %s %s %d %d",    v->produto,
											v->preco,
											v->quantidade,
											v->tipoCompra,
											v->cliente,
											v->mes,
											v->filial);
	return str;
}