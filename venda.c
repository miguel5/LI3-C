#include "venda.h"


/*Struct de vendas?*/
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

void setMes(int mes, Venda v){
	v->mes = mes;
}
