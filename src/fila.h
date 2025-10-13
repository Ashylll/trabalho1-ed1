#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

typedef void *FILA;

/*
    fila.h
    Módulo responsável pela implementação de uma fila para uso genérico mais funções com operações básicas
*/


/// @brief cria uma fila vazia 
/// @return retorna a fila vazia 
FILA criar_fila(void);

/// @brief verifica se uma fila f está vazia
/// @param f fila f
/// @return true se vazia, false se não
bool empty_fila(FILA f);


/// @brief adiciona um item ao fim da fila
/// @param f fila f
/// @param item item a ser adicionado
/// @return true se a operação foi bem sucedida, false se não
bool add_fila(FILA f, void *item);

/// @brief remove um item do início da fila
/// @param f filfa f
/// @param out_item ponteiro para o item a ser retirado
/// @return true se a operação foi bem sucedida, false se não
bool rmv_fila(FILA f, void **out_item);

/// @brief consulta o início da fila
/// @param f fila f
/// @param item ponteiro para o item
/// @return true se a operação foi bem sucedida, false se não
bool peek_fila(FILA f, void **out_item);

/// @brief apaga a filha
/// @param f fila f
void destruir_fila(FILA *f); 

#endif

