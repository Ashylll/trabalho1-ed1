#include "leitura.h"
#include "repo.h"
#include "chao.h"
#include "saida.h"
#include "svg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Helper para copiar o nome-base sem diretórios e sem extensão
static void basename_sem_ext(const char* path, char* dest, size_t destsz) {
    if (!dest || destsz == 0) return;
    dest[0] = '\0';
    if (!path) return;

    const char *p = strrchr(path, '/');
    if (!p) p = strrchr(path, '\\');
    p = p ? p + 1 : path;

    snprintf(dest, destsz, "%s", p);

    char *dot = strrchr(dest, '.');
    if (dot) *dot = '\0';
}

int main(int argc, char *argv[]){
    char path_in[256] = ".", path_out[256] = ".";
    char geo[128] = "", qry[128] = "";

    bool tem_geo = false, tem_qry = false, tem_out = false;
    int i;

    // Lê as flags
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i+1 < argc) {
            strcpy(path_in, argv[++i]);

        } else if (strcmp(argv[i], "-f") == 0 && i+1 < argc) {
            strcpy(geo, argv[++i]);
            tem_geo = true;

        } else if (strcmp(argv[i], "-q") == 0 && i+1 < argc) {
            strcpy(qry, argv[++i]);
            tem_qry = true;

        } else if (strcmp(argv[i], "-o") == 0 && i+1 < argc) {
            strcpy(path_out, argv[++i]);
            tem_out = true;

        } else {
            fprintf(stderr, "Aviso: flag desconhecida ou argumento ignorado: %s\n", argv[i]);
        }
}

    if (!tem_geo) {
        fprintf(stderr, ".geo não informado (obrigatório)\n");
        return 1;
    }

    if (!tem_out) {
        fprintf(stderr, "diretório de saída (-o) não informado (obrigatório)\n");
        return 1;
}

    // Monta caminhos completos 
    char geo_path[512], qry_path[512] = "";

    snprintf(geo_path, sizeof geo_path, "%s/%s", path_in, geo);

    if (tem_qry) snprintf(qry_path, sizeof qry_path, "%s/%s", path_in, qry);

    // Cria estruturas principais 
    CHAO chao = criar_chao();
    REPO repo = criar_repo();
    SAIDA saida = criar_saida();

    // leitura .geo
    if (!ler_geo(geo_path, chao, saida)) {
        fprintf(stderr, "Erro ao ler .geo\n");
        destruir_saida(&saida);
        destruir_repo(&repo);
        destruir_chao(&chao);

        return 2;
    }

    // Remove extensão .geo
    char base_geo[128];
    basename_sem_ext(geo, base_geo, sizeof base_geo);

    // Gera SVG inicial
    char svg_ini[512];
    snprintf(svg_ini, sizeof svg_ini, "%s/%s.svg", path_out, base_geo);
    FILE *fp_ini = fopen(svg_ini, "w");
    if (!fp_ini) {
        fprintf(stderr, "Erro: falha ao criar %s\n", svg_ini);
        
    } else {
        gerar_svg(saida, chao, fp_ini);
        fclose(fp_ini);
    }

    // Se tiver .qry
    if (tem_qry) {
        if (!ler_qry(qry_path, repo, chao, saida)) {
            fprintf(stderr, "Erro ao ler .qry\n");
            destruir_saida(&saida);
            destruir_repo(&repo);
            destruir_chao(&chao);
            
            return 3;
        }

        // Gera SVG e TXT finais
        char base_qry[128];
        basename_sem_ext(qry, base_qry, sizeof base_qry);

        char svg_final[1024], txt_final[1024];
        snprintf(svg_final, sizeof svg_final, "%s/%s-%s.svg", path_out, base_geo, base_qry);
        snprintf(txt_final, sizeof txt_final, "%s/%s-%s.txt", path_out, base_geo, base_qry);

        FILE *fp_svg = fopen(svg_final, "w");
        if (!fp_svg) {
            fprintf(stderr, "Erro: falha ao criar %s\n", svg_final);
            
        } else {
            gerar_svg(saida, chao, fp_svg);
            fclose(fp_svg);
        }

        FILE *fp_txt = fopen(txt_final, "w");
        if (!fp_txt) {
           
            fprintf(stderr, "Erro: falha ao criar %s\n", txt_final);
        } else {
            gerar_txt(saida, fp_txt);
            fclose(fp_txt);
        }
    }

    // Limpeza
    destruir_saida(&saida);
    destruir_repo(&repo);
    destruir_chao(&chao);

    printf("Arquivos gerados com sucesso em %s\n", path_out);

    return 0;
}