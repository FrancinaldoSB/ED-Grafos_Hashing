#include "base.h"

int main() {
    int configuracoes[N_CONFIGS][N_DISCOS];
    int matriz[N_CONFIGS][N_CONFIGS];

    gerar_configuracoes(configuracoes, N_CONFIGS);

    matrizAdjacente(configuracoes, matriz);

    return 0;
}