#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#define CAMPOSVENDA 7

/*Struct de vendas?*/
struct venda
{
    char* tipoCompra;
    char* cliente;
    char* produto;
    int quantidade;
    double preco;
    int mes;
    int filial;
};

typedef struct venda* Venda;

Venda* insere_struct_array(Venda* array, const Venda elem) 
{
    int lastIndex = 0;
    while (array[lastIndex] != NULL)    /* para saber o tamanho actual */
        lastIndex++;

    Venda* newarray = (Venda*) realloc(array, (lastIndex+2) * sizeof(Venda));   /* realoca */
    if (!newarray) return array;

    Venda newElem = strdup(elem);
    if (!newElem) return newarray;

    newarray[lastIndex] = newElem;     /* inserção do novo elementodn */
    lastIndex++;
    newarray[lastIndex] = NULL;           /* coloca a marca */
    return newarray;
}

char** insere_elem_array(char** array, const char *elem) 
{
    int lastIndex = 0;
    while (array[lastIndex] != NULL)    /* para saber o tamanho actual */
        lastIndex++;

    char** newarray = (char**) realloc(array, (lastIndex+2) * sizeof(char*));   /* realoca */
    if (!newarray) return array;

    char* newElem = strdup(elem);
    if (!newElem) return newarray;

    newarray[lastIndex] = newElem;     /* inserção do novo elemento */
    lastIndex++;
    newarray[lastIndex] = NULL;           /* coloca a marca */
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

Venda regVenda(char* linhaVendaOk)  
{
    Venda vendaAux;
    vendaAux = (Venda) malloc(sizeof(struct venda));
    char** campos;
    campos = tokenizeLinhaVendaDyn(linhaVendaOk);
    vendaAux -> produto = strdup(campos[0]);
    vendaAux -> cliente = strdup(campos[3]);
    vendaAux -> preco = atof(campos[1]);
    vendaAux -> quantidade = atoi(campos[2]);
    vendaAux -> tipoCompra = campos[4];
    vendaAux -> mes = atoi(campos[5]);
    vendaAux -> filial = atoi(campos[6]);  
    free(campos);
    return vendaAux;   
}

/* Funções de comparação entre arrays para validar*/
int isInArray(char* toCheck, char** array)
{
    int i = 0;

    while (array[i] != NULL)
    {
        if (!strcmp(toCheck, array[i]))
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


/* Ler e validar ficheiro produtos, separar em 2 funções depois */
void lerProdutos(char** arrayProd)
{
    FILE *fp;
    char* produto;
    char line[6];
    int i = 0;

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
                /* Check number */
                pnumber = &line[2];
                val = isBetweenNum(atoi(pnumber), 1000, 9999);
            }
            /* Store no array */
            if (val)
            {
                produto = strdup(line);
                arrayProd = insere_elem_array(arrayProd, produto);
            }
        }
    }

    fclose(fp);
}

/* Ler e validar clientes */
void lerClientes(char** arrayCli)
{
    FILE *fp;
    char* cliente;
    char line[5];
    int i = 0;

    char* cnumber;

    int val = 1;

    if((fp = fopen("Clientes.txt", "r")) != NULL)
    {
        while (fgets(line,6,fp) != NULL)
        {

            val = (strlen(line) <= 6);

            if (val) { val = isUpperN(line, 1); }

            /* Check number */
            if (val)
            {
                cnumber = &line[1];
                val = isBetweenNum(atoi(cnumber), 1000, 5000);
            }

            /* Store no array */
            if (val)
            {
                cliente = strdup(line);
                arrayCli = insere_elem_array(arrayCli, cliente);
            }
        }
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
    int i = 0;
    /*
    char* produto;
    char* preco;
    char* quant;
    char* compra;
    char* cliente;
    char* mes;
    char* filial;
    */
    int l;

    int val = 1;

    if((fp = fopen("Vendas_1M.txt", "r")) != NULL)
    {
        while (fgets(line,31,fp) != NULL)
        {
            strcpy(linef, line);

            venda = regVenda(linef);
            
            /* Validar todos os aspetos */
            val = isBetweenNum(venda -> preco,0.0,999.99);

            if (val) { val = isBetweenNum(venda -> quantidade,1,200); }

            if (val) { val = isBetweenNum(venda -> mes,1,12); }

            if (val) { val = isBetweenNum(venda -> filial,1,3); }

            if (val) { val = isInArray(venda -> produto, arrayProd); }

            if (val) { val = isInArray(venda -> cliente, arrayCli); }

            printf("val: %d\n", val);
            
            /* Store no array */
            if (val)
                arrayVendas = insere_struct_array(arrayVendas, venda);
        }
    }

    fclose(fp);
}

/* Criar ficheiro de vebdas válidas */
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
            fprintf("%s %f %d %c %s %d %d\n",   str -> produto,
                                                str -> preco,
                                                str -> quantidade,
                                                str -> tipoCompra,
                                                str -> cliente,
                                                str -> mes,
                                                str -> filial);
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

/* Main */
int main(int argc, char const *argv[])
{
    /* Começar os arrays */
    /*
    Venda* arrayVendas = (Venda*) malloc(1 * sizeof(Venda*));
    arrayVendas[0] = NULL;
    */
    char** arrayProd = (char**) malloc(1 * sizeof(char*));
    arrayProd[0] = NULL;

    /*
    char** arrayCli = (char**) malloc(1 * sizeof(char*));
    arrayCli[0] = NULL;
    */

    /*
    char* clientes[10];
    char* vendas[10];
    Venda* arrayVendas = (Venda*) malloc(1 * sizeof(Venda));
    arrayVendas[0] = NULL;
    */

    /* Ler os ficheiros e validar para arrays */
    lerProdutos(arrayProd);
    
    /*
    lerClientes(arrayCli);
    */
    
    /*
    lerVendas(arrayVendas, arrayProd, arrayCli);
    */
    
    /* Criar ficheiro de vendas válidas */
    /*
    ficheiroVendasCertas(arrayVendas); */

    /* Libertar a memória */
    int i = 0;
    while (*(arrayProd[i]) != NULL)
    {
        free(*(arrayProd[i]));
        i++;
    }
    free(arrayProd);

    /*
    i = 0;
    while (arrayCli[i] != NULL)
    {
        free(arrayCli[i]);
        i++;
    }
    free(arrayCli);
    */

    /*
    i = 0;
    
    while (arrayVendas[i] != NULL)
    {
        free(arrayVendas[i]);
        i++;
    }
    free(arrayVendas);
    */

    return 0;
}