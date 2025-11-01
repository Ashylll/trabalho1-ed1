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
            char msg[128];
            snprintf(msg, sizeof msg,
                    "Número de elementos ímpar: %s %d não tem par para verificar (retorna ao chão)",
                     tipo_nome(getTipo_forma(I)), getI_forma(I));
            add_texto_saida(saida, msg);

            add_chao(chao, I);
            pula_linha(saida);
            break;
        }

        double aI = area_forma(I);
        double aJ = area_forma(J);

        char buf[160];
        snprintf(buf, sizeof buf,
                 "verif %d: I(id = %d, área = %.2f) x J(id = %d, área = %.2f)",
                 ++verifs, getI_forma(I), aI, getI_forma(J), aJ);
        add_texto_saida(saida, buf);

        if (sobrepoe_formas(I, J)){
            add_texto_saida(saida, "Sobreposição: sim");

            if (aI < aJ){
                char msg[128];
                snprintf(msg, sizeof msg,
                         "Ação: %s %d esmagado; %s %d volta ao chão",
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
                             "Ação: troca cores de J; %s %d clonado (cores invertidas); "
                             "I e J voltam; clone volta depois",
                             tipo_nome(getTipo_forma(I)), getI_forma(I));
                } else {
                    snprintf(msg, sizeof msg,
                             "Ação: troca cores de J; falha ao clonar %s %d; apenas I e J voltam",
                             tipo_nome(getTipo_forma(I)), getI_forma(I));
                }
                add_texto_saida(saida, msg);
                pula_linha(saida);
            }
        } else {
            
            add_texto_saida(saida, "Sobreposição: não");

            char msg[160];
            snprintf(msg, sizeof msg,
                     "Ação: %s %d e %s %d voltam ao chão na mesma ordem",
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
        snprintf(sum, sizeof sum, "Área esmagada (rodada): %.2f", area_round);
        add_texto_saida(saida, sum);

        snprintf(sum, sizeof sum, "Pontuação total: %.2f", get_pontuacao(saida));
        add_texto_saida(saida, sum);

        snprintf(sum, sizeof sum, "Verificações: %d | Esmagadas: %d | Clonadas: %d",
                 verifs, esmagadas_round, clonadas_round);
        add_texto_saida(saida, sum);

        pula_linha(saida);
    }

    return true;
}
