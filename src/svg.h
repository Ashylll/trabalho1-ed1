#ifndef SVG_H
#define SVG_H

#include "forma.h"
#include "linha.h"
#include "texto.h"

#include <stdio.h>

/*
    svg.h
    Módulo responsável pelas funções de escrita do SVG
    
*/

/// @brief escreve cabeçalho XML e <svg>
/// @param fp arquivo
void svg_begin(FILE *fp);

/// @brief escreve (desenha) uma forma
/// @param fp arquivo aberto em modo escrita
/// @param f forma
void svg_escrever_forma(FILE *fp, FORMA f);

/// @brief escreve (desenha) um texto 
/// @param fp arquivo aberto em modo escrita
/// @param t texto
void svg_escrever_texto(FILE *fp, TEXTO t);

/// @brief escreve (desenha) uma linha
/// @param fp arquivo aberto em modo escrita
/// @param l linha
void svg_escrever_linha(FILE *fp, LINHA l);

/// @brief encerra o SVG
/// @param fp arquivo aberto
void svg_end(FILE *fp);

#endif