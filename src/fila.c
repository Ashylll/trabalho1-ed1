#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct elemento{
    void *chave;
    struct elemento *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct stFila {
    PONT inicio;
    PONT fim;
} stFila;

FILA criar_fila (void){
    stFila *f = malloc(sizeof(stFila));
    if (!f){
        fprintf(stderr, "Erro na alocação de memória");
        exit(1);
    }

    f->inicio = NULL;
    f->fim = NULL;

    return (FILA)f;
}

bool empty_fila(FILA f){
    if (!f) return true;

    stFila *fila = (stFila*)f;
    return (fila->inicio == NULL);

    return false;
}

bool add_fila(FILA f, void *item){
    if (!f) return false;

    stFila *fila = (stFila*)f;
    PONT novo = malloc(sizeof(ELEMENTO));
    if(!novo) return false;
   
    novo->chave = item;
    novo->prox = NULL;

    if (fila->inicio == NULL){
        fila->inicio = novo;
    } else {
        fila->fim->prox = novo;
    }

    fila->fim = novo;
    
    return true;
}

bool rmv_fila(FILA f, void **item){
    if (!f) return false;
    
    stFila *fila = (stFila*)f;
    if (fila->inicio == NULL) return false;

    PONT apagar = fila->inicio;
    *item = apagar->chave;
    fila->inicio = apagar->prox;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(apagar);

    return true;
}

bool peek_fila(FILA f, void **out_item){
    if (!f || !out_item) return false;

    stFila *fila = (stFila*)f;
    if(fila->inicio == NULL) return false;

    *out_item = fila->inicio->chave;

    return true;
}

void destruir_fila(FILA *f){
    if (!f || !*f) return;

    stFila *fila = (stFila*)*f;

    PONT atual = fila->inicio;
    while(atual){
        PONT apagar = atual;
        atual = atual->prox;
        free(apagar);
    } 
    free(fila);
    *f = NULL;
}