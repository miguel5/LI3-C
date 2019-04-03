#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct cliente* Cliente;

Cliente criaCliente(char*);

char* getCliRef(Cliente);

int validaCliente(Cliente);

#endif