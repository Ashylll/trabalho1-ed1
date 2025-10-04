#ifndef TEXTO_H
#define TEXTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* TEXTO;

/*
    texto.h
    Módulo responsável pela criação e estilização de textos
    Inclui funções com operações get e set

*/



/// @brief cria um texto com identificador, coordenadas, cores de borda e de preenchimento e estilo padrão 
/// @param i identificador 'i'
/// @param x coordenada x
/// @param y coordenada y
/// @param corb cor da borda (string)
/// @param corp cor de preenchimento (string)
/// @param a posição da âncora no texto: i(início), m(meio), f(fim)
/// @param txto conteúdo do texto a ser criado
/// @return ponteiro para o texto criado
TEXTO criar_texto(int i, double x, double y, const char* corb, const char* corp, char a, const char* txto);

// Funções get 


/// @brief retorna o identificador do texto
/// @param t texto 't'
/// @return identificador 'i'
int getI_texto(TEXTO t);


/// @brief retorna a coordenada x do texto
/// @param t texto 't'
/// @return coordenada x
double getX_texto(TEXTO t);

/// @brief retorna a coordenada y do texto
/// @param t texto 't'
/// @return coordenada y
double getY_texto(TEXTO t);

/// @brief retorna a cor da borda do texto
/// @param t texto 't'
/// @return cor da borda (string) 
char* getCORB_texto(TEXTO t);

/// @brief retorna a cor de preenchimento do texto
/// @param t texto 't'
/// @return cor de preenchimento (string) 
char* getCORP_texto(TEXTO t);

/// @brief retorna a posição da âncora do texto
/// @param t texto 't'
/// @return posição da âncora (char i, m, f)
char getA_texto(TEXTO t);

/// @brief retorna o conteúdo do texto
/// @param t texto 't'
/// @return texto 'txto' (string) 
char* getTXTO_texto(TEXTO t);

// Funções set 

/// @brief atribui um identificador ao texto
/// @param t texto 't'
/// @param i identificador 'i'
/// @return true se a operação foi bem sucedida, false se não
bool setI_texto(TEXTO t, int i);

/// @brief atribui uma coordenada x ao texto
/// @param t texto 't'
/// @param x
/// @return true se a operação foi bem sucedida, false se não
bool setX_texto(TEXTO t, double x);

/// @brief atribui uma coordenada y ao texto
/// @param t texto 't'
/// @param y coordenada y
/// @return true se a operação foi bem sucedida, false se não
bool setY_texto(TEXTO t, double y);

/// @brief atribui uma cor de borda ao texto
/// @param t texto 't'
/// @param corb cor de borda
/// @return true se a operação foi bem sucedida, false se não
bool setCORB_texto(TEXTO t, char* corb);

/// @brief atribui uma cor de preenchimento ao texto
/// @param t texto 't'
/// @param corp cor de preenchimento
/// @return true se a operação foi bem sucedida, false se não
bool setCORP_texto(TEXTO t, char* corp);

/// @brief atribui uma posição à âncora do texto
/// @param t texto 't'
/// @param a âncora do texto
/// @return true se a operação foi bem sucedida, false se não
bool setA_texto(TEXTO t, char a);

/// @brief atribui um conteúdo ao texto
/// @param t texto 't'
/// @param txto conteúdo do texto (string)
/// @return true se a operação foi bem sucedida, false se não
bool setTXTO_texto(TEXTO t, char* txto);


// Função estilo

/// @brief muda o estilo de um texto
/// @param t texto t
/// @param fFamily família do estilo (sans, serif, cursive)
/// @param fWeight peso do estilo (n: normal, b: bold, b+: bolder, l: lighter)
/// @param fSize tamanho do estilo
/// @return true se a operação foi bem sucedida, false se não
bool mudar_estilo(TEXTO t, char* fFamily, char fWeight, int fSize);



#endif