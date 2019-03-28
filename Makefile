CC=gcc
CFLAGS=-Wall
TARGET=main

default: $(TARGET)

main: $(TARGET).c venda.c
	gcc -Wall $(TARGET).c venda.c produto.c cliente.c filial.c `pkg-config --cflags --libs gmodule-2.0` -o $(TARGET)

exemplo: exemploVendaH.c venda.c
	gcc -Wall -o exemplo exemploVendaH.c venda.c

tree: tree.c venda.c
	gcc -Wall tree.c `pkg-config --cflags --libs gmodule-2.0` venda.c -o tree 

clean:
	rm $(TARGET)
