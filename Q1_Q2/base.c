#include "base.h"

void gerar_configuracoes(int configuracoes[][N_DISCOS], int total_config) {
    for (int i = 0; i < total_config; i++) {
        int temp = i;
        for (int j = 0; j < N_DISCOS; j++) {
            configuracoes[i][j] = temp % N_PINOS + 1; // Cada disco pode estar em 1, 2 ou 3
            temp /= N_PINOS;
        }
    }
}

int movimento_valido(int config1[], int config2[]) {
    int movimentos = 0;
    int disco_movido = -1;
    int valido = 1; // Flag para indicar se o movimento é válido

    // Verifica a quantidade de discos movidos
    for (int i = 0; i < N_DISCOS; i++) {
        if (config1[i] != config2[i]) {
            movimentos++;
            if (movimentos > 1) {
                valido = 0; // Mais de um disco movido
            }
            disco_movido = i;
        }
    }

    // Verifica se nenhum disco foi movido ou mais de um foi movido
    if (movimentos == 0 || movimentos > 1) {
        valido = 0; // Nenhum ou mais de um disco movido
    }

    // Validar regras: só o menor disco do pino pode ser movido
    if (valido) {
        int pino_origem = config1[disco_movido];
        int pino_destino = config2[disco_movido];

        // Verifica se há discos menores bloqueando no pino de origem ou no pino de destino
        for (int i = 0; i < N_DISCOS; i++) {
            if (i != disco_movido) {
                if (config1[i] == pino_origem && i < disco_movido) {
                    valido = 0; // Há discos menores bloqueando no pino de origem
                }
                if (config2[i] == pino_destino && i < disco_movido) {
                    valido = 0; // Há discos menores no pino de destino
                }
            }
        }
    }

    return valido; // Retorna o resultado final, se o movimento é válido (1) ou não (0)
}

void matrizAdjacente(int configuracoes[N_CONFIGS][N_DISCOS], int matriz[N_CONFIGS][N_CONFIGS]) {
    for (int li = 0; li < N_CONFIGS; li++) {
        for (int col = 0; col < N_CONFIGS; col++) {
            if (movimento_valido(configuracoes[li], configuracoes[col])) {
                matriz[li][col] = 1; // Custo do movimento é 1
            } else {
                matriz[li][col] = 0; // Sem conexão
            }
        }
    }
}