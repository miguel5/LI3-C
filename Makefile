CC=gcc
CFLAGS=-Wall
TARGET=main

default: $(TARGET)

main: $(TARGET).c venda.h produto.h cliente.h filial.h CatProd.h CatCli.h facturacao.h navegacao.h queries.h
	gcc -Wall $(TARGET).c venda.c produto.c cliente.c filial.c CatProd.c CatCli.c facturacao.c navegacao.c queries.c `pkg-config --cflags --libs gmodule-2.0` -o $(TARGET)

tree: tree.c venda.c
	gcc -Wall tree.c `pkg-config --cflags --libs gmodule-2.0` venda.c -o tree 

clean:
	rm $(TARGET)
