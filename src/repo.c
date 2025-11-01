#include "repo.h"
#include "fila.h"
#include "disparador.h"
#include "carregador.h"

#include <stdlib.h>
#include <stdbool.h>

typedef void* OBJETO;

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
    void *aux = NULL;

    while (rmv_fila(repo->objetos, &aux)){
        stObjeto *obj = (stObjeto*)aux;
        if (!obj) continue;

        switch (obj->tipo){
            case 'd': {
                if (obj->p){
                    DISPARADOR d = (DISPARADOR)obj->p;
                    destruir_disparador(&d);  
                    obj->p = NULL;
                }
            } break;

            case 'c': {
                if (obj->p){
                    CARREGADOR c = (CARREGADOR)obj->p;
                    destruir_carregador(&c);  
                    obj->p = NULL;
                }
            } break;

            default:
    
                break;
        }
        free(obj);
    }

    destruir_fila(&repo->objetos);
    free(repo);
    *r = NULL;
}


DISPARADOR repo_get_disparador(REPO r, int id){
    if (!r) return NULL;
    stRepo *repo = (stRepo*)r;
    if (empty_fila(repo->objetos)) return NULL;

    void *inicio = NULL;
    if (!peek_fila(repo->objetos, &inicio)) return NULL;

    DISPARADOR achou = NULL;
    void *temp = NULL;

    for (;;) {
        if (!rmv_fila(repo->objetos, &temp)) break;

        stObjeto *obj = (stObjeto*)temp;
        if (!achou && obj && obj->tipo == 'd' && obj->id == id) {
            achou = (DISPARADOR)obj->p;
        }

        add_fila(repo->objetos, temp);

        void *primeiro = NULL;
        if (!peek_fila(repo->objetos, &primeiro)) break;
        if (primeiro == inicio) break;
    }

    return achou;
}

bool repo_add_disparador(REPO r, int id, DISPARADOR d){
    if (!r || !d) return false;

    if (repo_get_disparador(r, id) != NULL) return false;

    stRepo *repo = (stRepo*)r;

    stObjeto *novo = (stObjeto*)malloc(sizeof *novo);
    if (!novo) return false;

    novo->id = id;
    novo->tipo = 'd';
    novo->p = d;

    if (!add_fila(repo->objetos, novo)) {
        free(novo);
        return false;
    }
    return true;
}

DISPARADOR repo_assegurar_disparador(REPO r, int id, double x, double y){
    DISPARADOR d = repo_get_disparador(r, id);
    if (d) return d;

    d = criar_disparador(id, x, y);
    if (!d) return NULL;

    if (!repo_add_disparador(r, id, d)){
        destruir_disparador(&d);
        return NULL;
    }

    return d;
}

CARREGADOR repo_get_carregador(REPO r, int id){
    if (!r) return NULL;
    stRepo *repo = (stRepo*)r;
    if (empty_fila(repo->objetos)) return NULL;

    void *inicio = NULL;
    if (!peek_fila(repo->objetos, &inicio)) return NULL;

    CARREGADOR achou = NULL;
    void *aux = NULL;

    for (;;) {
        if (!rmv_fila(repo->objetos, &aux)) break;

        stObjeto *obj = (stObjeto*)aux;
        if (!achou && obj && obj->tipo == 'c' && obj->id == id) {
            achou = (CARREGADOR)obj->p;
        }

        add_fila(repo->objetos, aux);

        void *primeiro = NULL;
        if (!peek_fila(repo->objetos, &primeiro)) break;
        if (primeiro == inicio) break;
    }

    return achou;
}

bool repo_add_carregador(REPO r, int id, CARREGADOR c){
    if (!r || !c) return false;
    if (repo_get_carregador(r, id) != NULL) return false;

    stRepo *repo = (stRepo*)r;

    stObjeto *novo = (stObjeto*)malloc(sizeof *novo);
    if (!novo) return false;

    novo->id = id;
    novo->tipo = 'c';
    novo->p = c;

    if (!add_fila(repo->objetos, novo)) {
        free(novo);
        return false;
    }

    return true;
}

CARREGADOR repo_take_carregador(REPO r, int id){
    if (!r) return NULL;
    stRepo *repo = (stRepo*)r;

    int n = tamanho_fila(repo->objetos);
    CARREGADOR achou = NULL;

    for (int i = 0; i < n; i++){
        void *aux = NULL;
        if (!rmv_fila(repo->objetos, &aux)) break;

        stObjeto *obj = (stObjeto*)aux;
        if (!achou && obj && obj->tipo == 'c' && obj->id == id){
            achou = (CARREGADOR)obj->p; 
            free(obj);                  
    
        } else {
            add_fila(repo->objetos, aux); 
        }
    }
    return achou; 
}

CARREGADOR repo_assegurar_carregador(REPO r, int id){
    if (!r) return NULL;

    CARREGADOR c = repo_get_carregador(r, id);
    if (c) return c;                            

    c = criar_carregador(id);
    if (!c) return NULL;

    if (!repo_add_carregador(r, id, c)){
        destruir_carregador(&c);
        return NULL;
    }
    return c;
}