#ifndef FACTURACAO_H
#define FACTURACAO_H

#include <gmodule.h>
#include "venda.h"

/* Informação importante a cada produto sobre facturação */
typedef struct factImp
{
	int vendasN1, vendasN2, vendasN3, vendasP1, vendasP2, vendasP3;
	float factN1, factP1, factN2, factP2, factN3, factP3;
} FactImp;

/* Conteudo de cada mês */
typedef struct prodTree
{
	GTree* prodtree;
	float fact;
	int v;
} ProdTree;

typedef struct prodvend
{
	char* prod;
	int vendas, vendasfil1, vendasfil2, vendasfil3;
} *ProdVenda;

/* Facturação */
typedef struct facturacao* Facturacao;

/* Aloca a memória e cria uma facturação */
Facturacao newFacturacao();

/* Aloca a memória e cria uma estrutura de dados que contém tudo de importante para a facturação */
FactImp* criaFactImp();

/* Insere os dados de uma venda na facturação */
void FacturacaoInsert(Facturacao f, Venda v);

/* Insere um produto não vendido na facturação */
void insereProdNV(Facturacao f, char* prod);

/* Verifica se um produto existe numa facturação */
int isProdThere(Facturacao f, char* prod);

/* Liberta a memória ocupada por uma facturação */
void freeFacturacao(Facturacao f);

#endif