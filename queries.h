#ifndef QUERIES_H
#define QUERIES_H

void query_um(CatProd, CatCli, char*, char*, char*);

/* Query três */
char* query_tres(Facturacao f, int mes, char* prod, int glob);

/* Query quatro */
void query_quatro(Facturacao f);

/* Query seis */
void query_seis(Facturacao f);

/* Query oito */
void query_oito(Facturacao f, int bef, int aft);

/* Query onze */
void query_onze(Facturacao f, int n);

#endif
