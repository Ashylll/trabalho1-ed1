#ifndef REPO_H
#define REPO_H

#include "disparador.h"
#include "carregador.h"

#include <stdbool.h>


typedef void* REPO;

typedef void* OBJETO;


REPO criar_repo(void);


void destruir_repo(REPO *r);


bool repo_add_disparador(REPO r, int id, DISPARADOR d);


DISPARADOR repo_get_disparador(REPO r, int id);


bool repo_add_carregador(REPO r, int id, CARREGADOR c);


CARREGADOR repo_get_carregador(REPO r, int id);

#endif