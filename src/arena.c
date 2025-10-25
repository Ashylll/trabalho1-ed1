#include "arena.h"
#include <stdlib.h>

typedef struct stArena {
    FILA formas;
} stArena;

ARENA criar_arena(void){
    stArena *arena = malloc(sizeof (*arena));
    if (!arena) return NULL;

    arena->formas = criar_fila();
    
    return arena;
}

void destruir_arena(ARENA *a){
    if (!a || !*a) return;
    stArena *arena = (stArena*)*a;

    destruir_fila(&arena->formas);
    free(arena);
    *a = NULL;
}

bool add_arena(ARENA a, FORMA f){
    if (!a || !f) return false;
    stArena *arena = (stArena*)a;

    return add_fila(arena->formas, f);
}

FORMA rmv_arena(ARENA a){
    if (!a) return NULL;
    stArena *arena = (stArena*)a;

    void *aux = NULL;
    if (!rmv_fila(arena->formas, &aux)) return NULL;

    return (FORMA)aux;
}

bool empty_arena(ARENA a){
    if (!a) return true;
    stArena *arena = (stArena*)a;

    return empty_fila(arena->formas);
}
