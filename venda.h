#ifndef VENDA_H
#define VENDA_H


typedef struct venda* Venda;

char* getTipoCompra(Venda);

char* getCliente(Venda);

char* getProduto(Venda);

int getQuantidade(Venda);

double getPreco(Venda);

int getMes(Venda);

int getFilial(Venda);

void setTipoCompra(char*, Venda);

void setCliente(char*, Venda);

void setProduto(char*, Venda);

void setQuantidade(int, Venda);

void setPreco(double, Venda);

void setMes(int, Venda);

void setFilial(int, Venda);		

#endif