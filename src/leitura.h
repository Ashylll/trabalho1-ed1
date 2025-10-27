#ifndef LEITURA_H
#define LEITURA_H

#include "saida.h"
#include "chao.h"
#include "repo.h"

#include <stdbool.h>

/*
    leitura.h
    Módulo responsável pela leitura dos arquivos de entrada .geo e . qry

*/

/// @brief realiza a leitura do arquivo .geo e cria as formas correspondentes
/// @param path_geo caminho para o arquivo .geo
/// @param chao chão onde as formas são armazenadas 
/// @param saida estrutura de saída para registrar as formas criadas
/// @return true se o arquivo foi lido com sucesso; false se falhou ao abrir ou a ler
bool ler_geo(const char *path_geo, CHAO chao, SAIDA saida);

/// @brief realiza a leitura do arquivo .qry e executa os comandos correspondentes
/// @param path_qry caminho para o arquivo .qry
/// @param repo repositório onde os disparadores e os carregadores são guardados
/// @param chao chão onde as formas são armazenadas
/// @param saida estrutura de saída para registrar formas criadas
/// @return true se o arquivo foi lido com sucess; false se falhou ao abrir ou a ler
bool ler_qry(const char *path_qry, REPO repo, CHAO chao, SAIDA saida);



#endif