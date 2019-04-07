#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "facturacao.h"
#include <gmodule.h>
#include "venda.h"


/*
* Struct de uma facturacao
* Array de 11 elementos (meses) cada um com uma arvore com produtos nas chaves e informação importante na informação. também tem um array de produtos não vendidos
*/
struct facturacao
{
	ProdTree trees[12];
	GArray *prodNV;
};

int cmp(char* a, char* b)
{
	return strcmp(a,b);
}

int cmp2(int a, int b)
{
	if (a==b) return 0;
	return (a>b);
}

Facturacao newFacturacao()
{
	Facturacao f = (Facturacao) malloc(sizeof(struct facturacao));
	int i = 0;
	while (i < 12)
	{
		ProdTree *p = malloc(sizeof(ProdTree));
		f->trees[i] = *p;
		f->trees[i].fact = 0;
		f->trees[i].v = 0;
		f->trees[i].prodtree = g_tree_new((GCompareFunc) cmp);
		i++;
	}
	f->prodNV = g_array_new(FALSE, FALSE, sizeof(char*));

	return f;
}

FactImp* criaFactImp()
{
	FactImp *f = (FactImp *) malloc(sizeof(FactImp));
	f->vendasN1=f->vendasN2=f->vendasN3=f->vendasP1=f->vendasP2=f->vendasP3=f->factN1=f->factP1=f->factN2=f->factP2=f->factN3=f->factP3=0;
	return f;
}

void insereNovaVenda(FactImp *f, double prec, int fil, char* tc, int q)
{
	double p = prec;
	if (strcmp(tc,"N")==0)
	{
		switch (fil)
		{
			case 1: f->factN1 += p; f->vendasN1 += q; break;
			case 2:	f->factN2 += p; f->vendasN2 += q; break;
			case 3:	f->factN3 += p; f->vendasN3 += q; break;
		}
	}
	else
	{
		switch (fil)
		{
			case 1: f->factP1 += p; f->vendasP1 += q; break;
			case 2:	f->factP2 += p; f->vendasP2 += q; break;
			case 3:	f->factP3 += p; f->vendasP3 += q; break;
		}
	}
}

FactImp* getFactImp(Facturacao f, int mes, char* prod)
{
	gpointer ptr;
	ptr = g_tree_lookup(f->trees[mes].prodtree, prod);
	FactImp *fa = (FactImp *) ptr;
	return fa;
}

void FacturacaoInsert(Facturacao f, Venda v)
{
	int mes = getMes(v)-1;
	double p = getPreco(v)*getQuantidade(v);
	char* prod = getProduto(v);
	int filial = getFilial(v);
	char* tc = getTipoCompra(v);
	int quantidade = getQuantidade(v);

	f->trees[mes].fact += p;
	f->trees[mes].v += getQuantidade(v);

	if (g_tree_lookup(f->trees[mes].prodtree, prod) != NULL)
	{
		FactImp *fa = getFactImp(f, mes, prod);
		insereNovaVenda(fa, p, filial, tc, quantidade);
		g_tree_insert(f->trees[mes].prodtree, prod, fa);
	}
	else
	{
		FactImp *fa = criaFactImp();
		insereNovaVenda(fa, p, filial, tc, quantidade);
		g_tree_insert(f->trees[mes].prodtree, prod, fa);
	}
}

int isProdThere(Facturacao f, char* prod)
{
	int i = 0;
	while (i < 12)
	{
		if (g_tree_lookup(f->trees[i].prodtree, prod) != NULL)
		{
			return 1;
		}
		i++;
	}

	return 0;
}

int sortNV(gpointer prod1, gpointer prod2)
{
	char* p1 = (char*) prod1;
	char* p2 = (char*) prod2;
	return strcmp(p1, p2);
}

void insereProdNV(Facturacao f, char* prod)
{
	g_array_append_val(f->prodNV, prod);
}

void sortProdNV(Facturacao f)
{
	g_array_sort(f->prodNV, (GCompareFunc) sortNV);
}

int traverseFree(gpointer key, gpointer value, gpointer data)
{
	free(key);
	free(value);

	return TRUE;
}

void freeFacturacao(Facturacao f)
{
	/* free trees and such */
	int i = 0;
	while (i < 12)
	{
		g_tree_foreach(f->trees[i].prodtree, traverseFree, 0);
		i++;
	}
	free(f->trees);
	/* free array */
	ProdVenda pv = malloc(sizeof(ProdVenda));
	int l = f->prodNV->len;
	while (i < l)
	{
		pv = g_array_index(f->prodNV, ProdVenda, i);
		free(pv);
		i++;
	}
	free(f->prodNV);

	free(f);
}

int totalVendas(Facturacao f, int bef, int aft)
{
	if (bef > aft)
	{
		int foo = aft;
		aft = bef;
		bef = foo;
	}

	int i = bef-1;
	int tot = 0;

	while (i < aft)
	{
		tot += f->trees[i].v;
		i++;
	}

	return tot;
}

float totalFact(Facturacao f, int bef, int aft)
{
	if (bef > aft)
	{
		int foo = aft;
		aft = bef;
		bef = foo;
	}

	int tot = 0;
	int i = bef-1;

	while (i < aft)
	{
		tot += f->trees[i].fact;
		i++;
	}

	return tot;
}

char* mesProd(Facturacao f, int mes, char* prod, int glob)
{
	/*glob 1 ut quer global, 0 quer por filial */
	mes = mes-1;
	gpointer ptr;
	int totalVN = 0;
	int totalVP = 0;
	float totalFN = 0;
	float totalFP = 0;

	char result[1000];
	char* resultfinal;

	if (g_tree_lookup(f->trees[mes].prodtree, prod) != NULL)
	{
		printf("Mês %d Produto %s\n", mes, prod);
		ptr = g_tree_lookup(f->trees[mes].prodtree, prod);
		FactImp *fa = (FactImp *) ptr;
		if (glob)
		{
			/* Global */
			totalVN = fa->vendasN1 + fa->vendasN2 + fa->vendasN3;
			totalVP = fa->vendasP1 + fa->vendasP2 + fa->vendasP3;
			totalFN = fa->factN1 + fa->factN2 + fa->factN3;
			totalFP = fa->factP1 + fa->factP2 + fa->factP3;
			sprintf(result, "Global:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao F: %f\n", totalVN, totalVP, totalFN, totalFP);
		}
		else
		{
			sprintf(result, "Filial 1:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao F: %f\nFilial 2:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao F: %f\nFilial 3:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao F: %f\n", fa->vendasN1, fa->vendasP1, fa->factN1, fa->factP1, fa->vendasN2, fa->vendasP2, fa->factN2, fa->factP2, fa->vendasN3, fa->vendasP3, fa->factN3, fa->factP3);
		}
	}
	else
	{
		printf("Produto não teve compras\n");
		sprintf(result, "Produto não teve compras\n");
	}

	resultfinal = strdup(result);
	//resultfinal = strdup(res);
	return resultfinal;

}

gboolean traverse(gpointer key, gpointer value, gpointer data)
{
	GArray *array;
	array = data;
	char* produto = (char*) key;
	FactImp *fa = (FactImp *) value;
	int tot = fa->vendasN1 + fa->vendasN2 + fa->vendasN3 + fa->vendasP1 + fa->vendasP2 + fa->vendasP3;

	/* See if already in array */
	int i = 0;
	int l = array->len;
	int notfound = 1;
	ProdVenda pvt = malloc(sizeof(ProdVenda));
	while (i < l)
	{
		pvt = g_array_index(array, ProdVenda, i);
		if (strcmp(pvt->prod, produto) == 0)
		{
			/* Add to array */
			pvt->vendas += tot;
			pvt->vendasfil1 = fa->vendasN1 + fa->vendasP1;
			pvt->vendasfil2 = fa->vendasN2 + fa->vendasP2;
			pvt->vendasfil3 = fa->vendasN3 + fa->vendasP3;
			notfound = 0;
		}
		i++;
	}

	/* Put in array */
	if (notfound)
	{
		ProdVenda pv = malloc(sizeof(ProdVenda));
		pv->prod = produto;
		pv->vendas = tot;
		pv->vendasfil1 = fa->vendasN1 + fa->vendasP1;
		pv->vendasfil2 = fa->vendasN2 + fa->vendasP2;
		pv->vendasfil3 = fa->vendasN3 + fa->vendasP3;
		g_array_append_val(array, pv);
	}

	return FALSE;
}

int sortProdVenda(gpointer p1, gpointer p2)
{
	ProdVenda *pp1 = (ProdVenda *) p1;
	ProdVenda *pp2 = (ProdVenda *) p2;
	if ((*pp1)->vendas == (*pp2)->vendas) return 0;
	if ((*pp1)->vendas > (*pp2)->vendas) return -1;
	return 1;
}

void nMaisVendidos(Facturacao f, int n)
{
	/* Make array of sales */
	int i = 0;

	GArray *array;
	array = g_array_new(FALSE, FALSE, sizeof(ProdVenda));

	while (i < 12)
	{
		g_tree_foreach(f->trees[i].prodtree, traverse, array);
		i++;
	}

	/* Now sort it */
	g_array_sort(array, (GCompareFunc) sortProdVenda);

	/* Now print n */ 
	printf("%d Produtos Mais Vendidos:\n", n);
	i = 0;
	ProdVenda pv = malloc(sizeof(ProdVenda));
	while (n > 0)
	{
		pv = g_array_index(array, ProdVenda, i);
		printf("%s com:\n%d vendas na filial 1\n%d vendas na filial 2\n%d vendas na filial 3\n", pv->prod, pv->vendasfil1, pv->vendasfil2, pv->vendasfil3);
		i++;
		n--;
	}
}

void quantosNV(Facturacao f)
{
	int l = f->prodNV->len;
	printf("Existem %d produtos não vendidos\n", l);
}

void listaNV(Facturacao f)
{
	int l = f->prodNV->len;
	int i = 0;
	char* prod;

	sortProdNV(f);
	printf("%d Produtos Não Vendidos:\n", f->prodNV->len);
	while (i < l)
	{
		prod = g_array_index(f->prodNV, char*, i);
		printf("%s\n", prod);
		i++;
	}
}