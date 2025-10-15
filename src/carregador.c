#include "carregador.h"
#include "pilha.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include <stdio.h>
#include <stdlib.h>

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

bool load_carregador(CARREGADOR c, FILA chao, int n){
    if(!c || !chao || n <= 0) return false;

    stCarregador *carregador = (stCarregador*)c;
    void *f = NULL;
    int i;
    for(i = 0; i < n; i++){
        if (!rmv_fila(chao, &f)) break;
        if (!push_pilha(carregador->formas, f)){
            add_fila(chao, f);
            return false;
        }
    }
    return (i == n);
}

bool destruir_carregador(CARREGADOR *c){
    if(!c || !*c) return true;
    stCarregador *carregador = (stCarregador*)*c;
    if(!empty_pilha(carregador->formas)) return false;

    destruir_pilha(&carregador->formas);

    free(carregador);
    *c = NULL;

    return true;
}
