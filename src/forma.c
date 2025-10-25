#include "forma.h"
#include "retangulo.h"
#include "circulo.h"    
#include "texto.h"      
#include "linha.h"

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct stForma{
    char tipo;
    void* handle;
} stForma;

FORMA criar_forma(char tipo, void* handle){
    if (!handle || (tipo != 'c' && tipo != 'r' && tipo != 't' && tipo != 'l')) return NULL;

    stForma* forma = malloc(sizeof(stForma));
    if (!forma) return NULL;

    forma->tipo = tipo;
    forma->handle = handle;

    return forma;
}

void destruir_forma(FORMA *f){
    if (!f || !*f) return;
    stForma *forma = (stForma*)*f;

    switch (forma->tipo){
        case 'c': destruir_circulo((CIRCULO*)&forma->handle); break;
        case 'r': destruir_retangulo((RETANGULO*)&forma->handle); break;
        case 't': destruir_texto((TEXTO*)&forma->handle); break;
        case 'l': destruir_linha((LINHA*)&forma->handle); break;
    }
    
    free(forma);
    *f = NULL;
}

int getI_forma(FORMA f){
    assert(f != NULL);

    stForma *forma = (stForma*)f;

    if(!forma->handle) return -1;

    switch (forma->tipo){
        case 'c': return getI_circulo(forma->handle);
        case 'r': return getI_retangulo(forma->handle);
        case 't': return getI_texto(forma->handle);
        case 'l': return getI_linha(forma->handle); 
        default: return - 1;
    }
}

char getTipo_forma(FORMA f){
    assert(f != NULL);
    stForma* forma = (stForma*)f;

    return forma->tipo;
}

void* getHandle_forma(FORMA f){
    if (!f) return NULL;
    stForma* forma = (stForma*)f;

    return forma->handle;
}

bool getXY_forma(FORMA f, double *x, double *y){
    if (!f || !x || !y) return false;

    stForma* forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': *x = getX_circulo(forma->handle); *y = getY_circulo(forma->handle); break;
        case 'r': *x = getX_retangulo(forma->handle); *y = getY_retangulo(forma->handle); break;
        case 't': *x = getX_texto(forma->handle); *y = getY_texto(forma->handle); break;
        case 'l': *x = getX1_linha(forma->handle); *y = getY1_linha(forma->handle); break;
        default: return false;
    }

    return true;
}

bool setXY_forma(FORMA f, double x, double y){
    if (!f) return false;

    stForma* forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': return setX_circulo(forma->handle, x) && setY_circulo(forma->handle, y);
        case 'r': return setX_retangulo(forma->handle, x) && setY_retangulo(forma->handle, y);
        case 't': return setX_texto(forma->handle, x) && setY_texto(forma->handle, y);
        case 'l': {
                double x1 = getX1_linha(forma->handle);
                double y1 = getY1_linha(forma->handle);
                double x2 = getX2_linha(forma->handle);
                double y2 = getY2_linha(forma->handle);
                double dx = x - x1;
                double dy = y - y1;
                return setX1_linha(forma->handle, x) && setY1_linha(forma->handle, y) &&
                setX2_linha(forma->handle, x2 + dx) && setY2_linha(forma->handle, y2 + dy);
        }
        default: return false;
    }
}

bool deslocar_forma(FORMA f, double dx, double dy){
    if (!f) return false;

    double x, y;

    if (!getXY_forma(f, &x, &y)) return false;

    return setXY_forma(f, x + dx, y + dy);
}
