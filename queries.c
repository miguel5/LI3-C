#include <stdlib.h>
#include "CatProd.h"
#include "CatCli.h"

/* Recebe apontador para sistema de gestão de vendas da main */
void query_um(CatProd prod_list, CatCli cli_list) /* Vai ser alterado devido a dependências */
{    
    int prod_validos, cli_validos, vendas_validos;
    char* prod_filename = NULL;
    char* cli_filename = NULL;
    char* venda_filename = NULL;

    /* Funções para determinar se o sistema atual contém dados. Se existirem, têm de ser apagados */
    if (!isProdEmpty(prod_list))
        freeProd(prod_list);
    if (!isCliEmpty(cli_list))
        freeCli(cli_list);
    /*
    if (!isFatEmpty(faturacao))
        freeFaturacao(faturacao);
    for (int i = 0; i < 3; i++)    
        if (!isFilEmpty(filial[i]))
            freeFilial(filial[i]);
    */

    prod_list = newCatProd();
    cli_list = newCliente();

    /* Receber do utilizador a proveniência da informação: nome dos ficheiros ou ficheiros por omissão */
    if (um_first_question()) /* Retorna 1 ou 0 */        
        um_second_question(prod_filename, cli_filename, venda_filename);

    prod_validos = lerProdutos(prod_list, prod_filename);
    cli_validos = lerClientes(cli_list, cli_filename);
    /*
    fillFaturacao(full_data -> faturacao);
    for (i = 0; i < 3; i++)
        fillFilial(full_data -> filial[3]);
    */
    um_present_result(prod_filename, cli_filename, venda_filename, prod_validos, cli_validos, vendas_validos);
}