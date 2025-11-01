#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

/*
    pilha.h
    Módulo responsável pela implementação de uma pilha para uso genérico mais funções com operações básicas

*/

typedef void *PILHA;

/// @brief cria uma pilha vazia
/// @return ponteiro para a pilha vazia
PILHA criar_pilha(void);

/// @brief verifica se uma pilha p está vazia
/// @param p pilha a ser checada
/// @return true se vazia; false se não || ponteiros nulos
bool empty_pilha(PILHA p);

/// @brief adiciona um item no topo da pilha
/// @param p pilha 
/// @param item item a ser adicionado
/// @return true se a operação foi bem sucedida; false se não 
bool push_pilha(PILHA p, void *item);

/// @brief remove o item no topo da pilha
/// @param p pilha 
/// @param out_item ponteiro para o item removido
/// @return true se a operação foi bem sucedida; false se não 
bool pop_pilha(PILHA p, void **out_item);

/// @brief consulta o topo da pilha
/// @param p pilha
/// @param out_item ponteiro para o item no topo da pilha
/// @return true se a operação foi bem sucedida; false se não 
bool peek_pilha(PILHA p, void **out_item);

/// @brief libera a pilha 
/// @param p pilha
void destruir_pilha(PILHA *p);

#endif







