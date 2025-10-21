#include "repo.h"
#include "fila.h"

#include <stdlib.h>

typedef struct stObjeto {
    int id;
    char tipo;
    OBJETO p;
} stObjeto;

typedef struct stRepo {
    FILA objetos;
} stRepo;

REPO criar_repo(void){
    stRepo *r = malloc(sizeof (*r));
    if(!r) return NULL;

    r->objetos = criar_fila();
    if(!r->objetos) {
        free (r);
        return NULL;
    }

    return r;
}

void destruir_repo(REPO *r){
    if (!r || !*r) return;
    stRepo *repo = (stRepo*)*r;
    void *aux;

    while (rmv_fila(repo->objetos, &aux));

    destruir_fila(&repo->objetos);
    free(repo);

    *r = NULL;
}