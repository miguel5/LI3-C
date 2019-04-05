#include <stdlib.h>
#include "CatProd.h"
#include "CatCli.h"
#include "facturacao.h"
#include <gmodule.h>

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

void query_tres(Facturacao f, int mes, char* prod, int glob)
{
    /*glob 1 ut quer global, 0 quer por filial */
    mes = mes-1;
    gpointer ptr;
    int totalVN = 0;
    int totalVP = 0;
    float totalFN = 0;
    float totalFP = 0;
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
            printf("Global:\n");
            printf("Total Vendas N: %d\nTotal Vendas P: %d\n", totalVN, totalVP);
            printf("Total Facturacao N: %f\nTotal Facturacao F: %f\n", totalFN, totalFP);
        }
        else
        {
            /* Filial a Filial */
            printf("Filial 1:\n");
            printf("Total Vendas N: %d\nTotal Vendas P: %d\n", fa->vendasN1, fa->vendasP1);
            printf("Total Facturacao N: %f\nTotal Facturacao F: %f\n", fa->factN1, fa->factP1);
            printf("Filial 2:\n");
            printf("Total Vendas N: %d\nTotal Vendas P: %d\n", fa->vendasN2, fa->vendasP2);
            printf("Total Facturacao N: %f\nTotal Facturacao F: %f\n", fa->factN2, fa->factP2);
            printf("Filial 3:\n");
            printf("Total Vendas N: %d\nTotal Vendas P: %d\n", fa->vendasN3, fa->vendasP3);
            printf("Total Facturacao N: %f\nTotal Facturacao F: %f\n", fa->factN3, fa->factP3);
        }
    }
}
