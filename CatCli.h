#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct cliente* Cliente;

Cliente newCliente();
void clienteInsert(Cliente c, char* key, void* value);
void* clienteLookup(Cliente c, char* key);

#endif