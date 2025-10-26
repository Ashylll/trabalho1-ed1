PROJ_NAME=ted
ALUNO=
LIBS=-lm
OBJETOS= \
  main.o \
  leitura.o repo.o chao.o saida.o svg.o \
  calc.o forma.o circulo.o retangulo.o linha.o texto.o \
  arena.o carregador.o disparador.o pilha.o fila.o

CC=gcc

CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -Wall -Wextra
LDFLAGS= -O0

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c leitura.h repo.h chao.h saida.h svg.h

leitura.o: leitura.c leitura.h saida.h chao.h disparador.h forma.h circulo.h retangulo.h texto.h linha.h repo.h arena.h calc.h
repo.o:    repo.c    repo.h    disparador.h carregador.h fila.h

chao.o:   chao.c   chao.h   fila.h forma.h
saida.o:  saida.c  saida.h  circulo.h retangulo.h linha.h texto.h forma.h fila.h svg.h chao.h
svg.o:    svg.c    svg.h    forma.h linha.h texto.h circulo.h retangulo.h

calc.o:      calc.c      calc.h      forma.h saida.h chao.h arena.h
forma.o:     forma.c     forma.h     retangulo.h circulo.h texto.h linha.h
circulo.o:   circulo.c   circulo.h
retangulo.o: retangulo.c retangulo.h
linha.o:     linha.c     linha.h
texto.o:     texto.c     texto.h

arena.o:       arena.c       arena.h       fila.h forma.h
carregador.o:  carregador.c  carregador.h  pilha.h forma.h
disparador.o:  disparador.c  disparador.h  carregador.h forma.h saida.h arena.h
pilha.o:       pilha.c       pilha.h
fila.o:        fila.c        fila.h


.PHONY: clean run memcheck

clean:
	rm -f $(OBJETOS) $(PROJ_NAME)

run: $(PROJ_NAME)
	./$(PROJ_NAME)

memcheck: $(PROJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROJ_NAME)
