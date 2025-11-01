#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "carregador.h"
#include "forma.h"
#include "saida.h"
#include "arena.h"

#include <stdbool.h>

/*
    disparador.h
    Módulo responsável pela criação e gerenciamento de disparadores

*/

typedef void* DISPARADOR;

/// @brief cria e posiciona um disparador no plano
/// @param l identificador para o disparador
/// @param x coordenada x do disparador 
/// @param y coordenada y do disparador
/// @return ponteiro para o disparador
DISPARADOR criar_disparador(int l, double x, double y);

/// @brief posiciona um disparador no plano
/// @param d disparador
/// @param x coordenada x do disparador
/// @param y coordenada y do disparador
/// @return true se a operação foi bem sucedida; false se não
bool posicionar_disparador(DISPARADOR d, double x, double y);

/// @brief encaixa no disparador o carregador esquerdo
/// @param d disparador
/// @param cesq carregador esquerdo
/// @return carregador antigo; NULL se não existia
CARREGADOR encaixar_cesq(DISPARADOR d, CARREGADOR cesq);

/// @brief encaixa no disparador o carregador direito
/// @param d disparador
/// @param cdir carregador direito
/// @return carregador antigo; NULL se não existia
CARREGADOR encaixar_cdir(DISPARADOR d, CARREGADOR cdir);

/// @brief pressiona o botão esquerdo ou direito do disparador n vezes
/// @param d disparador
/// @param lado botão a ser pressionado ('e' = esquerdo, 'd' = direito)
/// @param n número de vezes que o botão deve ser pressionado
/// @return true se a operação foi bem sucedida; false se não
bool shift_disparador(DISPARADOR d, char lado, int n);

/// @brief dispara uma forma e escreve o log do comando 'dsp' na saída
/// @param d disparador 
/// @param dx deslocamento da forma na coordenada x
/// @param dy deslocamento da forma na coordenada y
/// @param modo 'v' (visualizar) para traçar a linha da trajetória da forma, 'i' (ignorar) para ignorar o trajeto. Se ausente, trata como 'i'
/// @param saida caso modo == 'v', a função gera a linha da trajetória e passa para um ponteiro 'saida' de saída
/// @param arena arena para guardar cada forma lançada
/// @return true se a operação foi bem sucedida; false se não
bool disparo(DISPARADOR d, double dx, double dy, char modo, SAIDA saida, ARENA arena);

/// @brief dispara em rajada várias formas e escreve o log do comando 'rjd' na saída
/// @param d disparador
/// @param lado qual carregador (esquerdo|direito) será utilizado
/// @param dx deslocamento da forma na coordenada x
/// @param dy deslocamento da forma na coordenada y
/// @param ix incremento ao deslocamento a cada disparo na coordenada x
/// @param iy incremento ao deslocamento a cada disparo na coordenada y
/// @param arena arena para guardar cada forma lançada
/// @return true se a operação foi bem sucedida; false se não
bool rajada(DISPARADOR d, char lado, double dx, double dy, double ix, double iy, SAIDA saida, ARENA arena);

/// @brief libera o disparador
/// @param d disparador
void destruir_disparador(DISPARADOR *d);

/* === Operações get === */

/// @brief retorna o identificador do disparador
/// @param d disparador
/// @pre d != NULL
/// @return identificador
int getL_disparador(DISPARADOR d);

/// @brief retorna a coordenada x do disparador
/// @param d disparador
/// @pre d != NULL
/// @return coordenada x
double getX_disparador(DISPARADOR d);

/// @brief retorna a coordenada y do disparador
/// @param d disparador
/// @pre d != NULL
/// @return coordenada y
double getY_disparador(DISPARADOR d);

/// @brief retorna o carregador esquerdo do disparador
/// @param d disparador
/// @return carregador esquerdo
CARREGADOR getCesq_disparador(DISPARADOR d);

/// @brief retorna o carregador direito do disparador
/// @param d disparador
/// @return carregador direito
CARREGADOR getCdir_disparador(DISPARADOR d);

/* ===================== */


/* === Operações set === */

/// @brief atribui uma coordenada ao disparador   
/// @param d disparador
/// @param x coordenada x
/// @return true se a operação foi bem sucedida; false se não
bool setX_disparador(DISPARADOR d, double x);

/// @brief atribui uma coordenada ao disparador   
/// @param d disparador
/// @param y coordenada y
/// @return true se a operação foi bem sucedida; false se não
bool setY_disparador(DISPARADOR d, double y);

/* ===================== */


/// @brief retorna a forma no em posição de disparo
/// @param d disparador
/// @return forma em posição de disparo ou NULL se vazio/inválido
FORMA forma_em_disparo(DISPARADOR d);

#endif