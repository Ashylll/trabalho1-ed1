PROJ_NAME=ted
CC=gcc

CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -Wall -Wextra
LDFLAGS= -O0

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

ted: $(OBJ)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(PROJ_NAME)
