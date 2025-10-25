#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "chao.h"
#include "forma.h"
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
/// @param chao chão
/// @param n número de formas
/// @return true se a operação foi bem sucedida, false se não
bool load_carregador(CARREGADOR c, CHAO chao, int n);

/// @brief libera o carregador
/// @param c carregador
void destruir_carregador(CARREGADOR *c);

/// @brief retira uma forma do carregador
/// @param c carregador
/// @return ponteiro para a forma retirada; NULL se vazio ou inválido
void* pop_carregador(CARREGADOR c);

/// @brief acrescenta uma forma ao topo do carregador
/// @param c carregador
/// @param forma ponteiro para a forma
/// @return true se empilhou com sucesso, false se inválido ou erro de alocação
bool push_carregador(CARREGADOR c, FORMA f);

/// @brief retorna a forma no topo do carregador
/// @param c carregador
/// @param out_forma ponteiro de saída para a forma
/// @return true se a operação foi bem sucedida, false se c == NULL || out_forma == NULL || falha na alocação
bool peek_carregador(CARREGADOR c, FORMA *out_forma);

/// @brief checa se o carregador está vazio
/// @param c carregador
/// @return true se estiver vazio, false se não
bool empty_carregador(CARREGADOR c);

#endif