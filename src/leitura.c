#include "leitura.h"
#include "saida.h"
#include "chao.h"
#include "disparador.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"
#include "repo.h"
#include "arena.h"
#include "calc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Comandos .geo */

static bool comando_c(const char *linha, CHAO chao){
    int i; 
    double x, y, r;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &i, &x, &y, &r, corb, corp) != 6) return false;

    CIRCULO c = criar_circulo(i, x, y, r, corb, corp);
    if (!c) return false;

    FORMA f = criar_forma('c', c);
    add_chao(chao, f);

    registrar_id(i);

    return true;    
}

static bool comando_r(const char *linha, CHAO chao){
    int i;
    double x, y, w, h;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &i, &x, &y, &w, &h, corb, corp) != 7) return false;
    
    RETANGULO r = criar_retangulo(i, x, y, w, h, corb, corp);
    if (!r) return false;

    
    FORMA f = criar_forma('r', r);
    add_chao(chao, f);
    
    registrar_id(i);

    return true;
}

static bool comando_l(const char *linha, CHAO chao){
    int i;
    double x1, y1, x2, y2;
    char cor[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s", &i, &x1, &y1, &x2, &y2, cor) != 6) return false;
    
    LINHA l = criar_linha(i, x1, y1, x2, y2, cor);
    if (!l) return false;

    FORMA f = criar_forma('l', l);
    add_chao(chao, f);
    
    registrar_id(i);

    return true;

}

static bool comando_t(const char *linha, const char *fFamily, const char *fWeight, int fSize, CHAO chao){
    int i;
    double x, y;
    char corb[32], corp[32], ancora, txto[512];

    if(sscanf(linha, "%*s %d %lf %lf %31s %31s %c %[^\n]", &i, &x, &y, corb, corp, &ancora, txto) < 7) return false;
    
    TEXTO t = criar_texto(i, x, y, corb, corp, ancora, txto);
    if (!t) return false;

    
    (void)mudar_estilo(t, fFamily, fWeight, fSize);
    FORMA f = criar_forma('t', t);
    add_chao(chao, f);
    
    registrar_id(i);
    
    return true;
}

static bool comando_ts(const char *linha, char *fFamily, char *fWeight, int *fSize){
    char novo_family[32], novo_weight[8];
    int novo_size;

    if (sscanf(linha, "%*s %31s %7s %d", novo_family, novo_weight, &novo_size) != 3) return false;

    strncpy(fFamily, novo_family, 31);
    fFamily[31] = '\0';

    strncpy(fWeight, novo_weight, 7);
    fWeight[7] = '\0';

    *fSize = novo_size;

    return true;
}

/* Comandos .qry */

static bool comando_pd(const char *linha, REPO  repo, SAIDA saida){
    int l; double x, y;

    if (sscanf(linha, "%*s %d %lf %lf", &l, &x, &y) != 3) return false;
    
    registrar_instrucao(saida);
    log_saida(saida, "[*] pd %d %.2f %.2f", l, x, y);

    DISPARADOR d = repo_assegurar_disparador(repo, l, x, y);
    if (d) posicionar_disparador(d, x, y);

    pula_linha(saida);

    return true;
}

static bool comando_lc(const char *linha, REPO repo, CHAO chao, SAIDA saida){
    int c_id, n;
    if (sscanf(linha, "%*s %d %d", &c_id, &n) != 2){
        fprintf(stderr, "sscanf\n");
        return false;
    } 
    
    registrar_instrucao(saida);
    log_saida(saida, "[*] lc %d %d", c_id, n);
    pula_linha(saida);
    
    CARREGADOR c = repo_assegurar_carregador(repo, c_id);
    if (!c) {
        fprintf(stderr, "repo assegurar\ncd_id = %d\nn = %d\n", c_id, n);
        return false;
    }
    for (int k = 0; k < n; k++){
        FORMA f = NULL;
        if (!rmv_chao(chao, &f)) break;
        info_forma_txt(saida, f);
        push_carregador(c, f);
        pula_linha(saida);
    }

    return true;
}

static bool comando_atch(const char *linha, REPO repo, SAIDA saida){
    int d_id, cesq_id, cdir_id;
    if (sscanf(linha, "%*s %d %d %d", &d_id, &cesq_id, &cdir_id) != 3) return false;

    registrar_instrucao(saida);
    log_saida(saida, "[*] atch %d %d %d", d_id, cesq_id, cdir_id);

    DISPARADOR d = repo_get_disparador(repo, d_id);
    if (!d) return false;

    CARREGADOR cesq = repo_take_carregador(repo, cesq_id);
    if (!cesq) cesq = criar_carregador(cesq_id);   

    CARREGADOR cdir = repo_take_carregador(repo, cdir_id);
    if (!cdir) cdir = criar_carregador(cdir_id);  

    CARREGADOR oldE = encaixar_cesq(d, cesq);
    CARREGADOR oldD = encaixar_cdir(d, cdir);

    if (oldE) destruir_carregador(&oldE);
    if (oldD) destruir_carregador(&oldD);
    
    pula_linha(saida);

    return true;
}

static bool comando_shft(const char *linha, REPO repo, SAIDA saida){
    int d_id, n; char lado; DISPARADOR d;
    if (sscanf(linha, "%*s %d %c %d", &d_id, &lado, &n) != 3) return false;

    registrar_instrucao(saida);
    log_saida(saida, "[*] shft %d %c %d", d_id, lado, n);

    d = repo_get_disparador(repo, d_id);
    if (!d || !shift_disparador(d, lado, n)) return false;

    FORMA f = forma_em_disparo(d);
    if (!f) return false;

    info_forma_txt(saida, f); 
    pula_linha(saida);
    
    return true;
}

static bool comando_dsp(const char *linha, REPO repo, SAIDA saida, ARENA arena){
    int d_id; double dx, dy; char modo = 'i';
    int lidos = sscanf(linha, "%*s %d %lf %lf %c", &d_id, &dx, &dy, &modo);

    if (lidos < 3) return false;

    if (lidos == 3) modo = 'i';
    if (modo != 'i' && modo != 'v') modo = 'i';

    registrar_instrucao(saida);

    if (lidos == 4){
        log_saida(saida, "[*] dsp %d %.2f %.2f %c", d_id, dx, dy, modo);
    } else {
        log_saida(saida, "[*] dsp %d %.2f %.2f",     d_id, dx, dy);
    }         

    pula_linha(saida);

    DISPARADOR d = repo_get_disparador(repo, d_id);
    if (!d) return false;

    return disparo(d, dx, dy, modo, saida, arena);
}

static bool comando_rjd(const char *linha, REPO repo, SAIDA saida, ARENA arena){
    int d_id; 
    char lado; 
    double dx, dy, ix, iy;
    if (sscanf(linha, "%*s %d %c %lf %lf %lf %lf", &d_id, &lado, &dx, &dy, &ix, &iy) != 6) return false;

    registrar_instrucao(saida);
    log_saida(saida, "[*] rjd %d %c %.2f %.2f %.2f %.2f", d_id, lado, dx, dy, ix, iy);
    pula_linha(saida);

    if (lado != 'e' && lado != 'd') return false;

    DISPARADOR d = repo_get_disparador(repo, d_id);
    if (!d) return false;

    return rajada(d, lado, dx, dy, ix, iy, saida, arena);
}

static bool comando_calc(CHAO chao, SAIDA saida, ARENA arena){
    registrar_instrucao(saida);
    add_texto_saida(saida, "[*] calc");

    return calc(chao, arena, saida);
}


bool ler_geo(const char *path_geo, CHAO chao){
    FILE *fp = fopen(path_geo, "r");
    if(!fp) return false;

    char linha[1024], comando[8];

    char fFamily[32] = "sans-serif";
    char fWeight[8] = "normal";
    int fSize = 20;

    while (fgets(linha, sizeof linha, fp)){
        if(sscanf(linha, "%7s", comando) != 1) continue;
        if(comando[0] == '#') continue;

        if (strcmp(comando, "c") == 0){
            if(!comando_c(linha, chao)){
                fprintf(stderr, "Erro ao processar o comando 'c'\n");
            }
        }

        else if (strcmp(comando, "r") == 0){
            if(!comando_r(linha, chao)){
                fprintf(stderr, "Erro ao processar o comando 'r'\n");
            }
        }

        else if (strcmp(comando, "l") == 0){
            if(!comando_l(linha, chao)){
                fprintf(stderr, "Erro ao processar o comando 'l'\n");
            }

        }

        else if(strcmp(comando, "t") == 0){
           if(!comando_t(linha, fFamily, fWeight, fSize, chao)){
                fprintf(stderr, "Erro ao processar o comando 't'\n");
           }
        }

        else if (strcmp(comando, "ts") == 0){
            if(!comando_ts(linha, fFamily, fWeight, &fSize)){
                fprintf(stderr, "Erro ao processar o comando 'ts'\n");
            }
        }
    }

    fclose(fp);

    return true;
}

bool ler_qry(const char *path_qry, REPO repo, CHAO chao, SAIDA saida){
    FILE *fp = fopen(path_qry, "r");
    if(!fp) return false;

    ARENA arena = criar_arena();

    char linha[1024], comando [8];

    while (fgets(linha, sizeof linha, fp)){
        if (sscanf(linha, "%7s", comando) != 1) continue;
        if (comando[0] == '#') continue;

        if (strcmp(comando, "pd") == 0){
            if (!comando_pd(linha, repo, saida)){
                fprintf(stderr, "Erro ao processar o comando 'pd'\n");
                return false;
            }
        }

        else if (strcmp(comando, "lc") == 0){
            if (!comando_lc(linha, repo, chao, saida)){
                fprintf(stderr, "Erro ao processar o comando 'lc'\n");
                return false;
            }
        }

        else if (strcmp(comando, "atch") == 0){
            if (!comando_atch(linha, repo, saida)){
                fprintf(stderr, "Erro ao processar o comando 'atch'\n");
                return false;
            }
        }

        else if (strcmp(comando, "shft") == 0){
            if (!comando_shft(linha, repo, saida)){
                fprintf(stderr, "Erro ao processar o comando 'shft'\n");
                return false;
            }
        }

        else if (strcmp(comando, "dsp") == 0){
            if (!comando_dsp(linha, repo, saida, arena)){
                fprintf(stderr, "Erro ao processar o comando 'dsp'\n");
                return false;
            }
        }

        else if (strcmp(comando, "rjd") == 0){
            if (!comando_rjd(linha, repo, saida, arena)){
                fprintf(stderr, "Erro ao processar o comando 'rjd'\n");
                return false;
            }
        }

        else if (strcmp(comando, "calc") == 0){
            if (!comando_calc(chao, saida, arena)){
                fprintf(stderr, "Erro ao processar o comando 'calc'\n");
                return false;
            }
        }

    }

    destruir_arena(&arena);
    fclose(fp);
    return true;
}    

