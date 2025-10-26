#ifndef SVG_H
#define SVG_H

#include "forma.h"
#include "linha.h"
#include "texto.h"

#include <stdio.h>

/*
    svg.h
    Módulo responsável pelas funções que escrevem no SVG
*/

/// @brief escreve cabeçalho XML e <svg>
void svg_begin(FILE *fp);

/// @brief escreve uma forma
void svg_escrever_forma(FILE *fp, FORMA f);

/// @brief escreve um texto 
void svg_escrever_texto(FILE *fp, TEXTO t);

/// @brief escreve uma linha 
void svg_escrever_linha(FILE *fp, LINHA l);

/// @brief encerra o SVG
void svg_end(FILE *fp);

#endif