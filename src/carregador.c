#include "carregador.h"
#include "pilha.h"
#include "forma.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stCarregador{
    int c;
    PILHA formas;
} stCarregador;

CARREGADOR criar_carregador(int c){
    stCarregador *carregador = malloc(sizeof(*carregador));
    if(!carregador){
        fprintf(stderr, "Erro na alocação de memória\n");
        return NULL;
    }

    carregador->c = c;

    carregador->formas = criar_pilha();
    if(!carregador->formas){
        fprintf(stderr, "Erro na alocação de memória\n");
        free(carregador);
        return NULL;
    }
    
    return carregador;
}

bool load_carregador(CARREGADOR c, CHAO chao, int n){
    if(!c || !chao || n <= 0) return false;

    stCarregador *carregador = (stCarregador*)c;
    FORMA f = NULL;
    int i;
    for(i = 0; i < n; i++){
        if (!rmv_chao(chao, &f)) break;
        if (!push_pilha(carregador->formas, f)){
            add_chao(chao, f);
            return false;
        }
    }
    return (i == n);
}

void destruir_carregador(CARREGADOR *c){
    if(!c || !*c) return;
    stCarregador *carregador = (stCarregador*)*c;

    void *aux = NULL;
    while (pop_pilha(carregador->formas, &aux)) {
        FORMA f = (FORMA)aux;
        destruir_forma(&f);          
    }
    destruir_pilha(&carregador->formas);

    free(carregador);
    *c = NULL;

}

void* pop_carregador(CARREGADOR c){
    if (!c) return NULL;
    stCarregador *carregador = (stCarregador*)c;
    if(empty_pilha(carregador->formas)) return NULL;

    void* forma = NULL;
    if(!pop_pilha(carregador->formas, &forma)) return NULL;

    return forma;
}

bool push_carregador(CARREGADOR c, FORMA f){
    if (!c || !f) return false;
    stCarregador *carregador = (stCarregador*)c;

    if(!push_pilha(carregador->formas, f)) return false;

    return true;
}

bool peek_carregador(CARREGADOR c, FORMA *out_forma){
    if (!c || !out_forma) return false;
    stCarregador *carregador = (stCarregador*)c;
  
    if (empty_pilha(carregador->formas)) return false;

    return peek_pilha(carregador->formas, out_forma);
}

bool empty_carregador(CARREGADOR c){
    if (!c) return true;
    stCarregador *carregador = (stCarregador*)c;

    return (empty_pilha(carregador->formas));
}