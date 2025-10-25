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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool ler_geo(const char *path_geo, CHAO chao, SAIDA saida){
    FILE *fp = fopen(path_geo, "r");
    if(!fp) return false;

    char linha[1024], comando[8];

    char fFamily[32] = "sans";
    char fWeight[8] = "n";
    int fSize = 12;

    while (fgets(linha, sizeof linha, fp)){
        if(sscanf(linha, "%7s", comando) != 1) continue;
        if(comando[0] == '#') continue;

        if (strcmp(comando, "c") == 0){
            int i; 
            double x, y, r;
            char corb[32], corp[32];
            CIRCULO c = NULL;

            if(sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &i, &x, &y, &r, corb, corp) == 6){
                c = criar_circulo(i, x, y, r, corb, corp);
            } 

            if (c){
                FORMA f = criar_forma('c', c);
                add_chao(chao, f);
                add_forma_saida(saida, f);
            }
        }

        else if (strcmp(comando, "r") == 0){
            int i;
            double x, y, w, h;
            char corb[32], corp[32];
            RETANGULO r = NULL;

            if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &i, &x, &y, &w, &h, corb, corp) == 7){
                r = criar_retangulo(i, x, y, w, h, corb, corp);
            }

            if (r){
                FORMA f = criar_forma('r', r);
                add_chao(chao, f);
                add_forma_saida(saida, f);
            }
        }

        else if (strcmp(comando, "l") == 0){
            int i;
            double x1, y1, x2, y2;
            char cor[32];
            LINHA l = NULL;

            if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s", &i, &x1, &y1, &x2, &y2, cor) == 6){
                l = criar_linha(i, x1, y1, x2, y2, cor);
            }

            if (l){
                FORMA f = criar_forma('l', l);
                add_chao(chao, f);
                add_forma_saida(saida, f);
            }

        }

        else if(strcmp(comando, "t") == 0){
            int i;
            double x, y;
            char corb[32], corp[32], ancora, txto[512];
            TEXTO t = NULL;

            if(sscanf(linha, "%*s %d %lf %lf %31s %31s %c %[^\n]", &i, &x, &y, corb, corp, &ancora, txto) >= 7){
                t = criar_texto(i, x, y, corb, corp, ancora, txto);
            }
            
            if (t){
                (void)mudar_estilo(t, fFamily, fWeight, fSize);
                FORMA f = criar_forma('t', t);
                add_chao(chao, f);
                add_forma_saida(saida, f);
            }
        }

        else if (strcmp(comando, "ts") == 0){
            if(sscanf(linha, "%*s %31s %7s %d", fFamily, fWeight, &fSize) == 3){
                
            }
        }
    }

    fclose(fp);

    return true;
}

bool ler_qry(const char *path_qry, REPO repo, CHAO chao, SAIDA saida){
    FILE *fp = fopen(path_qry, "r");
    if(!fp) return false;

    char linha[1024], comando [8];

    while (fgets(linha, sizeof linha, fp)){
        if (sscanf(linha, "%7s", comando) != 1) continue;
        if (comando[0] == '#') continue;

        if (strcmp(comando, "pd") == 0){
            int l;
            double x, y;
            DISPARADOR d = NULL;

            if (sscanf(linha, "%d %lf %lf", &l, &x, &y) == 3){
                d = repo_assegurar_disparador(repo, l, x, y);
                if (d) posicionar_disparador(d, x, y);
            }
        }

        else if (strcmp(comando, "lc") == 0){
            int c, n;
            CARREGADOR c = NULL;
            if (sscanf(linha, "%*s %d %d", &c, &n) == 2){
                c = repo_assegurar_carregador(repo, c);
                if (c) load_carregador(c, chao, n);
            }
        }

        else if (strcmp(comando, "atch") == 0){
            int d_id, cesq, dir;
            DISPARADOR d;
            CARREGADOR cesq;
            CARREGADOR cdir;

            if (sscanf(linha, "%*s %d %d %d", &d_id, &cesq, &cdir) == 3){
                d = repo_get_disparador(repo, d_id);
                if (d){
                    cesq = repo_take_carregaodor(repo, cesq);
                    cdir = repo_take_carregaodor(repo, cdir);
                    if (cesq) encaixar_cesq(d, cesq);
                    if (cdir) encaixar_cdir(d, cdir);
                }  
            }
        }

        else if (strcmp(comando, "shft") == 0){
            int d_id, n;
            char lado;
            DISPARADOR d;

            if (sscanf(linha, "%*s %d %c %d", &d_id, &lado, &n)){
                d = repo_get_disparador(repo, d_id);
                if (d) shift_disparador(d, lado, n);
            }
        }

        else if (strcmp(comando, "dsp") == 0){
            int d_id;
            double dx, dy;
            char modo = 'i';
            DISPARADOR d;

            if (sscanf(linha, "%*s %d %lf %lf  %c", &d_id, &dx, &dy, &modo) >= 3){
                d = repo_get_disparador(repo, d_id);
                if (d) disparo(d, dx, dy, modo, saida);
            }
        }

        else if (strcmp(comando, "dsp") == 0){
            int d_id;
            char lado;
            double dx, dy, ix, iy;
            DISPARADOR d;

            if (sscanf(linha, "%*s %d %c %lf %lf %lf %lf", &d_id, &lado, &dx, &dy, &ix, &iy) == 6){
                d = repo_get_disparador(repo, d_id);
                if (d) rajada(d, lado, dx, dx, ix, iy);
            }
        }

        else if (strcmp(comando, "calc") == 0){

        }
    }

    fclose(fp);
    return true;
}

