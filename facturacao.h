#ifndef FACTURACAO_H
#define FACTURACAO_H

#include "venda.h"

typedef struct facturacao* Facturacao;

Facturacao criaFacturacao();

void insereVendaV(Facturacao f, Venda v);

void insereProdNV(Facturacao f, char* prod);

#endif