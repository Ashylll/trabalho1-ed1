#include "pilha.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct elemento{
    void *chave;
    struct elemento *prox;   
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct stPilha{
    PONT topo;
} stPilha;

PILHA criar_pilha(void){
    stPilha *p = malloc(sizeof(stPilha));
    if (p != NULL) p->topo = NULL;

    return (PILHA)p; 
}

bool empty_pilha(PILHA p){
    if (!p) return true;
    stPilha *pilha = (stPilha*)p;

    return (pilha->topo == NULL);
}

bool push_pilha(PILHA p, void *item){
    if (!p) return false;
    
    stPilha *pilha = (stPilha*)p;
    PONT novo = malloc(sizeof(ELEMENTO));
    if (!novo) return false;
    
    novo->chave = item;
    novo->prox = pilha->topo;
    pilha->topo = novo;

    return true;
}

bool pop_pilha(PILHA p, void **out_item){
    if (!p || !out_item) return false;

    stPilha *pilha = (stPilha*)p;
    if (!pilha->topo) return false;
    
    PONT apagar = pilha->topo;
    *out_item = apagar->chave;
    pilha->topo = apagar->prox;
    free(apagar);
    
    return true;
}

bool peek_pilha(PILHA p, void **out_item){
    if (!p || !out_item) return false;

    stPilha *pilha = (stPilha*)p;
    if (!pilha->topo) return false;

    *out_item = pilha->topo->chave;

    return true;
}

void destruir_pilha(PILHA *p){
    if (!p || !*p) return;

    stPilha *pilha = (stPilha*)*p;

    PONT atual = pilha->topo;
    while (atual) {
        PONT apagar = atual;
        atual = atual->prox;
        free(apagar);
    }
    free(pilha);
    *p = NULL;
}