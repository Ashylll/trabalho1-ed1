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
    stFila *fila = malloc(sizeof(*fila));
    if (!fila){
        fprintf(stderr, "Erro na alocação de memória\n");
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

bool empty_fila(FILA f){
    if (!f) return true;

    stFila *fila = (stFila*)f;
    return (fila->inicio == NULL);

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

bool rmv_fila(FILA f, void **out_item){
    if (!f || !out_item) return false;
    
    stFila *fila = (stFila*)f;
    if (fila->inicio == NULL) return false;

    PONT apagar = fila->inicio;
    *out_item = apagar->chave;
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

int tamanho_fila(FILA f){
    if (!f || empty_fila(f)) return 0;

    void *inicio = NULL; 
    if (!peek_fila(f, &inicio)) return 0;
    int n = 0;
    void *aux = NULL;

    for (;;) {
        rmv_fila(f, &aux);
        add_fila(f, aux);
        n++;

        void *primeiro = NULL; 
        peek_fila(f, &primeiro);
        if (primeiro == inicio) break;
    }

    return n;
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