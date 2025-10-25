#include "saida.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct stSaida {
    FILA formas;
    FILA textos;
    int cont_id_trajeto;
} stSaida;

SAIDA criar_saida(void){
    stSaida *saida = malloc(sizeof *saida);
    if(!saida) return NULL;

    saida->formas = criar_fila();
    if (!saida->formas){
        free(saida);
        return NULL;
    }

    saida->textos = criar_fila();
    if(!saida->textos){
        destruir_fila(&saida->formas);
        free(saida);
        return NULL;
    }
    saida->cont_id_trajeto = -1;

    return saida;
}

void destruir_saida(SAIDA *s){
    if (!s || !*s) return;
    stSaida *saida = (stSaida*)*s;
    void *aux;

    while (rmv_fila(saida->formas, &aux)) {
        FORMA f = (FORMA)aux;
        if (getI_forma(f) < 0) destruir_forma(&f);
    }
    destruir_fila(&saida->formas);

    while (rmv_fila(saida->textos, &aux)) {
        free(aux);
    }
    destruir_fila(&saida->textos);

    free(saida);
    *s = NULL;
}

bool add_forma_saida(SAIDA s, FORMA f){
    if (!s || !f) return false;

    stSaida *saida = (stSaida*)s;

    if(!add_fila(saida->formas, f)) return false;

    return true;
}

bool add_texto_saida(SAIDA s, const char*  texto){
    if (!s || !texto) return false;

    stSaida *saida = (stSaida*)s;

    char* dup = malloc(strlen(texto)+1);
    if (!dup) return false;
    
    strcpy(dup, texto);
    if (!add_fila(saida->textos, dup)) {
        free(dup);
        return false;
    }

    return true;
}

bool gerar_svg(SAIDA s, FILE* arq){

}


bool gerar_txt(SAIDA s, FILE* arq){

}

int gerar_id_trajeto(SAIDA s){
    if (!s) return -1;
    stSaida *saida = (stSaida*)s;
    
    return saida->cont_id_trajeto--;
}

