#include "venda.h"


/*Struct de vendas*/
struct venda
{
    char* tipoCompra;
    char* cliente;
    char* produto;
    int quantidade;
    double preco;
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