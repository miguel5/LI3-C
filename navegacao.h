#ifndef NAVEGACAO_H
#define NAVEGACAO_H

#include <gmodule.h>

int um_first_question();
void um_second_question(char* prod_filename, char* cli_filename, char* venda_filename);
void um_present_result(char* prod_filename, char* cli_filename, char* venda_filename, int prod_validos, int cli_validos, int vendas_validos);
void dois_pergunta(char*);
void tres_question(int* mes, char ** produto, int* glob);
void tres_present_result(char* result);

void oito_question(int* mesbef, int* mesaft);

void onze_question(int* n);

void main_menu();
void opcao_invalida();

#endif
