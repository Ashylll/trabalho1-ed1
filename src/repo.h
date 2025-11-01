#ifndef REPO_H
#define REPO_H

#include "disparador.h"
#include "carregador.h"

#include <stdbool.h>

/* 
    repo.h
    Módulo responsável pelo repositório de disparadores e carregadores
    
*/

typedef void* REPO;

// Cria repositório para disparadores e carregadores
REPO criar_repo(void);

// Libera o repositório
void destruir_repo(REPO *r);

// Retorna um disparador presente no repositório a partir de seu id
DISPARADOR repo_get_disparador(REPO r, int id);

// Adiciona um disparador ao repositório
bool repo_add_disparador(REPO r, int id, DISPARADOR d);

// Retorna um disparador presente no repositório a partir de seu id. Se não existe, o cria e o retorna
DISPARADOR repo_assegurar_disparador(REPO r, int id, double x, double y);

// Retorna um carregador presente no repositório a partir de seu id
CARREGADOR repo_get_carregador(REPO r, int id);

// Adiciona um carregador ao repositório
bool repo_add_carregador(REPO r, int id, CARREGADOR c);

// Desvincula o carregador do repositório para a posterior transferência de "ownership" para um disparador
CARREGADOR repo_take_carregador(REPO r, int id);

// Retorna um carregador presente no repositório a partir de seu id. Se não existe, o cria e o retorna
CARREGADOR repo_assegurar_carregador(REPO r, int id);

#endif