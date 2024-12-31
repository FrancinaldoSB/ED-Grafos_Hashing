#include "base.h"

void BellmanFord(int matriz[][N_CONFIGS], int startVerticies, int endVerticies)
{
    int distancias[N_CONFIGS], i, passo, u, v;
    
    for (i = 0; i < N_CONFIGS; i++)
    {
        distancias[i] = INT_MAX;
    }

    distancias[startVerticies] = 0;

    for (passo = 0; passo < N_CONFIGS - 1; passo++)
    {
        for (u = 0; u < N_CONFIGS; u++)
        {
            for (v = 0; v < N_CONFIGS; v++)
            {
                if (matriz[u][v] && distancias[u] != INT_MAX &&
                    distancias[u] + matriz[u][v] < distancias[v])
                {
                    distancias[v] = distancias[u] + matriz[u][v];

                }
            }
        }
    }
    
    printf("\nMenor caminho de %d para %d: %d\n", startVerticies, endVerticies, distancias[endVerticies]);
}

void metrificarTempo(int matriz[][N_CONFIGS])
{
    int startVerticies = 0;
    int endVerticies = N_CONFIGS - 1;

    clock_t startVerticies_time, end_time;
    double time;

    startVerticies_time = clock();

    // Executando Djijkstra 100 vezes para obter a média
    for (int i = 0; i < 100; i++) {
        BellmanFord(matriz, startVerticies, endVerticies);
    }
    end_time = clock();

    time = (double)(end_time - startVerticies_time) / CLOCKS_PER_SEC;

    printf("Tempo gasto - BellmanFord Executando 100 vezes: %lf ms\n", time * 1000);
    printf("\n");
}

int main() {
    int configuracoes[N_CONFIGS][N_DISCOS];
    int matriz[N_CONFIGS][N_CONFIGS];

    gerar_configuracoes(configuracoes, N_CONFIGS);

    matrizAdjacente(configuracoes, matriz);

    metrificarTempo(matriz);

    return 0;
}