#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    void *chave;
    struct elemento *prox;   
} ELEMENTO;

typedef ELEMENTO *PONT;

struct pilha{
    PONT topo;
};

pilha criar_pilha(void){
    pilha p = (pilha) malloc(sizeof(struct pilha));
    if (p != NULL) p->topo = NULL;
    return p; 
}

bool empty_pilha(pilha p){
    return (p->topo == NULL);
}

bool push_pilha(pilha p, void *item){
    if (!p) return false;
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (!novo) return false;
    novo->chave = item;
    novo->prox = p->topo;
    p->topo = novo;
    return true;
}

bool pop_pilha(pilha p, void **out_item){
    if (!p || !p->topo) return false;
    PONT apagar = p->topo;
    *out_item = apagar->chave;
    p->topo = p->topo->prox;
    free(apagar);
    return true;
}
