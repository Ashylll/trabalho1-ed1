#include "retangulo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct stRetangulo {
    int i;
    double x, y, w, h;
    char *corb, *corp;
} stRetangulo;

RETANGULO criar_retangulo(int i, double x, double y, double w, double h, const char* corb, const char* corp){
    stRetangulo *r = malloc(sizeof(stRetangulo));
    if (!r) {
        fprintf(stderr, "Erro na alocação de memória");
        free(r);
        exit(1);
    }

    r->i = i;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;

    r->corb = malloc(strlen(corb)+1);
    if (!corb){
        fprintf(stderr, "Erro na alocação de memória");
        free(r);
        exit(1);
    }
    strcpy(r->corb, corb);

    r->corp = malloc(strlen(corp)+1);
    if (!corp){
        fprintf(stderr, "Erro na alocação de memória");
        free(r);
        exit(1);
    }
    strcpy(r->corp, corp);

    return (RETANGULO)r;
}


// Funções get

int getI_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->i;
}

double getX_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->x;
}

double getY_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->y;
}

double getW_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->w;
}

double getH_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->h;
}

char* getCORB_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->corb;
}

char* getCORP_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

    return retangulo->corp;
}

// Funções set

bool setI_retangulo(RETANGULO r, int i){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->i = i;

    return true;
}

bool setX_retangulo(RETANGULO r, double x){
    if (!r) return false;

   stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->x = x;

    return true;
}

bool setY_retangulo(RETANGULO r, double y){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->y = y;

    return true;
}

bool setW_retangulo(RETANGULO r, double w){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->w = w;

    return true;
}

bool setH_retangulo(RETANGULO r, double h){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    retangulo->h = h;

    return true;
}


bool setCORB_retangulo(RETANGULO r, const char* corb){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    strcpy(retangulo->corb, corb);

    return true;
}

bool setCORP_retangulo(RETANGULO r, const char* corp){
    if (!r) return false;

    stRetangulo *retangulo = (stRetangulo*)r; 
    strcpy(retangulo->corp, corp);
    
    return true;
}