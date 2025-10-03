#include "linha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct stLinha {
    int i;
    double x1, y1, x2, y2;
    char *cor;
} stLinha;

LINHA criar_linha(int i, double x1, double y1, double x2, double y2, const char* cor){
    stLinha *l = malloc(sizeof(stLinha));
   if (!l){
    fprintf(stderr, "Erro na alocação de memória");
    exit(1);
   }

    l->i = i;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;

    l->cor = malloc(strlen(cor)+1);
    if (l->cor == NULL){
        fprintf(stderr, "Erro na alocação de memória");
        free(l);
        exit(1);
    }
    strcpy(l->cor, cor);

    return (LINHA)l;
}

// Funções get

double getX1_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->x1;
}

double getY1_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->y1;
}

double getX2_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->x2;
}

double getY2_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->y2;
}

char* getCOR_linha(LINHA l){
    stLinha *linha = (stLinha*)l;

    return linha->cor;
}


// Funções set

bool setI_linha(LINHA l, int i){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->i = i;

    return true;
}

bool setI_linha(LINHA l, double x1){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->x1 = x1;
    
    return true;
}

bool setI_linha(LINHA l, double y1){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->y1 = y1;

    return true;
}

bool setI_linha(LINHA l, double x2){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->x2 = x2;

    return true;
}

bool setI_linha(LINHA l, double y2){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    linha->y2 = y2;

    return true;
}

bool setI_linha(LINHA l, char* cor){
    if (!l) return false;

    stLinha *linha = (stLinha*)l; 
    strcpy(linha->cor, cor);

    return true;
}