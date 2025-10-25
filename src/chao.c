#include "chao.h"
#include "forma.h"
#include "fila.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct stChao{
    FILA formas;
    int n;

} stChao;

CHAO criar_chao(void){
   stChao *chao = malloc(sizeof(*chao));
   if(!chao) return NULL;
   
   chao->formas = criar_fila();
   if(!chao->formas){
    free(chao);
    return NULL;
   }

   chao->n = 0;

   return chao;
}

void destruir_chao(CHAO *c){
    if(!c || !*c) return;
    stChao *chao = (stChao*)*c;

    void *aux = NULL;
    while (rmv_fila(chao->formas, &aux)){
        FORMA f = (FORMA)aux;
        destruir_forma(&f);
    }
    
    destruir_fila(&chao->formas);
    free(chao);
    *c = NULL;
}

bool add_chao(CHAO c, FORMA f){
    if(!c || !f) return false;
    stChao *chao = (stChao*)c;
    
    if(!add_fila(chao->formas, f)) return false;

    chao->n++;

    return true;
}

bool rmv_chao(CHAO c, FORMA *out){
    if(!c || !out) return false;
    stChao *chao = (stChao*)c;

    void *aux = NULL;
    if(!rmv_fila(chao->formas, &aux)) return false;

    chao->n--;

    *out = (FORMA)aux;

    return true;
}

bool empty_chao(CHAO c){
    if (!c) return true;
    stChao *chao = (stChao*)c;

    return empty_fila(chao->formas);
}

int size_chao(CHAO c){
    if (!c) return 0;
    stChao *chao = (stChao*)c;

    return chao->n;
}