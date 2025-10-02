#ifndef PILHA_H
#define PILHA_H
#include <stdbool.h>

typedef struct pilha* pilha;

/*
    pilha.h
    Módulo responsável pela implementação de uma pilha para uso genérico mais funções com operações básicas
*/

/// @brief cria uma pilha vazia
/// @return retorna a pilha vazia
pilha criar_pilha(void);

/// @brief verifica se uma pilha p está vazia
/// @param p pilha a ser checada
/// @return true se vazia, false se não
bool empty_pilha(pilha p);

/// @brief adiciona um item no topo da pilha
/// @param p pilha p
/// @param item item a ser adicionado
/// @return true se a operação foi bem sucedida, false se não
bool push_pilha(pilha p, void *item);

/// @brief remove o item no topo da pilha
/// @param p pilha p
/// @param out_item ponteiro para o item removido
/// @return true se a operação foi bem sucedida, false se não
bool pop_pilha(pilha p, void **out_item);

#endif







