#ifndef CARREGADOR_H
#define CARREGADOR_H

#include <stdbool.h>

typedef void* CARREGADOR;

/*
    carregador.h
    Módulo responsável pela criação e gerenciamento de carregadores

*/

/// @brief criar um carregador
/// @param c identificador
/// @return ponteiro para o carregador
CARREGADOR criar_carregador(int c);

/// @brief carrega um carregador com formas do chão
/// @param c carregador
/// @param n número de formas
/// @return true se a operação foi bem sucedida, false se não
bool load_carregador(CARREGADOR c, int n);

/// @brief apaga o carregador
/// @param c carregador
void destruir_carregador(CARREGADOR *c);

#endif