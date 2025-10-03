#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* TEXTO;

/*
    texto.h
    Módulo responsável pela criação de textos
    Inclui funções com operações get e set

*/



/// @brief cria um texto com identificador, coordenadas e cores de borda e de preenchimento 
/// @param i identificador 'i'
/// @param x coordenada x
/// @param y coordenada y
/// @param corb cor da borda (string)
/// @param corp cor de preenchimento (string)
/// @param a posição da âncora no texto: i(início), m(meio), f(fim)
/// @param txto conteúdo do texto a ser criado
/// @return ponteiro para o texto criado
TEXTO criar_texto(int i, float x, float y, const char* corb, const char* corp, char a, const char* txto);

