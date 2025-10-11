#include "circulo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PI 3.14

typedef struct stCirculo{
    int i;
    double x, y, r;
    char *corb, *corp;
} stCirculo;

CIRCULO criar_circulo(int i, double x, double y, double r, const char *corb, const char *corp){
    stCirculo *c = malloc(sizeof(stCirculo));
   if (!c){
    fprintf(stderr, "Erro na alocação de memória");
    exit(1);
   }

    c->i = i;
    c->x = x;
    c->y = y;
    c->r = r;
    
    c->corb = malloc(strlen(corb)+1);
    if (c->corb == NULL){
        fprintf(stderr, "Erro na alocação de memória");
        free(c);
        exit(1);
    }
    strcpy(c->corb, corb);

     c->corp = malloc(strlen(corp)+1);
    if (c->corp == NULL){
        fprintf(stderr, "Erro na alocação de memória");
        free(c->corb);
        free(c);
        exit(1);
    }
    strcpy(c->corp, corp);

    return (CIRCULO)c;
}

double area_circulo(CIRCULO c){
    stCirculo *circulo = (stCirculo*)c;

    double area = PI * circulo->r * circulo->r;
    
    return area;
}

// Funções get

int getI_circulo(CIRCULO c){
    stCirculo *circulo = (stCirculo*)c;

    return circulo->i;
}

double getX_circulo(CIRCULO c){
    stCirculo *circulo = (stCirculo*)c;

    return circulo->x;
}

double getY_circulo(CIRCULO c){
    stCirculo *circulo = (stCirculo*)c;

    return circulo->y;
}

double getR_circulo(CIRCULO c){
    stCirculo *circulo = (stCirculo*)c;

    return circulo->r;
}

char* getCORB_circulo(CIRCULO c){
    stCirculo *circulo = (stCirculo*)c;

    return circulo->corb;
}

char* getCORP_circulo(CIRCULO c){
    stCirculo *circulo = (stCirculo*)c;

    return circulo->corp;
}

// Funções set

bool setI_circulo(CIRCULO c, int i){
    if (!c) return false;

    stCirculo *circulo = (stCirculo*)c; 
    circulo->i = i;
    return true;
}

bool setX_circulo(CIRCULO c, double x){
    if (!c) return false;

   stCirculo *circulo = (stCirculo*)c; 
    circulo->x = x;

    return true;
}

bool setY_circulo(CIRCULO c, double y){
    if (!c) return false;

    stCirculo *circulo = (stCirculo*)c; 
    circulo->y = y;

    return true;
}

bool setR_circulo(CIRCULO c, double r){
    if (!c) return false;

    stCirculo *circulo = (stCirculo*)c; 
    circulo->r = r;

    return true;
}

bool setCORB_circulo(CIRCULO c, const char* corb){
    if (!c) return false;

    stCirculo *circulo = (stCirculo*)c; 
    strcpy(circulo->corb, corb);

    return true;
}

bool setCORP_circulo(CIRCULO c, const char* corp){
    if (!c) return false;

    stCirculo *circulo = (stCirculo*)c; 
    strcpy(circulo->corp, corp);
    
    return true;
}