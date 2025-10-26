#ifndef CHAO_H
#define CHAO_H

#include "forma.h"

#include <stdbool.h>
#include <stdio.h>

/*
    chao.h
    Módulo responsável pela criação e pelo gerenciamento do chão

*/

typedef void* CHAO;

/// @brief cria o chão
/// @return ponteiro para o chão
CHAO criar_chao(void);

/// @brief libera o chão
/// @param c chão
void destruir_chao(CHAO *c);

/// @brief adiciona uma forma ao chão
/// @param c chão
/// @param f forma
/// @return true se a operação foi bem sucedida, false se houve erro
bool add_chao(CHAO c, FORMA f);

/// @brief remove uma forma do chão
/// @param c chão
/// @param out handle para a forma a ser retirada
/// @return true se a operação foi bem sucedida, false se houve erro
bool rmv_chao(CHAO c, FORMA *out);

/// @brief checa se não há formas no chão
/// @param c chão
/// @return true se estiver vazio, false se não
bool empty_chao(CHAO c);

/// @brief checa quantas formas estão no chão
/// @param c chão
/// @return número inteiro de formas
int size_chao(CHAO c);

/// @brief percorre o chão desenhando as formas 
/// @param c chão
/// @param fp arquivo SVG aberto em modo escrita 
void percorrer_chao(CHAO c, FILE *fp);




#endif