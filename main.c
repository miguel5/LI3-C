#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "venda.h"
#include "produto.h"
#include "cliente.h"
#include "filial.h"
#include "CatProd.h"

#define CAMPOSVENDA 7
#define ERROR "Erro ao abrir ficheiro!"


Venda* insere_struct_array(Venda* array, const Venda elem) 
{
    int lastIndex = 0;
    while (array[lastIndex] != NULL)    /* para saber o tamanho actual */
        lastIndex++;

    Venda* newarray = (Venda*) realloc(array, (lastIndex+2) * sizeof(Venda));   /* realoca */
    if (!newarray) return array;

    Venda newElem = cloneVenda(elem);
    //if (!newElem) return newarray;

    newarray[lastIndex] = newElem;     /* inserção do novo elementodn */
    lastIndex++;
    newarray[lastIndex] = NULL;           /* coloca a marca */
    return newarray;
}

char** insere_elem_array(char** array, const char *elem, int* sizePtr) 
{
    /*
    int lastIndex = 0;
    while (array[lastIndex] != NULL)     //para saber o tamanho actual
        lastIndex++;
    */

    char** newarray = (char**) realloc(array, (*sizePtr + 2) * sizeof(char*));   /* realoca */
    if (!newarray) return array;

    char* newElem = strdup(elem);
    if (!newElem) return newarray;

    newarray[*sizePtr] = newElem;     // inserção do novo elemento
    /* newarray[(char) array[0]] = NULL;          //coloca a marca */
    (*sizePtr)++;
    return newarray;
}

char** tokenizeLinhaVendaDyn(char* vendaRaw) 
{
    int index = 0;
    /* dimensão vertical */
    char** campos = (char**) malloc(CAMPOSVENDA * sizeof(char*)); 
    char* token = strtok(vendaRaw," ");  
    while(!(token == NULL)) {
        campos[index] = strdup(token);
        /* printf(" %s\n", token); */
        token = strtok(NULL," ");
        index++;
    }
    return campos;
}

// Função que recebe uma linha de uma venda valida e transforma numa estrutura Venda
Venda regVenda(char* linhaVendaOk)
{
    char** campos;
    campos = tokenizeLinhaVendaDyn(linhaVendaOk);

    Venda v = novaVenda(campos[4],
                        campos[3],
                        campos[0],
                        atof(campos[1]),
                        atoi(campos[2]),
                        atoi(campos[5]),
                        atoi(campos[6]));

    //free(campos);
    return v;
}

/* Funções de comparação entre arrays para validar*/
int isInArray(char* toCheck, char** array)
{
    int i = 0;

    while (array[i] != NULL)
    {
        if (strcmp(toCheck, array[i]))
        {
            return 1;
        }
        i++;
    }

    return 0;
}

/* Funções de validação */
int isUpperN(char letters[], int n)
{
    int i = 0;

    /* while (i < strlen(letters)) */
    while (i < n)
    {
        if (!isupper(letters[i])) return 0;
        i++;
    } 


    return 1;
}

int isBetweenNum(int n, int l, int r)
{
    return ((n >= l) && (n <= r));
}

// Teste
/*
void lerProdutos(CatProd cp)
{
    FILE *fp;
    char line[7];

    char* pnumber;

    int val = 1;

    if((fp = fopen("Produtos.txt", "r")) != NULL)
    {
        while (fgets(line,7,fp) != NULL)
        {
            val = (strlen(line) <= 6);        

            if (val)
            {
                val = isUpperN(line,2);
            }

            if (val)
            {
                // Check number
                pnumber = &line[2];
                val = isBetweenNum(atoi(pnumber), 1000, 9999);
            }
            // Store no array
            if (val)
                catProdInsert(cp, line, 1);            
        }
    }

    fclose(fp);
}
*/

/* Ler e validar ficheiro produtos, separar em 2 funções depois */
char** lerProdutos(char** arrayProd, int* sizeProdPtr)
{
    FILE *fp;
    char line[7];
    //int i = 0;

    char* pnumber;

    int val = 1;

    if((fp = fopen("Produtos.txt", "r")) != NULL)
    {
        while (fgets(line,7,fp) != NULL)
        {
            val = (strlen(line) <= 6);        

            if (val)
            {
                val = isUpperN(line,2);
            }

            if (val)
            {
                //Check number
                pnumber = &line[2];
                val = isBetweenNum(atoi(pnumber), 1000, 9999);
            }
            // Store no array
            if (val)
                arrayProd = insere_elem_array(arrayProd, line, sizeProdPtr);            
        }
    }

    fclose(fp);
    return arrayProd;
}

char** duplicate_removal(char** array, int* old_size)
{
    int new_size = 0, i;
    char** temp_array = (char**) malloc(*old_size * sizeof(char*));

    temp_array[0] = strdup(array[0]);
    new_size++;

    for (i = 1; i < *old_size; i++)
    {
        if (strcmp(array[i], array[i - 1]) != 0)
        {
            temp_array[new_size] = strdup(array[i]);
            new_size++;
        }
    }    
    temp_array[new_size] = NULL;
    for (i = 0; i < *old_size; i++)
        free(array[i]);
    free(array);
    *old_size = new_size;
    return temp_array;
}
/* Ler e validar clientes */
char** lerClientes(char** arrayCli, int* sizeCliPtr)
{
    FILE *fp;
    char line[6];

    char* cnumber;

    int val = 1;

    if((fp = fopen("Clientes.txt", "r")) != NULL)
    {
        while (fgets(line,6,fp) != NULL)
        {
            val = (strlen(line) <= 5);

            if (val) 
                val = isUpperN(line, 1); 

            /* Check number */
            if (val)
            {
                cnumber = &line[1];
                val = isBetweenNum(atoi(cnumber), 1000, 5000);
            }

            /* Store no array */
            if (val)            
                arrayCli = insere_elem_array(arrayCli, line, sizeCliPtr);            
        }
    }
    else
        fprintf(stderr, "%s\n", ERROR);

    fclose(fp);
    return arrayCli;
}

void ficheiroProdCliValidos(char** array, char* nome)
{
    FILE *fp;    
    if ((fp = fopen(nome, "w")) == NULL)
    {
        fprintf(stderr, "%s\n", ERROR);
        return;
    }
    int i = 0;
    /* Ciclo para escrever */
    if (array[0] == NULL) 
        printf("ARRAY VAZIO !!\n");
    else 
        while (array[i] != NULL) 
        {
            fprintf(fp, "%s\n", array[i]);
            i++;
        }
    fclose(fp);
}

/* Ler e validar ficheiro vendas, separar em 2 funções depois */
void lerVendas(Venda* arrayVendas, char** arrayProd, char** arrayCli)
{
    FILE *fp;

    Venda venda;
    char line[30];
    char linef[30];
    //int i = 0;
    /*
    char* produto;
    char* preco;
    char* quant;
    char* compra;
    char* cliente;
    char* mes;
    char* filial;
    */
    //int l;

    int val = 1;
    int validCount = 0;

    if((fp = fopen("Vendas_1M.txt", "r")) != NULL)
    {
        while (fgets(line,35,fp) != NULL)
        {
            strcpy(linef, line);

            venda = regVenda(linef);
            printf("%s\n", vendaToString(venda));
            printf("validCount: %d\n", validCount);
            
            /* Validar todos os aspetos */
            val = isBetweenNum(getPreco(venda),0.0,999.99);

            if (val) { val = isBetweenNum(getQuantidade(venda),1,200); }

            if (val) { val = isBetweenNum(getMes(venda),1,12); }

            if (val) { val = isBetweenNum(getFilial(venda),1,3); }

            if (val) { val = isInArray(getProduto(venda), arrayProd); }

            if (val) { val = isInArray(getCliente(venda), arrayCli); }

            //printf("val: %d\n", val);
            
            /* Store no array */
            if (val){
                arrayVendas = insere_struct_array(arrayVendas, venda);
                validCount++;
            }
        }
    }
    else
        fprintf(stderr, "%s\n", ERROR);

    fclose(fp);
}

/* Criar ficheiro de vendas válidas */
void ficheiroVendasCertas(Venda* arrayVendas)
{
    FILE *fp;    
    fp = fopen("Vendas_1MValidas.txt", "w");
    Venda str;
    int i = 0;
    /* Ciclo para escrever */
    if (arrayVendas[0] == NULL) 
        printf("ARRAY VAZIO !!\n");
    else 
        while ((str = arrayVendas[i]) != NULL) 
        {
            fprintf(fp, "%s %f %d %s %s %d %d\n",   getProduto(str),
                                                    getPreco(str),
                                                    getQuantidade(str),
                                                    getTipoCompra(str),
                                                    getCliente(str),
                                                    getMes(str),
                                                    getFilial(str));
            i++;
        }
    fclose(fp);
}
/*
void printArrayDyn (char** array) {
    char* str; int i=0;
    if(array[0] == NULL) printf("ARRAY VAZIO !!\n");
    else {
           while ((str = array[i]) != NULL) {
              printf("%s\n", str);
              i++;
           }
    }
}
*/
/* Ficheiros de validação? */
int maisLongaVenda(char* vendas[])
{
    int i = 1;
    int max = 0;

    if (vendas[0] != NULL)
    {
        max = strlen(vendas[0]);

        while (vendas[i] != NULL)
        {
            if (strlen(vendas[i]) > max)
            {
                max = strlen(vendas[i]);
            }

            i++;
        }
    }

    return max;
}

int compareFunction(const void* a, const void* b)
{
    const char* strA = *(const char**) a;
    const char* strB = *(const char**) b;
    return strcmp(strA, strB);
}

/* Main */
int main(int argc, char const *argv[])
{
    /* Começar os arrays */
    char** arrayProd = (char**) malloc(sizeof(char*));
    arrayProd[0] = NULL;
    int arrayProdSize = 0;
    int* sizeProdPtr = &arrayProdSize;

    char** arrayCli = (char**) malloc(1 * sizeof(char*));
    arrayCli[0] = NULL;
    int arrayCliSize = 0;
    int* sizeCliPtr = &arrayCliSize;

    //CatProd cp = newCatProd();

    /* Ler os ficheiros e validar para arrays */
    arrayProd = lerProdutos(arrayProd, sizeProdPtr);
    arrayCli = lerClientes(arrayCli, sizeCliPtr);
    
    /* Ordenar arrays de Produtos */
    qsort(arrayProd, arrayProdSize, sizeof(char *), compareFunction);
    arrayProd = duplicate_removal(arrayProd, sizeProdPtr);

    qsort(arrayCli, arrayCliSize, sizeof(char *), compareFunction);
    arrayCli = duplicate_removal(arrayCli, sizeCliPtr);
    
    /* Criar ficheiro de vendas válidas */    
    ficheiroProdCliValidos(arrayProd, "Produtos_Validos.txt");
    ficheiroProdCliValidos(arrayCli, "Clientes_Validos.txt");

    /*
    * Teste modulo produto.c
    Produto p = criaProd("A1234");
    printf("%s\n", getProdRef(p));
    */

    /*
     * Teste modulo cliente.c
    Cliente c = criaCliente("Ze Manel");
    printf("%s\n", getCliRef(c));
    */
    
    //Venda foo = novaVenda("N", "Ze Manel", "qwerty", 9.99, 20, 8, 3);
    //Venda foo2 = novaVenda("N", "Ze Manel", "welele", 9.99, 20, 8, 3);
    //printf("%s\n", vendaToString(foo));
    //printf("Is equal: %d\n", vendaCmp(foo, foo2));

    /*
    Venda* arrayVendas = (Venda*) malloc(sizeof(Venda)*1100000);
    lerVendas(arrayVendas, arrayProd, arrayCli);
    ficheiroVendasCertas(arrayVendas);
    */

    /*
     * Teste modulo filial.c
    */
    /*
    Filial f = newFilial();
    filialInsert(f, foo, "1");
    printf("%d\n", filialLookup(f, foo2));
    */

    /* Libertar a memória */
    int i;
    for (i = 0; i < (*sizeProdPtr); i++)
        free(arrayProd[i]);
    free(arrayProd);

    for (i = 0; i < (*sizeCliPtr); i++)
        free(arrayCli[i]);
    free(arrayCli);

    return 0;
}
