#ifndef CIRCULO_H
#define CIRCULO_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* CIRCULO;

/*
    circulo.h
    Módulo responsável pela criação de círculos
    Inclui funções com operações get e set

*/

/// @brief cria um circulo com identificador, cor de borda e de preenchimento e coordenas
/// @param i identificador numérico do círculo
/// @param x coordenada do eixo x
/// @param y coordenada do eixo y
/// @param r raio
/// @param corb cor da borda (string)
/// @param corp cor de preenchimento (string)
/// @return retorna ponteiro para o círculo
CIRCULO criar_circulo(int i, double x, double y, double r, const char* corb, const char* corp);


/* Funções get */

/// @brief retorna o identificador do círculo
/// @param c círculo
/// @return identificador 'i'
int getI_circulo(CIRCULO c);

/// @brief retorna a coordenada x do círculo 
/// @param c círculo    
/// @return coordenada x 
double getX_circulo(CIRCULO c);

/// @brief retorna a coordenada y do círculo 
/// @param c círculo    
/// @return coordenada y 
double getY_circulo(CIRCULO c);

/// @brief retorna o raio do círculo 
/// @param c círculo    
/// @return raio 'r'
double getR_circulo(CIRCULO c);

/// @brief retorna a cor da borda do círculo
/// @param c círculo
/// @return cor da borda (string)
char* getCORB_circulo(CIRCULO c);

/// @brief retorna a cor de preenchimento do círculo
/// @param c círculo
/// @return cor de preenchimento (string)
char* getCORP_circulo(CIRCULO c);

/* Funções set */

/// @brief atribui um identificador ao círculo
/// @param c círculo
/// @param i identificador 'i'
/// @return true se a operação foi bem sucedida, false se não
bool setI_circulo(CIRCULO c, int i);

/// @brief atribui uma coordenada x ao círculo
/// @param c círculo
/// @param x coordenada x
/// @return true se a operação foi bem sucedida, false se não
bool setX_circulo(CIRCULO c, double x);

/// @brief atribui uma coordenada y ao círculo
/// @param c círculo
/// @param x coordenada y
/// @return true se a operação foi bem sucedida, false se não
bool setY_circulo(CIRCULO c, double y);

/// @brief atribui um raio ao círculo
/// @param c círculo
/// @param r raio 'r'
/// @return true se a operação foi bem sucedida, false se não
bool setR_circulo(CIRCULO c, double r);

/// @brief atribui uma cor de borda ao círculo
/// @param c círculo
/// @param corb cor de borda 
/// @return true se a operação foi bem sucedida, false se não
bool setCORB_circulo(CIRCULO c, const char* corb);

/// @brief atribui uma cor de preenchimento ao círculo
/// @param c círculo
/// @param corb cor de preenchimento
/// @return true se a operação foi bem sucedida, false se não
bool setCORP_circulo(CIRCULO c, const char* corp);

#endif
