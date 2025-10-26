#ifndef SAIDA_H
#define SAIDA_H

#include "forma.h"
#include "chao.h"

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
/// @param s ponteiro para o handle de saída
void destruir_saida(SAIDA *s);

/// @brief adiciona uma forma à saída SVG
/// @param s saída
/// @param f forma
/// @return true se a operação foi bem sucedida, false se s == NULL ou erro interno
bool add_forma_saida(SAIDA s, FORMA f);

/// @brief adiciona uma mensagem de texto à saída TXT (copia a string internamente)
/// @param s saída
/// @param texto texto (string)
/// @return true se a operação foi bem sucedida, false se s == NULL ou erro interno 
bool add_texto_saida(SAIDA s, const char* texto);

/// @brief gera arquivo SVG com todas as formas desenhadas
/// @param s saída
/// @param arq ponteiro para arquivo aberto
/// @return true se a operação foi bem sucedida, false se s == NULL || falha ao abrir o arquivo || erro interno 
bool gerar_svg(SAIDA s, CHAO chao, FILE *fp);

/// @brief gera arquivo TXT com todas as mensagens escritas
/// @param s saída
/// @param arq ponteira para arquivo aberto
/// @return true se a operação foi bem sucedida, false se s == NULL || falha ao abrir o arquivo || erro interno 
bool gerar_txt(SAIDA s, FILE *fp);

/// @brief gera um id negativo e único (decrementa a cada chamada) para a linha que representa a trajetória
/// @param s saída
/// @return id negativo 
int gerar_id_trajeto(SAIDA s);

/// soma área na pontuação total
void somar_pontuacao(SAIDA s, double area);

/// Incrementam o contador de formas esmagadas, número de instruções, de disparos e de formas clonadas.
void registrar_esmagada(SAIDA s);
void registrar_instrucao(SAIDA s);
void registrar_disparo(SAIDA s);
void registrar_clone(SAIDA s);

/// Retornam os valores registrados (pontuação, número de instruções, de disparos, de esmagadas e de clonagens)
double get_pontuacao(SAIDA s);
int get_instrucoes(SAIDA s);
int get_disparos(SAIDA s);
int get_esmagadas(SAIDA s);
int get_clones(SAIDA s);

/// Coloca uma marca visual (asterisco vermelho) no local da forma esmagada
void marcar_esmagada(SAIDA s, FORMA esmagada);

/// Escreve no arquivo aberto todas as informações da forma 
void info_forma_txt(SAIDA s, FORMA f);

/// Escreve no arquivo aberto as posições inicial e final da forma deslocada por um comando
void info_posicoes_txt(SAIDA s, double xi, double yi, double xf, double yf);

/// Pula uma linha no arquivo aberto
void pula_linha(SAIDA s);

#endif