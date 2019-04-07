#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include "CatProd.h"
#include "CatCli.h"
#include "facturacao.h"
#include "navegacao.h"
#include <gmodule.h>

struct facturacao
{
    ProdTree trees[12];
    GArray *prodNV;
};

/* Recebe apontador para sistema de gestão de vendas da main */
void query_um(CatProd prod_list, CatCli cli_list, char* prod_filename, char* cli_filename, char* venda_filename) /* Vai ser alterado devido a dependências */
{    
    /* Funções para determinar se o sistema atual contém dados. Se existirem, têm de ser apagados */
    freeProd(prod_list);
    freeCli(cli_list);
    /*
    freeFaturacao(faturacao);
    for (int i = 0; i < 3; i++)    
            freeFilial(filial[i]);
    */

    prod_list = newCatProd();
    cli_list = newCatCli();

    /* Receber do utilizador a proveniência da informação: nome dos ficheiros ou ficheiros por omissão */
    if (um_first_question()) /* Retorna 1 ou 0 */        
        um_second_question(prod_filename, cli_filename, venda_filename);

    /*
    fillFaturacao(full_data -> faturacao);
    for (i = 0; i < 3; i++)
        fillFilial(full_data -> filial[3]);
    */
}

char* query_tres(Facturacao f, int mes, char* prod, int glob)
{
    /*glob 1 quer global, 0 quer por filial */
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
            /*Global:\n
            Total Vendas N: %d\nTotal Vendas P: %d\n
            Total Facturacao N: %f\nTotal Facturacao F: %f\n*/
            sprintf(result, "Global:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao F: %f\n", totalVN, totalVP, totalFN, totalFP);
        }
        else
        {
            /* Filial a Filial 
            Filial 1:\n
            Total Vendas N: %d\nTotal Vendas P: %d\n
            Total Facturacao N: %f\nTotal Facturacao F: %f\n
            Filial 2:\n
            Total Vendas N: %d\nTotal Vendas P: %d\n
            Total Facturacao N: %f\nTotal Facturacao F: %f\n
            Filial 3:\n
            Total Vendas N: %d\nTotal Vendas P: %d\n
            Total Facturacao N: %f\nTotal Facturacao F: %f\n*/
            sprintf(result, "Filial 1:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao P: %f\nFilial 2:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao P: %f\nFilial 3:\nTotal Vendas N: %d\nTotal Vendas P: %d\nTotal Facturacao N: %f\nTotal Facturacao P: %f\n", fa->vendasN1, fa->vendasP1, fa->factN1, fa->factP1, fa->vendasN2, fa->vendasP2, fa->factN2, fa->factP2, fa->vendasN3, fa->vendasP3, fa->factN3, fa->factP3);
        }
    }
    else
    {
        printf("Produto não teve compras\n");
        sprintf(result, "Produto não teve compras\n");
    }

    resultfinal = strdup(result);
    return resultfinal;
}

/* Função de ordenar por ordem alfabeta o array de produtos não vendidos */
int sortNVN(gconstpointer prod1, gconstpointer prod2)
{
    return -1;
}

void query_quatro(Facturacao f)
{
    int l = f->prodNV->len;
    int i = 0;
    char* prod;

    /* Sort Array */
    g_array_sort(f->prodNV, (GCompareFunc) sortNVN);

    /* Print da Lista */
    printf("%d Produtos Não Vendidos:\n", f->prodNV->len);
    while (i < l)
    {
        prod = g_array_index(f->prodNV, char*, i);
        printf("Produto: %s\n", prod);
        i++;
    }
    printf("Fim lista Não Vendidos\n");
    //listaNV(f);
}

void query_seis(Facturacao f)
{
    //quantosNV(f);
    int l = f->prodNV->len;
    printf("Existem %d produtos não vendidos\n", l);
}

void query_oito(Facturacao f, int bef, int aft)
{
    float totF = 0;
    int totV = 0;
    if (bef > aft)
    {
        int foo = aft;
        aft = bef;
        bef = foo;
    }

    int i = bef-1;

    while (i < aft)
    {
        totF += f->trees[i].fact;
        totV += f->trees[i].v;
        i++;
    }

    printf("Total de Vendas entre %d e %d: %d\n", bef, aft, totV);
    printf("Total de Facturação entre %d e %d: %f\n", bef, aft, totF);
}

/* Função que das arvores mensais vai criar uma global */
gboolean traverseMakeAllTree(gpointer key, gpointer value, gpointer data)
{
    GTree *tree;
    tree = data;
    char* produto = (char*) key;
    FactImp *fa = (FactImp *) value;

    if (g_tree_lookup(tree, produto) != NULL)
    {
        gpointer ptr;
        ptr = g_tree_lookup(tree, produto);
        FactImp *fat = (FactImp *) ptr;
        fat->vendasN1 += fa->vendasN1;
        fat->vendasN2 += fa->vendasN2;
        fat->vendasN3 += fa->vendasN3;
        fat->vendasP1 += fa->vendasP1;
        fat->vendasP2 += fa->vendasP2;
        fat->vendasP3 += fa->vendasP3;
        g_tree_insert(tree, produto, fat);
    }
    else
    {
        FactImp *fat = criaFactImp();
        fat->vendasN1 = fa->vendasN1;
        fat->vendasN2 = fa->vendasN2;
        fat->vendasN3 = fa->vendasN3;
        fat->vendasP1 = fa->vendasP1;
        fat->vendasP2 = fa->vendasP2;
        fat->vendasP3 = fa->vendasP3;
        g_tree_insert(tree, produto, fat);
    }

    return FALSE;
}

/* Função de comparação para a arvore geral */
int cmpN(char* a, char* b)
{
    return strcmp(a,b);
}

/* Coloca a maior venda atravessando a arvore geral */
int traverseMax(gpointer key, gpointer value, gpointer data)
{
    ProdVenda *pm = (ProdVenda *) data;
    char* produto = (char*) key;
    FactImp *fa = (FactImp *) value;
    int tot = fa->vendasN1 + fa->vendasN2 + fa->vendasN3 + fa->vendasP1 + fa->vendasP2 + fa->vendasP3;

    if (tot >= (*pm)->vendas)
    {
        (*pm)->vendas = tot;
        (*pm)->prod = produto;
        (*pm)->vendasfil1 = fa->vendasN1 + fa->vendasP1;
        (*pm)->vendasfil2 = fa->vendasN2 + fa->vendasP2;
        (*pm)->vendasfil3 = fa->vendasN3 + fa->vendasP3;
    }

    return 0;

}

void query_onze(Facturacao f, int n)
{
    int i = 0;

    GTree *prodvT;
    prodvT = g_tree_new((GCompareFunc) cmpN);

    while (i < 12)
    {
        g_tree_foreach(f->trees[i].prodtree, traverseMakeAllTree, prodvT);
        i++;
    }

    ProdVenda pv = malloc(sizeof(ProdVenda));

    while (n > 0)
    {
        pv->vendas = pv->vendasfil1 = pv->vendasfil2 = pv->vendasfil3 = 0;
        pv->prod = "";
        g_tree_foreach(prodvT, traverseMax, &pv);
        printf("Produto Mais Vendido numero %d: %s com %d vendas\n", n, pv->prod, pv->vendas);
        g_tree_remove(prodvT, pv->prod);
        n--;
    }
}