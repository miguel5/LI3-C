#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int um_first_question() 
{
    char escolha;
    printf("Pretende utilizar ficheiros altenativos? s ou n\n");
    scanf("%c", &escolha);
    getchar();
    while(escolha != 's' && escolha != 'n')
    {
        printf("Escolha inválida. Responda com s ou n.\n");
        scanf("%c", &escolha);
        getchar();
    }
    if (escolha == 's')
        return 1;
    else 
        return 0;
}

void um_second_question(char* prod_filename, char* cli_filename, char* venda_filename)
{
    printf("Introduza nome do ficheiro de produtos\n");
    scanf("%s", prod_filename);
    printf("Introduza nome do ficheiro de clientes\n");
    scanf("%s", cli_filename);
    printf("Introduza nome do ficheiro de vendas\n");
    scanf("%s", venda_filename);
}

void um_present_result(char* prod_filename, char* cli_filename, char* venda_filename, int prod_validos, int cli_validos, int vendas_validos)
{
    printf("Ficheiro lido\tLinhas validadas\n");
    printf("%s\t%d\n", prod_filename, prod_validos);
    printf("%s\t%d\n", cli_filename, cli_validos);
    printf("%s\t%d\n", venda_filename, vendas_validos);
}

void main_menu()
{
    system("clear");
    printf("Introduza a opção pretendida\n");
    printf("1 - Ler ficheiros\n");
    printf("2 - Lista de produtos por letra\n");
    printf("3 - Número de vendas e faturação por produto\n");
    printf("4 - Lista de produtos não vendidos\n");
    printf("5 - Lista de clientes com compras realizadas\n");
    printf("6 - Produtos não comprados e clientes sem compras\n");
    printf("7 - Número de produtos comprados por cliente\n");
    printf("8 - Total de vendas por intervalo\n");
    printf("9 - Lista de clientes por produto comprado\n");
    printf("10 - Lista dos mais comprados por cliente\n");
    printf("11 - Lista dos produtos mais vendidos\n");
    printf("12 - 3 maiores gastos por cliente\n");
    printf("0 - Terminar o programa\n");
}

void opcao_invalida()
{
    system("clear");
    printf("Opção inválida.\nDeve introduzir número de 1 a 12 ou 0 para terminar.\n");
    sleep(2);
}
