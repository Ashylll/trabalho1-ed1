#include "disparador.h"
#include "carregador.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "linha.h"
#include "forma.h"
#include "saida.h"

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
    int id_trajeto;
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
    disparador->id_trajeto = -1;

    return disparador;
}

bool posicionar_disparador(DISPARADOR d, double x, double y){
    if(!d) return false;
    stDisparador *disparador = (stDisparador*)d;

    disparador->x = x;
    disparador->y = y;

    return true;
}

CARREGADOR encaixar_cesq(DISPARADOR d, CARREGADOR cesq){
    if (!d) return NULL;
    stDisparador *disparador = (stDisparador*)d;
    
    CARREGADOR antigo = disparador->cesq;
    disparador->cesq = cesq;

    return antigo;
}

CARREGADOR encaixar_cdir(DISPARADOR d, CARREGADOR cdir){
    if (!d) return NULL;
    stDisparador *disparador = (stDisparador*)d;

    CARREGADOR antigo = disparador->cdir;
    disparador->cdir = cdir;

    return antigo;
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

bool disparo(DISPARADOR d, double dx, double dy, char modo, SAIDA saida, ARENA arena){
    if(!d || !arena) return false;
    stDisparador *disparador = (stDisparador*)d;
    if(!disparador->emDisparo) return false;

    FORMA f = disparador->emDisparo;

    double x = disparador->x;
    double y = disparador->y;

    double xi = 0.0, yi = 0.0;
    getXY_forma(f, &xi, &yi);

    setXY_forma(f, x, y);

    if(!deslocar_forma(f, dx, dy)) return false;

    if (saida){
        double xf = x + dx;
        double yf = y + dy;
        info_forma_txt(saida, f);
        info_posicoes_txt(saida, xi, yi, xf, yf);
        pula_linha(saida);
        registrar_disparo(saida);
    }
    if(modo == 'v' && saida){
        int id = gerar_id_trajeto(saida);
        LINHA trajeto = criar_linha(id, x, y, x + dx, y + dy, "violet");

        if(trajeto){
            FORMA ftrajeto = criar_forma('l', trajeto);
            add_forma_saida(saida, ftrajeto);
        }
    }

    add_arena(arena, f);
    disparador->emDisparo = NULL;

    return true;
}

bool rajada(DISPARADOR d, char lado, double dx, double dy, double ix, double iy, SAIDA saida, ARENA arena) {

    if (!d || !arena || (lado != 'e' && lado != 'd')) return false;
    stDisparador *disp = (stDisparador*)d;

    for (;;) {
        CARREGADOR origem = (lado == 'e') ? disp->cdir : disp->cesq;
        bool origem_vazia = (origem == NULL) || empty_carregador(origem);

        if (origem_vazia && !disp->emDisparo) break;

        if (!disp->emDisparo) {
            if (!shift_disparador(d, lado, 1)) return false;
            if (!disp->emDisparo) break;
        }

        if (!disparo(d, dx, dy, 'i', saida, arena)) return false;

        dx += ix;
        dy += iy;
    }

    return true;
}

void destruir_disparador(DISPARADOR *d){
    if (!d || !*d) return;                 
    stDisparador *disparador = (stDisparador*)*d;
    
    destruir_carregador(&disparador->cesq);
    destruir_carregador(&disparador->cdir);

    if (disparador->emDisparo) {
        destruir_forma(&disparador->emDisparo); 
    }
    
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

FORMA forma_em_disparo(DISPARADOR d){
    if (!d) return NULL;
    stDisparador *disp = (stDisparador*)d;
    
    return disp->emDisparo;
}
