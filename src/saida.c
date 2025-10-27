#include "saida.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"
#include "fila.h"
#include "svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void coord_marca(FORMA f, double *px, double *py){
    *px = *py = 0.0;
    if (!f) return;

    char t = getTipo_forma(f);
    void *hand = getHandle_forma(f);

    switch (t){
        case 'c': 
            *px = getX_circulo(hand);
            *py = getY_circulo(hand);
            break;
        case 'r': 
            *px = getX_retangulo(hand) + getW_retangulo(hand) * 0.5;
            *py = getY_retangulo(hand) + getH_retangulo(hand) * 0.5;
            break;
        case 'l': { 
            double x1 = getX1_linha(hand), y1 = getY1_linha(hand);
            double x2 = getX2_linha(hand), y2 = getY2_linha(hand);
            *px = (x1 + x2) * 0.5;
            *py = (y1 + y2) * 0.5;
        } break;
        case 't':
            *px = getX_texto(hand);
            *py = getY_texto(hand);
            break;
        default: break;
    }
}

typedef struct stSaida {
    FILA formas;
    FILA textos;
    int cont_id_trajeto;
    double pontuacao_total;
    int n_instrucoes;
    int n_disparos;
    int n_esmagadas;
    int n_clones;
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
    saida->pontuacao_total = 0.0;
    saida->n_instrucoes = saida->n_disparos = saida->n_esmagadas = saida->n_clones = 0;

    return saida;
}

void destruir_saida(SAIDA *s){
    if (!s || !*s) return;
    stSaida *saida = (stSaida*)*s;
    void *aux;

    while (rmv_fila(saida->formas, &aux)) {
        FORMA f = (FORMA)aux;
        if (f && getI_forma(f) < 0) destruir_forma(&f);
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

bool gerar_svg(SAIDA s, CHAO chao, FILE *fp){
    if (!s || !chao || !fp) return false;

    stSaida *saida = (stSaida*)s;
    svg_begin(fp);

    // Desenha o chão (todas as formas atuais)
    percorrer_chao(chao, fp);

    // Desenha as formas auxiliares (trajetórias e asteriscos)
    void *aux;
    FILA tmp = copiar_fila(saida->formas);
    while (rmv_fila(tmp, &aux)){
        svg_escrever_forma(fp, (FORMA)aux);
    }
    destruir_fila(&tmp);

    svg_end(fp);
    return true;
}

bool gerar_txt(SAIDA s, FILE* arq){
    if (!s || !arq) return false;
    stSaida *saida = (stSaida*)s;

    // 1) Logs
    void *aux;
    FILA tmp = copiar_fila(saida->textos);
    while (rmv_fila(tmp, &aux)){
        fprintf(arq, "%s\n", (char*)aux);
    }
    destruir_fila(&tmp);

    // 2) Sumário final (no fim do arquivo)
    fprintf(arq,
        "\n=== RELATÓRIO FINAL ===\n"
        "Pontuação total: %.2f\n"
        "Instruções: %d\n"
        "Disparos: %d\n"
        "Esmagadas: %d\n"
        "Clones: %d\n",
        get_pontuacao(saida),
        get_instrucoes(saida),
        get_disparos(saida),
        get_esmagadas(saida),
        get_clones(saida)
    );
    return true;
}


int gerar_id_trajeto(SAIDA s){
    if (!s) return -1;
    stSaida *saida = (stSaida*)s;
    
    return saida->cont_id_trajeto--;
}

void somar_pontuacao(SAIDA s, double area){
    if(s) ((stSaida*)s)->pontuacao_total += area;
}

void registrar_esmagada(SAIDA s){
    if(s) ((stSaida*)s)->n_esmagadas += 1;
}

void registrar_instrucao(SAIDA s){
    if(s) ((stSaida*)s)->n_instrucoes++;
}

void registrar_disparo(SAIDA s){
    if(s) ((stSaida*)s)->n_disparos++;
}

void registrar_clone(SAIDA s){
    if(s) ((stSaida*)s)->n_clones++;
}

double get_pontuacao(SAIDA s){
    if (!s) return 0.0;
    return ((stSaida*)s)->pontuacao_total;
}

int get_instrucoes(SAIDA s){
    if (!s) return 0;
    return ((stSaida*)s)->n_instrucoes;
}

int get_disparos(SAIDA s){
    if (!s) return 0;
    return ((stSaida*)s)->n_disparos;
}

int get_esmagadas(SAIDA s){
    if (!s) return 0;
    return ((stSaida*)s)->n_esmagadas;
}

int get_clones(SAIDA s){
    if (!s) return 0;
    return ((stSaida*)s)->n_clones;
}

void marcar_esmagada(SAIDA s, FORMA esmagada){
    if (!s || !esmagada) return;
    stSaida *saida = (stSaida*)s;

    double x, y;
    coord_marca(esmagada, &x, &y);

    int id = gerar_id_trajeto(s);
 
    TEXTO t = criar_texto(id, x, y, "none", "red", 'm', "*");
    if (!t) return;
    mudar_estilo(t, "sans", "b", 20);

    FORMA marca = criar_forma('t', t);
    if (!marca){
        destruir_texto(&t);
        return;
    }

    add_forma_saida(saida, marca);
}

void info_forma_txt(SAIDA s, FORMA f){
    if (!s || !f) return;

    char buf[256];
    char t = getTipo_forma(f);
    void *hand = getHandle_forma(f);

    switch (t){
        case 'c': {
            snprintf(buf, sizeof buf, "Círculo %d", getI_circulo(hand));
            add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "x: %.2f", getX_circulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "y: %.2f", getY_circulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "r: %.2f", getR_circulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "corb: %s", getCORB_circulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "corp: %s", getCORP_circulo(hand)); add_texto_saida(s, buf);
        } break;

        case 'r': {
            snprintf(buf, sizeof buf, "Retângulo %d", getI_retangulo(hand));
            add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "x: %.2f", getX_retangulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "y: %.2f", getY_retangulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "w: %.2f", getW_retangulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "h: %.2f", getH_retangulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "corb: %s", getCORB_retangulo(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "corp: %s", getCORP_retangulo(hand)); add_texto_saida(s, buf);
        } break;

        case 'l': {
            snprintf(buf, sizeof buf, "Linha %d", getI_linha(hand));
            add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "x1: %.2f", getX1_linha(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "y1: %.2f", getY1_linha(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "x2: %.2f", getX2_linha(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "y2: %.2f", getY2_linha(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "cor: %s", getCOR_linha(hand)); add_texto_saida(s, buf);
        } break;

        case 't': {
            snprintf(buf, sizeof buf, "Texto %d", getI_texto(hand));
            add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "x: %.2f", getX_texto(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "y: %.2f", getY_texto(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "corb: %s", getCORB_texto(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "corp: %s", getCORP_texto(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "font: %s", getFFamily_texto(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "weight: %s", getFWeight_texto(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "size: %d", getFSize_texto(hand)); add_texto_saida(s, buf);
            snprintf(buf, sizeof buf, "txt: \"%s\"", getTXTO_texto(hand)); add_texto_saida(s, buf);
        } break;

        default:
            add_texto_saida(s, "Forma desconhecida");
        break;
    }
}

void info_posicoes_txt(SAIDA s, double xi, double yi, double xf, double yf){
    if (!s) return;
    char buf[128];
    snprintf(buf, sizeof buf, "pos_inicial: (%.2f,%.2f)", xi, yi);
    add_texto_saida(s, buf);
    snprintf(buf, sizeof buf, "pos_final: (%.2f,%.2f)", xf, yf);
    add_texto_saida(s, buf);
}

void pula_linha(SAIDA s){
    if (!s) return;
    add_texto_saida(s, "");
}


