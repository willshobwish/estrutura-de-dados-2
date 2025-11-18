# Makefile para Projeto de Grafos de Pré-Requisitos

CC = gcc
CFLAGS = -Wall -Wextra -g

# Diretórios
DIR_MATRICE = ../matrice
DIR_LIST = ../list

# Arquivos comuns
COMUM_SRC = requisitos_comum.c
COMUM_OBJ = requisitos_comum.o

# Programas finais
PROG_MATRICE = requisitos_matriz
PROG_LIST = requisitos_lista

# Regra padrão - compila ambos
all: $(PROG_MATRICE) $(PROG_LIST)

# Compila arquivo comum
$(COMUM_OBJ): $(COMUM_SRC) requisitos_comum.h
	$(CC) $(CFLAGS) -c $(COMUM_SRC) -o $(COMUM_OBJ)

# Compila implementação com matriz
$(PROG_MATRICE): requisitos_matriz.c $(COMUM_OBJ) $(DIR_MATRICE)/graph.c $(DIR_MATRICE)/graph.h
	$(CC) $(CFLAGS) requisitos_matriz.c $(COMUM_OBJ) $(DIR_MATRICE)/graph.c -o $(PROG_MATRICE)

# Compila implementação com lista
$(PROG_LIST): requisitos_lista.c $(COMUM_OBJ) $(DIR_LIST)/graph.c $(DIR_LIST)/graph.h
	$(CC) $(CFLAGS) requisitos_lista.c $(COMUM_OBJ) $(DIR_LIST)/graph.c -o $(PROG_LIST)

# Executa programa com matriz
run-matriz: $(PROG_MATRICE)
	./$(PROG_MATRICE)

# Executa programa com lista
run-lista: $(PROG_LIST)
	./$(PROG_LIST)

# Executa ambos
run-all: run-matriz run-lista

# Limpeza
clean:
	rm -f $(COMUM_OBJ) $(PROG_MATRICE) $(PROG_LIST) $(PROG_MATRICE).exe $(PROG_LIST).exe

.PHONY: all clean run-matriz run-lista run-all
