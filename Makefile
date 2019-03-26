CC=gcc
CFLAGS=-Wall
TARGET=main

default: $(TARGET)

main: $(TARGET).c venda.c
	gcc -Wall -o $(TARGET) $(TARGET).c venda.c produto.c

exemplo: exemploVendaH.c venda.c
	gcc -Wall -o exemplo exemploVendaH.c venda.c

tree: tree.c venda.c
	gcc -Wall tree.c `pkg-config --cflags --libs gmodule-2.0` venda.c -o tree 

clean:
	rm $(TARGET)
