#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

typedef void *FILA;

/*
    pilha.h
    Módulo responsável pela implementação de uma fila para uso genérico mais funções com operações básicas
*/


/// @brief cria uma fila vazia 
/// @return retorna a fila vazia 
FILA criar_fila(void);

/// @brief verifica se uma fila f está vazia
/// @param f fila f
/// @return true se vazia, false se não
bool empty_pilha(FILA f);


/// @brief adiciona um item ao fim da fila
/// @param f fila f
/// @param item item a ser adicionado
/// @return true se a operação foi bem sucedida, false se não
bool add_pilha(FILA f, void *item);

/// @brief remove um item do início da fila
/// @param f filfa f
/// @param out_item ponteiro para o item a ser retirado
/// @return true se a operação foi bem sucedida, false se não
bool rmv_pilha(FILA f, void **out_item);

#endif

