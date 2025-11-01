#include "calc.h"
#include "forma.h"
#include "saida.h"

#include <stdio.h>
#include <stdbool.h>

static const char* tipo_nome(char n){
    switch (n){
        case 'c': return "circulo";
        case 'r': return "retangulo";
        case 't': return "texto";
        case 'l': return "linha";
        default:  return "forma";
    }
}

bool calc(CHAO chao, ARENA arena, SAIDA saida){
    if (!chao || !arena || !saida) return false;

    double area_round = 0.0;
    int verifs = 0, esmagadas_round = 0, clonadas_round = 0;

    while (1){
        FORMA I = rmv_arena(arena);
        if (!I) break; 
        FORMA J = rmv_arena(arena);
        if (!J) {
            add_chao(chao, I);  
            break;
        }

        double aI = area_forma(I);
        double aJ = area_forma(J);

        char buf[160];
        snprintf(buf, sizeof buf,
                 "verif %d: I(id=%d, a=%.2f) x J(id=%d, a=%.2f)",
                 ++verifs, getI_forma(I), aI, getI_forma(J), aJ);
        add_texto_saida(saida, buf);

        if (sobrepoe_formas(I, J)){
            add_texto_saida(saida, "sobreposicao: sim");

            if (aI < aJ){
                char msg[128];
                snprintf(msg, sizeof msg,
                         "acao: %s %d esmagado; %s %d volta ao chao",
                         tipo_nome(getTipo_forma(I)), getI_forma(I),
                         tipo_nome(getTipo_forma(J)), getI_forma(J));
                add_texto_saida(saida, msg);

                somar_pontuacao(saida, aI);
                area_round += aI;
                registrar_esmagada(saida);
                ++esmagadas_round;

                marcar_esmagada(saida, I);
                destruir_forma(&I);
                add_chao(chao, J);
                pula_linha(saida);
            } else { 
                trocar_cores(I, J);

               
                FORMA clone = clonar_forma(I);

                
                add_chao(chao, I);
                add_chao(chao, J);

                char msg[160];
                if (clone){
                    inverter_cores(clone);
                    add_chao(chao, clone);
                    registrar_clone(saida);
                    ++clonadas_round;

                    snprintf(msg, sizeof msg,
                             "acao: troca cores de J; %s %d clonado (cores invertidas); "
                             "I e J voltam; clone volta depois",
                             tipo_nome(getTipo_forma(I)), getI_forma(I));
                } else {
                    snprintf(msg, sizeof msg,
                             "acao: troca cores de J; falha ao clonar %s %d; apenas I e J voltam",
                             tipo_nome(getTipo_forma(I)), getI_forma(I));
                }
                add_texto_saida(saida, msg);
                pula_linha(saida);
            }
        } else {
            
            add_texto_saida(saida, "sobreposicao: nao");

            char msg[160];
            snprintf(msg, sizeof msg,
                     "acao: %s %d e %s %d voltam ao chao na mesma ordem",
                     tipo_nome(getTipo_forma(I)), getI_forma(I),
                     tipo_nome(getTipo_forma(J)), getI_forma(J));
            add_texto_saida(saida, msg);

            add_chao(chao, I);
            add_chao(chao, J);
            pula_linha(saida);
        }
    }

    
    {
        char sum[96];
        snprintf(sum, sizeof sum, "Area esmagada (round): %.2f", area_round);
        add_texto_saida(saida, sum);

        snprintf(sum, sizeof sum, "Pontuacao total: %.2f", get_pontuacao(saida));
        add_texto_saida(saida, sum);

        snprintf(sum, sizeof sum, "Verificacoes: %d | Esmagadas: %d | Clonadas: %d",
                 verifs, esmagadas_round, clonadas_round);
        add_texto_saida(saida, sum);

        pula_linha(saida);
    }

    return true;
}
