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
    if (!corb || !corp) {
        fprintf(stderr, "Cores inválidas\n");
        return NULL;
    }

    if (w < 0 || h < 0) {
        fprintf(stderr, "Dimensões inválidas\n");
        return NULL;
    }
 
    stRetangulo *retangulo = malloc(sizeof(*retangulo));
    if (!retangulo) {
        fprintf(stderr, "Erro na alocação de memória\n");
        return NULL;
    }

    retangulo->i = i;
    retangulo->x = x;
    retangulo->y = y;
    retangulo->w = w;
    retangulo->h = h;

    retangulo->corb = malloc(strlen(corb)+1);
    if (!retangulo->corb){
        fprintf(stderr, "Erro na alocação de memória\n");
        free(retangulo);
        return NULL;
    }
    strcpy(retangulo->corb, corb);

    retangulo->corp = malloc(strlen(corp)+1);
    if (!retangulo->corp){
        fprintf(stderr, "Erro na alocação de memória\n");
        free(retangulo->corb);
        free(retangulo);
        return NULL;
    }
    strcpy(retangulo->corp, corp);

    return retangulo;
}

double area_retangulo(RETANGULO r){
    stRetangulo *retangulo = (stRetangulo*)r;

     double area = retangulo->w * retangulo->h;

     return area;
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