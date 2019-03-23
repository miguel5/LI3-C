CC=gcc
CFLAGS=-Wall
TARGET=main

default: $(TARGET)

main: $(TARGET).c venda.c
	gcc -Wall -o $(TARGET) $(TARGET).c venda.c

exemplo: exemploVendaH.c venda.c
	gcc -Wall -o exemplo exemploVendaH.c venda.c

main_teste: main_teste.c venda.c
	gcc -Wall -o main_teste main_teste.c venda.c

clean:
	rm $(TARGET)
