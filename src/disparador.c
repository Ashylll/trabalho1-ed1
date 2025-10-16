#include "disparador.h"
#include "carregador.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "linha.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct stDisparador{
    int l;
    double x, y;
    CARREGADOR cesq;
    CARREGADOR cdir;
    FORMA emDisparo;
} stDisparador;

DISPARADOR criar_disparador(int l, double x, double y){
    stDisparador *disparador = malloc(sizeof(*disparador));
    if(!disparador){
    fprintf(stderr, "Erro na alocação de memória\n");
    return NULL;
    }

    disparador->l = l;
    disparador->x = x;
    disparador->y = y; 
    disparador->cesq = NULL;
    disparador->cdir = NULL;
    disparador->emDisparo = NULL;

    return disparador;
}

bool posicionar_disparador(DISPARADOR d, double x, double y){
    if(!d) return false;
    stDisparador *disparador = (stDisparador*)d;

    disparador->x = x;
    disparador->y = y;

    return true;
}

bool encaixar_cesq(DISPARADOR d, CARREGADOR cesq){
    if (!d || !cesq) return false;
    
    stDisparador *disparador = (stDisparador*)d;
    disparador->cesq = cesq;

    return true;
}

bool encaixar_cdir(DISPARADOR d, CARREGADOR cdir){
    if (!d || !cdir) return false;

    stDisparador *disparador = (stDisparador*)d;

    disparador->cdir = cdir;

    return true;
}

bool shift_disparador(DISPARADOR d, char lado, int n){
    if (!d || (lado != 'e' && lado != 'd') || n <= 0) return false;
    stDisparador *disparador = (stDisparador*)d;
    if (!disparador->cesq || !disparador->cdir) return false;
    
    int i;
    CARREGADOR origem;
    CARREGADOR destino;
    bool moveu = false;

    if (lado == 'e'){
        origem = disparador->cdir;
        destino = disparador->cesq;
    } else {
        origem = disparador->cesq;
        destino = disparador->cdir;
    }

    for(i = 0; i < n; i++){
        if(disparador->emDisparo){
            if(!push_carregador(destino, disparador->emDisparo)) break;
            disparador->emDisparo = NULL;
            moveu = true;
        }

        FORMA f = pop_carregador(origem);
        if(!f) break;
        disparador->emDisparo = f;
        moveu = true;
    }

    return  moveu;
}

bool disparo(DISPARADOR d, double dx, double dy, char modo){

}

bool rajada(DISPARADOR d, char lado, double dx, double dy, double ix, double iy){
    
}

void destruir_disparador(DISPARADOR *d){
    if (!d || !*d) return;                 
    stDisparador *disparador = (stDisparador*)*d;
    
    free(disparador);
    *d = NULL;
}

int getL_disparador(DISPARADOR d){
    assert (d != NULL);
    stDisparador *disparador = (stDisparador*)d;

    return disparador->l;
}

double getX_disparador(DISPARADOR d){
    assert (d != NULL);
    stDisparador *disparador = (stDisparador*)d;

    return disparador->x;
}

double getY_disparador(DISPARADOR d){
    assert (d != NULL);
    stDisparador *disparador = (stDisparador*)d;

    return disparador->y;
}

CARREGADOR getCesq_disparador(DISPARADOR d){
    if (!d) return NULL;
    stDisparador *disparador = (stDisparador*)d;

    return disparador->cesq;
}

CARREGADOR getCdir_disparador(DISPARADOR d){
    if (!d) return NULL;
    stDisparador *disparador = (stDisparador*)d;

    return disparador->cdir;
}

bool setX_disparador(DISPARADOR d, double x){
    if (!d) return false;

    stDisparador *disparador = (stDisparador*)d;
    disparador->x = x;

    return true;
}

bool setY_disparador(DISPARADOR d, double y){
    if (!d) return false;

    stDisparador *disparador = (stDisparador*)d;
    disparador->y = y;

    return true;
}
