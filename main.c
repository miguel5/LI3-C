#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gmodule.h>
#include "venda.h"
#include "produto.h"
#include "cliente.h"
#include "filial.h"

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

    Venda v = novaVenda(campos[3],
                        campos[4],
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

// Ler produtos e guardar numa estrutura CatProd
void lerProdutos(CatProd cp)
{
    FILE *fp;
    char* line = malloc(sizeof(char*));

    int val = 0;

    if((fp = fopen("Produtos.txt", "r")) != NULL)
    {
        while (fgets(line,7,fp) != NULL)
        {
            Produto prod = criaProd(line);
            val = validaProduto(prod);

            // Store no array
            if (val){
                catProdInsert(cp, strdup(line), prod);
                free(prod);
            }

        }
    }

    fclose(fp);
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

// Ler e validar clientes
void lerClientes(CatCli cc)
{
    FILE *fp;
    char* line = malloc(sizeof(char*));

    int val = 0;

    if((fp = fopen("Clientes.txt", "r")) != NULL)
    {
        while (fgets(line,6,fp) != NULL)
        {   
            Cliente cli = criaCliente(line);
            val = validaCliente(cli);

            /* Store no array */
            if (val)            
                catCliInsert(cc, strdup(line), cli);
                free(cli);            
        }
    }
    else
        fprintf(stderr, "%s\n", ERROR);

    fclose(fp);
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

void lerVendas(Filial vendasTree, CatProd cp, CatCli cc)
{
    FILE *fp;

    Venda venda;
    char* line = malloc(sizeof(char*));
    char* linef = malloc(sizeof(char*));
    int val = 0;
    int validCount = 0;

    if((fp = fopen("Vendas_1M.txt", "r")) != NULL)
    {
        while (fgets(line,35,fp) != NULL)
        {
            linef = strdup(line);
            venda = regVenda(linef);
            
            // Validar todos os aspetos
            val = validaVenda(venda, cp, cc);
            
            // Store na GTree
            if (val){
                filialInsert(vendasTree, venda, "1");
                validCount++;
                printf("%s\n", vendaToString(venda));
                printf("Vendas válidas: %d\n", validCount);
                //free(venda);
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
    /* Começar os arrays
    char** arrayProd = (char**) malloc(sizeof(char*));
    arrayProd[0] = NULL;
    int arrayProdSize = 0;
    int* sizeProdPtr = &arrayProdSize;

    char** arrayCli = (char**) malloc(1 * sizeof(char*));
    arrayCli[0] = NULL;
    int arrayCliSize = 0;
    int* sizeCliPtr = &arrayCliSize;*/

    CatProd cp = newCatProd();
    CatCli cc = newCatCli();

    /* Ler os ficheiros e validar para arrays */
    //arrayProd = lerProdutos(arrayProd, sizeProdPtr);
    //arrayCli = lerClientes(arrayCli, sizeCliPtr);
    lerProdutos(cp);
    lerClientes(cc);

    //Produto p = (Produto) catProdLookup(cp, "PE1822");
    //printf("%s\n", getProdRef(p));

    /*
    char* foo = catCliLookup(cc, "A3439");
    if(foo != NULL)
        printf("%s\n", foo);
    else
        printf("Lookup returned NULL!\n");
    */

    //Venda v = novaVenda("N", "A3439", "HR1648", 9.99, 20, 8, 3);
    //printf("%d\n", validaVenda(v, cp, cc));

    /* Ordenar arrays de Produtos
    qsort(arrayProd, arrayProdSize, sizeof(char *), compareFunction);
    arrayProd = duplicate_removal(arrayProd, sizeProdPtr);

    qsort(arrayCli, arrayCliSize, sizeof(char *), compareFunction);
    arrayCli = duplicate_removal(arrayCli, sizeCliPtr);*/
    
    /* Criar ficheiro de vendas válidas    
    ficheiroProdCliValidos(arrayProd, "Produtos_Validos.txt");
    ficheiroProdCliValidos(arrayCli, "Clientes_Validos.txt");
    */
    
    //Venda foo = novaVenda("N", "Ze Manel", "qwerty", 9.99, 20, 8, 3);
    //Venda foo2 = novaVenda("N", "Ze Manel", "welele", 9.99, 20, 8, 3);
    //printf("%s\n", vendaToString(foo));
    //printf("Is equal: %d\n", vendaCmp(foo, foo2));

    Filial f = newFilial();
    lerVendas(f, cp, cc);
    //forEach1(f);
    //printf("CatProd nodos: %d\n", catProdNodos(cp));
    //printf("CatCli nodos: %d\n", catCliNodos(cc));
    /*
     * Teste modulo filial.c
    */
    /*
    Filial f = newFilial();
    filialInsert(f, foo, "1");
    printf("%d\n", filialLookup(f, foo2));
    */

    /* Libertar a memória 
    int i;
    for (i = 0; i < (*sizeProdPtr); i++)
        free(arrayProd[i]);
    free(arrayProd);

    for (i = 0; i < (*sizeCliPtr); i++)
        free(arrayCli[i]);
    free(arrayCli);*/

    return 0;
}
