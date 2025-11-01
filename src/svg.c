#include "svg.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>


static const char* svg_safe_color(const char* in, char* out, size_t cap){
    if (!out || cap == 0) return "#000000";
    if (!in || !*in) { strcpy(out, "#000000"); return out; }

    if (in[0] == '#') {
        size_t n = strlen(in);
        if (n == 4 || n == 7) {
            int ok = 1;
            for (size_t i = 1; i < n; ++i)
                if (!isxdigit((unsigned char)in[i])) { ok = 0; break; }
            if (ok) { strncpy(out, in, cap-1); out[cap-1]='\0'; return out; }
        }
    }
    int letras = 1;
    for (const char *p = in; *p; ++p){
        unsigned char c = (unsigned char)*p;
        if (!(c>='a' && c<='z')) { letras = 0; break; }
    }
    if (letras && strlen(in) < cap) { strcpy(out, in); return out; }

    strcpy(out, "#000000");
    fprintf(stderr, "[svg] cor inválida → fallback (#000000): \"%s\"\n", in);
    return out;
}

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

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
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
            char corb_ok[32], corp_ok[32];

            double opacidade = 0.6;

            fprintf(fp,
            "<circle style=\"fill:%s;fill-opacity:%.1f;stroke:%s\" r=\"%.2f\" cy=\"%.2f\" cx=\"%.2f\" />\n",
            svg_safe_color(corp, corp_ok, sizeof corp_ok),
            opacidade,
            svg_safe_color(corb, corb_ok, sizeof corb_ok),
            r, y, x);

            break;
        }

        case 'r': { 
            double x = getX_retangulo(hand);
            double y = getY_retangulo(hand);
            double w = getW_retangulo(hand);
            double h = getH_retangulo(hand);
            const char *corb = getCORB_retangulo(hand);
            const char *corp = getCORP_retangulo(hand);
            char corb_ok[32], corp_ok[32];

            double opacidade = 0.6;

            fprintf(fp,
            "<rect style=\"fill:%s;fill-opacity:%.1f;stroke:%s\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n",
            svg_safe_color(corp, corp_ok, sizeof corp_ok),
            opacidade,
            svg_safe_color(corb, corb_ok, sizeof corb_ok),
            x, y, w, h);

            break;
        }

        case 'l': {
            double x1 = getX1_linha(hand);
            double y1 = getY1_linha(hand);
            double x2 = getX2_linha(hand);
            double y2 = getY2_linha(hand);
            const char *cor = getCOR_linha(hand);
            char cor_ok[32];

            double opacidade = 0.8;

            fprintf(fp,
            "<line style=\"stroke:%s;stroke-width:2.0;stroke-opacity:%.1f\" x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n",
            svg_safe_color(cor, cor_ok, sizeof cor_ok),
            opacidade, x1, y1, x2, y2);

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

            char corb_ok[32], corp_ok[32];

            double opacidade = 1.0;

            fprintf(fp,
                "<text style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:0.7;"
                "font-family:%s;font-weight:%s;font-size:%dpx;line-height:0%%\" "
                "x=\"%.2f\" y=\"%.2f\">%s</text>\n",
                svg_safe_color(corp,   corp_ok,   sizeof corp_ok),
                opacidade,
                svg_safe_color(corb,   corb_ok,   sizeof corb_ok),
                family, weight, size, x, y, txt_esc);
                
                break;
        }

        default:
            fprintf(stderr, "[svg_escrever_forma] tipo desconhecido: %c\n", tipo);
            break;
    }
}



void svg_end(FILE *fp){
    if (!fp) return;
    
    fprintf(fp, "</svg>\n");
}


