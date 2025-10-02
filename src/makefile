# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -Wall -Wextra -fstack-protector-all

# Pega automaticamente todos os .c da pasta src/
SRC = $(wildcard src/*.c)

# Converte .c em .o
OBJ = $(SRC:.c=.o)

# Nome do executável (vai ficar dentro de src/)
TARGET = src/ted

# Regra padrão (executável)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Regra para compilar cada .c em .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar (remove objetos e executável)
clean:
	rm -f src/*.o $(TARGET)
