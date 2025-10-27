#include "svg.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"

#include <stdio.h>
#include <string.h>

static void esc_xml(const char* in, char* out, size_t cap){
    if (!in || !out || cap == 0) return;

    size_t k = 0;
    for (size_t i = 0; in[i] && k + 6 < cap; ++i){
        const char c = in[i];
        const char* rep = NULL;
        switch (c){
            case '&': rep = "&amp;";  break;
            case '<': rep = "&lt;";   break;
            case '>': rep = "&gt;";   break;
            case '"': rep = "&quot;"; break;
            case '\'':rep = "&apos;"; break;
        }
        if (rep){
            size_t len = strlen(rep);
            if (k + len < cap){
                memcpy(out + k, rep, len);
                k += len;
            }
        } else {
            out[k++] = c;
        }
    }
    out[k] = '\0';
}


void svg_begin(FILE *fp){
    if (!fp) return;

    fprintf(fp,
    "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" "
    "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
    );
}

void svg_escrever_forma(FILE *fp, FORMA f){
    if (!fp || !f) return;

    char tipo = getTipo_forma(f);
    void *hand = getHandle_forma(f);

    switch (tipo){
        case 'c': { 
            double x = getX_circulo(hand);
            double y = getY_circulo(hand);
            double r = getR_circulo(hand);
            const char *corb = getCORB_circulo(hand);
            const char *corp = getCORP_circulo(hand);

            fprintf(fp,
                "<circle style=\"fill:%s;fill-opacity:0.6;stroke:%s\" r=\"%.2f\" cy=\"%.2f\" cx=\"%.2f\" />\n",
                corp, corb, r, y, x);
            break;
        }

        case 'r': { 
            double x = getX_retangulo(hand);
            double y = getY_retangulo(hand);
            double w = getW_retangulo(hand);
            double h = getH_retangulo(hand);
            const char *corb = getCORB_retangulo(hand);
            const char *corp = getCORP_retangulo(hand);

            fprintf(fp,
                "<rect style=\"fill:%s;fill-opacity:0.6;stroke:%s\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n",
                corp, corb, x, y, w, h);
            break;
        }

        case 'l': {
            double x1 = getX1_linha(hand);
            double y1 = getY1_linha(hand);
            double x2 = getX2_linha(hand);
            double y2 = getY2_linha(hand);
            const char *cor = getCOR_linha(hand);

            fprintf(fp,
                "<line style=\"stroke:%s;stroke-width:1.5;stroke-opacity:0.6\" x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n",
                cor, x1, y1, x2, y2);
            break;
        }

        case 't': { 
            double x = getX_texto(hand);
            double y = getY_texto(hand);
            const char *corb = getCORB_texto(hand);
            const char *corp = getCORP_texto(hand);
            const char *txto = getTXTO_texto(hand);
            const char *family = getFFamily_texto(hand);
            const char *weight = getFWeight_texto(hand);
            int size = getFSize_texto(hand);

            char txt_esc[1024];
            esc_xml(txto, txt_esc, sizeof txt_esc);

            fprintf(fp,
                "<text style=\"fill:%s;fill-opacity:0.6;stroke:%s;font-family:%s;font-weight:%s;font-size:%dpx;line-height:0%%\" x=\"%.2f\" y=\"%.2f\">%s</text>\n",
                corp, corb, family, weight, size, x, y, txt_esc);
            break;
        }

        default:
            fprintf(stderr, "[svg_escrever_forma] tipo desconhecido: %c\n", tipo);
            break;
    }
}

void svg_escrever_texto(FILE *fp, TEXTO t){
    if (!fp || !t) return;

    double x = getX_texto(t);
    double y = getY_texto(t);
    const char *corb = getCORB_texto(t);  
    const char *corp = getCORP_texto(t);   
    const char *txto = getTXTO_texto(t);   
    const char *family = getFFamily_texto(t);
    const char *weight = getFWeight_texto(t);
    int size = getFSize_texto(t);

    char txt_esc[1024];
    esc_xml(txto, txt_esc, sizeof txt_esc);

    double opacity = 0.6;
    if (strcmp(txt_esc, "*") == 0 && strcmp(corp, "red") == 0) {
        opacity = 1.0;
    }

    fprintf(fp,
        "<text style=\"fill:%s;fill-opacity:%.1f;stroke:%s;"
        "font-family:%s;font-weight:%s;font-size:%dpx;line-height:0%%\" "
        "x=\"%.2f\" y=\"%.2f\">%s</text>\n",
        corp, opacity, corb, family, weight, size, x, y, txt_esc);
}

void svg_escrever_linha(FILE *fp, LINHA l){
    if (!fp || !l) return;

    double x1 = getX1_linha(l);
    double y1 = getY1_linha(l);
    double x2 = getX2_linha(l);
    double y2 = getY2_linha(l);
    const char *cor = getCOR_linha(l);

    fprintf(fp,
        "<line style=\"stroke:%s;stroke-width:2.0;stroke-opacity:0.6\" x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n",
        cor, x1, y1, x2, y2);
}

void svg_end(FILE *fp){
    if (!fp) return;
    
    fprintf(fp, "</svg>\n");
}


