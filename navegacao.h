#ifndef NAVEGACAO_H
#define NAVEGACAO_H

int um_first_question();
void um_second_question(char* prod_filename, char* cli_filename, char* venda_filename);
void um_present_result(char* prod_filename, char* cli_filename, char* venda_filename, int prod_validos, int cli_validos, int vendas_validos);
void main_menu();
void opcao_invalida();

#endif