#include "base.h"

/**
 * @brief Função de Bellman-Ford para encontrar o menor caminho entre dois vértices
 * 
 * @param matriz Matriz de adjacência
 * @param startVerticies Vértice de origem
 * @param endVerticies Vértice de destino
 * @return void
 */
void BellmanFord(int matriz[][N_CONFIGS], int startVerticies, int endVerticies){
    int distancias[N_CONFIGS], i, passo, u, v;
    
    for (i = 0; i < N_CONFIGS; i++)
        distancias[i] = INT_MAX;

    distancias[startVerticies] = 0;

    for (passo = 0; passo < N_CONFIGS - 1; passo++){
        for (u = 0; u < N_CONFIGS; u++){
            for (v = 0; v < N_CONFIGS; v++){
                if (matriz[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz[u][v] < distancias[v])
                    distancias[v] = distancias[u] + matriz[u][v];
            }
        }
    }
    printf("Caminho mais curto entre %d e %d: %d\n", startVerticies, endVerticies, distancias[endVerticies]);
}

/**
 * @brief Função para medir o tempo de execução do algoritmo
 * 
 * @param matriz Matriz de adjacência
 * @return void
 */
void metrificarTempo(int matriz[][N_CONFIGS]){
    int startVerticies = 0, endVerticies = N_CONFIGS - 1, i;

    clock_t startVerticies_time, end_time;
    double time;

    startVerticies_time = clock();

    for(i = 0; i < 1000; i++)
        BellmanFord(matriz, startVerticies, endVerticies);
    end_time = clock();

    time = (double)(end_time - startVerticies_time) * 1000 / CLOCKS_PER_SEC;

    printf("%lf\n", time);
}

int main(){
    int configuracoes[N_CONFIGS][N_DISCOS];
    int matriz[N_CONFIGS][N_CONFIGS], i;

    gerar_configuracoes(configuracoes, N_CONFIGS);

    matrizAdjacente(configuracoes, matriz);

    printf("Tempo de execucao do algoritmo de Bellman-Ford:\n");
    for(i = 0; i < 30; i++)
        metrificarTempo(matriz);

    return 0;
}