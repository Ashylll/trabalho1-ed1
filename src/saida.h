#ifndef SAIDA_H
#define SAIDA_H

#include "forma.h"
#include "fila.h"

#include <stdio.h>
#include <stdbool.h>

/* 
    saida.h
    Módulo responsável pelo gerenciamento de saídas
    
*/

typedef void* SAIDA;


/// @brief cria uma estrutura de saída responsável por transportar todas as formas para SVG e mensagens para TXT
/// @return handle para a estrutura de saída; NULL se falhar
SAIDA criar_saida(void);

/// @brief libera toda a memória associada à estrutura de saída
/// @param s saída
void destruir_saida(SAIDA s);

/// @brief adiciona uma forma à saída SVG
/// @param s saída
/// @param f forma
/// @return true se a operação foi bem sucedida, false se s == NULL ou erro interno
bool add_forma_saida(SAIDA s, FORMA f);

/// @brief adiciona uma mensagem de texto à saída TXT
/// @param s saída
/// @param texto texto (string)
/// @return true se a operação foi bem sucedida, false se s == NULL ou erro interno 
bool add_texto_saida(SAIDA s, const char* texto);

/// @brief gera arquivo SVG com todas as formas desenhadas
/// @param s saída
/// @param arq ponteiro para arquivo aberto
/// @return true se a operação foi bem sucedida, false se s == NULL || falha ao abrir o arquivo || erro interno 
bool gerar_svg(SAIDA s, FILE* arq);

/// @brief gera arquivo TXT com todas as mensagens escritas
/// @param s saída
/// @param arq ponteira para arquivo aberto
/// @return true se a operação foi bem sucedida, false se s == NULL || falha ao abrir o arquivo || erro interno 
bool gerar_txt(SAIDA s, FILE* arq);

#endif