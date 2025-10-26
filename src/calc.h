#ifndef CALC_H
#define CALC_H

#include "chao.h"
#include "arena.h"
#include "saida.h"
#include <stdbool.h>

/*
    cal.h
    Módulo responsável pelo processamento das figuras na arena
    
*/

/// @brief Processa as formas lançadas na areana, aplicando as regras do projeto
/// @param chao chão a ser atualizado (formas que voltam após o cálculo)
/// @param arena fila de formas lançadas (consumida pelo cálculo)
/// @param saida saída para registrar textos/trajetos conforme necessário
/// @return true se processou sem erros; false caso contrário
bool calc(CHAO chao, ARENA arena, SAIDA saida);

#endif
