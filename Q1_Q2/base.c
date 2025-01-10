#include "base.h"

/**
 * @brief Função para gerar todas as configurações possíveis, com base no total de configurações
 * 
 * @param configuracoes Matriz de configurações
 * @param total_config Total de configurações possíveis
 * @return void
 */
void gerar_configuracoes(int configuracoes[][N_DISCOS], int total_config) {
    for (int i = 0; i < total_config; i++) {
        int temp = i;
        for (int j = 0; j < N_DISCOS; j++) {
            configuracoes[i][j] = temp % N_PINOS + 1; // Cada disco pode estar em 1, 2 ou 3
            temp /= N_PINOS;
        }
    }
}

/**
 * @brief Função para verificar se o movimento é válido
 * 
 * @param config1 Configuração 1
 * @param config2 Configuração 2
 * @return int Retorna 1 se o movimento é válido e 0 se não for
 */
int movimento_valido(int config1[], int config2[]){
    int movimentos = 0, disco_movido = -1, valido = 1;

    // Verifica a quantidade de discos movidos
    for (int i = 0; i < N_DISCOS; i++) {
        if (config1[i] != config2[i]) {
            movimentos++;
            if (movimentos > 1)
                valido = 0;
            disco_movido = i;
        }
    }

    if (movimentos == 0 || movimentos > 1)
        valido = 0;

    // Validar regras: só o menor disco do pino pode ser movido
    if (valido) {
        int pino_origem = config1[disco_movido];
        int pino_destino = config2[disco_movido];

        // Verifica se há discos menores bloqueando no pino de origem ou no pino de destino
        for (int i = 0; i < N_DISCOS; i++) {
            if (i != disco_movido) {
                if (config1[i] == pino_origem && i < disco_movido)
                    valido = 0;
                if (config2[i] == pino_destino && i < disco_movido)
                    valido = 0;
            }
        }
    }

    return valido;
}

/**
 * @brief Função para gerar a matriz de adjacência com base nas configurações
 * 
 * @param configuracoes Matriz de configurações
 * @param matriz Matriz de adjacência
 * @return void
 */
void matrizAdjacente(int configuracoes[N_CONFIGS][N_DISCOS], int matriz[N_CONFIGS][N_CONFIGS]) {
    for(int li = 0; li < N_CONFIGS; li++){
        for(int col = 0; col < N_CONFIGS; col++){
            if (movimento_valido(configuracoes[li], configuracoes[col]))
                matriz[li][col] = 1;
            else
                matriz[li][col] = 0;
        }
    }
}