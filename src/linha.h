#ifndef LINHA_H
#define LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* LINHA;

/*
    linha.h
    Módulo responsável pela criação de linhas
    Inclui funções com operações get e set

*/


/// @brief cria uma linha com identificador e cor
/// @param i identificador 'i'
/// @param x1 coordenada x da extremidade 1 (x1)
/// @param y1 coordenada y da extremidade 1 (y1)
/// @param x2 coordenada x da extremidade 2 (x2)
/// @param y2 coordenada y da extremidade 2 (y2)
/// @param cor cor da linha
/// @return retorna ponteiro para a linha
LINHA criar_linha(int i, double x1, double y1, double x2, double y2, const char* cor);


/* Funções get */

/// @brief retorna o identificador da linha
/// @param l linha
/// @return identificador 'i'
int getI_linha(LINHA l);

/// @brief retorna a coordenada x1 da linha
/// @param l linha 
/// @return coordenada x1 
double getX1_linha(LINHA l);

/// @brief retorna a coordenada y1 da linha
/// @param l linha   
/// @return coordenada y1 
double getY1_linha(LINHA l);

/// @brief retorna a coordenada x2 da linha
/// @param l linha
/// @return coordenada x2
double getX2_linha(LINHA l);

/// @brief retorna a coordenada y2 da linha
/// @param l linha
/// @return coordenada y2
double getY2_linha(LINHA l);

/// @brief retorna a cor da linha
/// @param l linha
/// @return cor da linha (string)
char* getCOR_linha(LINHA l);

/* Funções set */

/// @brief atribui um identificador à linha
/// @param l linha
/// @param i identificador 'i'
/// @return true se a operação foi bem sucedida, false se não
bool setI_linha(LINHA l, int i);

/// @brief retorna a coordenada x1 da linha
/// @param l linha 
/// @param x1 coordenada x1
/// @return true se a operação foi bem sucedida, false se não
bool setX1_linha(LINHA l, double x1);

/// @brief retorna a coordenada y1 da linha
/// @param l linha   
/// @param y1 coordenada y1 
/// @return true se a operação foi bem sucedida, false se não 
bool setY1_linha(LINHA l, double y1);

/// @brief retorna a coordenada x2 da linha
/// @param l linha
/// @param x2 coordenada x2
/// @return true se a operação foi bem sucedida, false se não
bool setX2_linha(LINHA l, double x2);

/// @brief retorna a coordenada y2 da linha
/// @param l linha
/// @param y2 coordenada y2 
/// @return true se a operação foi bem sucedida, false se não
bool setY2_linha(LINHA l, double y2);

/// @brief retorna a cor da linha
/// @param l linha
/// @param cor cor
/// @return true se a operação foi bem sucedida, false se não
bool setCOR_linha(LINHA l, const char* cor);

#endif