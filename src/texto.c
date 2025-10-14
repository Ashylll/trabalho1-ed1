#include "texto.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FFAMILY_PADRAO "sans"
#define FWEIGHT_PADRAO 'n'
#define FSIZE_PADRAO 12
#define CONST_AREA 20.0

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
    if (!corb || !corp || !txto) {
        fprintf(stderr, "Cores/texto inválidos\n");
        return NULL;
    }

    if (a != 'i' && a != 'm' && a != 'f') {
        fprintf(stderr, "Parâmetro 'a' inválido\n");
        return NULL;
    }
    
    stTexto *texto = malloc(sizeof(*texto));
    if (!texto) {
        fprintf(stderr, "Erro na alocação de memória\n");
        return NULL;
    }
    
    texto->i = i;
    texto->x = x;
    texto->y = y;
    texto->a = a;

    texto->estilo.fFamily = malloc(strlen(FFAMILY_PADRAO)+1);
     if (!texto->estilo.fFamily) {
        fprintf(stderr, "Erro na alocação de memória\n");
        free(texto);
        return NULL;
    }
    strcpy(texto->estilo.fFamily, FFAMILY_PADRAO);

    texto->estilo.fWeight = FWEIGHT_PADRAO;
    texto->estilo.fSize = FSIZE_PADRAO;


    texto->corb = malloc(strlen(corb)+1);
    if (!texto->corb){
        fprintf(stderr, "Erro na alocação de memória\n");
        free(texto->estilo.fFamily);
        free(texto);
        return NULL;    
    }
    strcpy(texto->corb, corb);

    texto->corp = malloc(strlen(corp)+1);
    if (!texto->corp){
        fprintf(stderr, "Erro na alocação de memória\n");
        free(texto->corb);
        free(texto->estilo.fFamily);
        free(texto);
        return NULL;    
    }
    strcpy(texto->corp, corp);

    texto->txto = malloc(strlen(txto)+1);
    if (!texto->txto){
        fprintf(stderr, "Erro na alocação de memória\n");
        free(texto->corp);
        free(texto->corb);
        free(texto->estilo.fFamily);
        free(texto);
        return NULL;    
    }
    strcpy(texto->txto, txto);

    return texto;

}

double area_texto(TEXTO t){
    if(!t) return 0.0;

    stTexto *texto = (stTexto*)t;

    if (!texto->txto) return 0.0;

    double area = CONST_AREA * (double)(strlen(texto->txto));

    return area;
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