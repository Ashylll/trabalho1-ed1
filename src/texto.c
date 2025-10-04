#include "texto.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FFAMILY_PADRAO "sans"
#define FWEIGHT_PADRAO 'n'
#define FSIZE_PADRAO 12

typedef struct stEstilo{
    char* fFamily;
    char fWeight;
    int fSize;
} stEstilo;

typedef struct stTexto{
    int i;
    double x, y;
    char *corb, *corp, a, *txto;

    stEstilo estilo;
} stTexto;

TEXTO criar_texto(int i, double x, double y, const char* corb, const char* corp, char a, const char* txto){
    stTexto *t = malloc(sizeof(*t));
    if (!t) {
        fprintf(stderr, "Erro na alocação de memória");
        exit(1);
    }
    
    t->i = i;
    t->x = x;
    t->y = y;
    t->a = a;

    t->estilo.fFamily = malloc(strlen(FFAMILY_PADRAO)+1);
     if (!t->estilo.fFamily) {
        fprintf(stderr, "Erro na alocação de memória");
        free(t);
        exit(1);
    }
    strcpy(t->estilo.fFamily, FFAMILY_PADRAO);

    t->estilo.fWeight = FWEIGHT_PADRAO;
    t->estilo.fSize = FSIZE_PADRAO;


    t->corb = malloc(strlen(corb)+1);
    if (!t->corb){
        fprintf(stderr, "Erro na alocação de memória");
        free(t->estilo.fFamily);
        free(t);
        exit(1);    
    }
    strcpy(t->corb, corb);

    t->corp = malloc(strlen(corp)+1);
    if (!t->corp){
        fprintf(stderr, "Erro na alocação de memória");
        free(t->corb);
        free(t->estilo.fFamily);
        free(t);
        exit(1);    
    }
    strcpy(t->corp, corp);

    t->txto = malloc(strlen(txto)+1);
    if (!t->txto){
        fprintf(stderr, "Erro na alocação de memória");
        free(t->corp);
        free(t->corb);
        free(t->estilo.fFamily);
        free(t);
        exit(1);    
    }
    strcpy(t->txto, txto);

    return (TEXTO)t;

}

// Funções get

int getI_texto(TEXTO t){
    stTexto *texto = (stTexto*)t;

    return texto->i;

}



double getX_texto(TEXTO t){
    stTexto *texto = (stTexto*)t;

    return texto->x;

}


double getY_texto(TEXTO t){
    stTexto *texto = (stTexto*)t;

    return texto->y;

}


char* getCORB_texto(TEXTO t){
    stTexto *texto = (stTexto*)t;

    return texto->corb;
}


char* getCORP_texto(TEXTO t){
    stTexto *texto = (stTexto*)t;

    return texto->corp;
}


char getA_texto(TEXTO t){
    stTexto *texto = (stTexto*)t;

    return texto->a;
}


char* getTXTO_texto(TEXTO t){
    stTexto *texto = (stTexto*)t;

    return texto->txto;
}

// Funções set

bool setI_texto(TEXTO t, int i){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;
    texto->i = i;

    return true;
}

bool setX_texto(TEXTO t, double x){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;
    texto->x = x;

    return true;
}

bool setY_texto(TEXTO t, double y){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;
    texto->y = y;

    return true;
}

bool setCORB_texto(TEXTO t, char *corb){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;
    texto->corb = corb;

    return true;
}

bool setCORP_texto(TEXTO t, char *corp){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;
    texto->corp = corp;

    return true;
}

bool setA_texto(TEXTO t, char a){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;
    texto->a = a;

    return true;
}

bool setTXTO_texto(TEXTO t, char *txto){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;
    texto->txto = txto;

    return true;
}

// Função estilo

bool mudar_estilo(TEXTO t, char *fFamily, char fWeight, int fSize){
    if (!t) return false;

    stTexto *texto = (stTexto*)t;

    char *novaFamily = malloc(strlen(fFamily) + 1);
    if (!novaFamily) {
        fprintf(stderr, "Erro na alocação de memória\n");
        return false;
    }
    strcpy(novaFamily, fFamily);
    free(texto->estilo.fFamily);

    texto->estilo.fFamily = novaFamily;
    texto->estilo.fWeight = fWeight;
    texto->estilo.fSize = fSize;

    return true;
}