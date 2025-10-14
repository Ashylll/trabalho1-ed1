#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdbool.h>

typedef void* RETANGULO;

/*
    retangulo.h
    Módulo responsável pela criação de retangulos
    Inclui funções com operações relacionadas

*/

/// @brief cria um retângulo com identificador, cor de borda e de preenchimento e coordenas âncora
/// @param i identificador numérico do retângulo
/// @param x coordenada âncora do eixo x
/// @param y coordenada âncora do eixo y
/// @param w largura
/// @param h altura
/// @param corb cor da borda (string)
/// @param corp cor de preenchimento (string)
/// @return retorna ponteiro para o retângulo
RETANGULO criar_retangulo(int i, double x, double y, double w, double h, const char* corb, const char* corp);

/// @brief retorna a área do retângulo    
/// @param r retângulo
/// @return área
double area_retangulo(RETANGULO r);

/* Funções get */

/// @brief retorna o identificador do retângulo
/// @param r retangulo
/// @return identificador 'i'
int getI_retangulo(RETANGULO r);

/// @brief retorna a coordenada x do retângulo 
/// @param r retângulo  
/// @return coordenada x 
double getX_retangulo(RETANGULO r);

/// @brief retorna a coordenada y do retângulo
/// @param r retângulo   
/// @return coordenada y 
double getY_retangulo(RETANGULO r);

/// @brief retorna a largura do retângulo
/// @param r retângulo
/// @return largura 'w'
double getW_retangulo(RETANGULO r);

/// @brief retorna a altura do retângulo
/// @param r retângulo
/// @return largura 'h'
double getH_retangulo(RETANGULO r);

/// @brief retorna a cor da borda do retângulo
/// @param r retângulo
/// @return cor da borda (string)
char* getCORB_retangulo(RETANGULO r);

/// @brief retorna a cor de preenchimento do retângulo
/// @param r retângulo
/// @return cor de preenchimento (string)
char* getCORP_retangulo(RETANGULO r);

/* Funções set*/

/// @brief atribui um identificador ao retângulo
/// @param r retângulo
/// @param i identificador 'i'
/// @return true se a operação foi bem sucedida, false se não
bool setI_retangulo(RETANGULO r, int i);

/// @brief atribui uma coordenada x à âncora do retângulo
/// @param r retângulo
/// @param x coordenada x
/// @return true se a operação foi bem sucedida, false se não
bool setX_retangulo(RETANGULO r, double x);

/// @brief atribui uma coordenada y à âncora do retângulo
/// @param r retângulo
/// @param x coordenada y
/// @return true se a operação foi bem sucedida, false se não
bool setY_retangulo(RETANGULO r, double y);

/// @brief atribui uma largura ao retângulo
/// @param r retângulo
/// @param w largura 'w'
/// @return true se a operação foi bem sucedida, false se não
bool setW_retangulo(RETANGULO r, double w);

/// @brief atribui uma altura ao retângulo
/// @param r retângulo
/// @param w altura 'h'
/// @return true se a operação foi bem sucedida, false se não
bool setH_retangulo(RETANGULO r, double h);

/// @brief atribui uma cor de borda ao retângulo
/// @param r retângulo
/// @param corb cor de borda 
/// @return true se a operação foi bem sucedida, false se não
bool setCORB_retangulo(RETANGULO r, const char* corb);

/// @brief atribui uma cor de preenchimento ao retângulo
/// @param r retângulo
/// @param corb cor de preenchimento
/// @return true se a operação foi bem sucedida, false se não
bool setCORP_retangulo(RETANGULO r, const char* corp);

#endif