#ifndef ARENA_H
#define ARENA_H

#include "fila.h"
#include "forma.h"

#include <stdbool.h>

/*
    arena.h
    Módulo responsável pela criação e pelo gerenciamento da arena

*/

typedef void* ARENA;

/// @brief cria a arena
/// @return ponteiro para a arena
ARENA criar_arena(void);

/// @brief libera a arena
/// @param a arena
void destruir_arena(ARENA *a);

/// @brief adiciona uma forma à arena
/// @param a arena
/// @param f forma
/// @return true se a operação foi bem sucedida; false se houve erro
bool add_arena(ARENA a, FORMA f);

/// @brief remove uma forma da arena em ordem de disparo
/// @param a arena
/// @return forma removida; NULL se vazio ou inválido
FORMA rmv_arena(ARENA a);

/// @brief checa se não há formas na arena
/// @param a arena
/// @return true se estiver vazia; false se não
bool empty_arena(ARENA a);

#endif
