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
pilha criar_pilha();

/// @brief verifica se uma pilha p está vazia
/// @param p pilha a ser checada
/// @return true se vazia, false se não
bool empty_pilha(pilha p);

/// @brief verifica se uma pilha p está cheia
/// @param p pilha a ser checada
/// @return true se cheia, false se não
bool full_pilha(pilha p);

/// @brief adiciona um item no topo da pilha
/// @param p pilha p
/// @param item item a ser adicionado
void push_pilha(pilha p, void *item);

/// @brief remove o item no topo da pilha
/// @param p pilha p
void pop_pilha(pilha p);

#endif







