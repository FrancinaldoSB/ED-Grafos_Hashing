#include "base.h"

/**
 * @brief Função de Djikstra para encontrar o menor caminho entre dois vértices
 * 
 * @param matriz Matriz de adjacência
 * @param startVerticies Vértice de origem
 * @param endVerticies Vértice de destino
 * @return void
 */
void Dijkstra(int matriz[][N_CONFIGS], int startVerticies, int endVerticies){
    int distancias[N_CONFIGS], visitados[N_CONFIGS], i, count, v;

    for(i = 0; i < N_CONFIGS; i++){
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    distancias[startVerticies] = 0;

    for (count = 0; count < N_CONFIGS - 1; count++){
        int u = -1;

        for (i = 0; i < N_CONFIGS; i++){
            if (!visitados[i] && (u == -1 || distancias[i] < distancias[u]))
                u = i;
        }

        visitados[u] = 1;

        for (v = 0; v < N_CONFIGS; v++){
            if (!visitados[v] && matriz[u][v] && distancias[u] != INT_MAX && distancias[u] + matriz[u][v] < distancias[v])
                distancias[v] = distancias[u] + matriz[u][v];
        }
    }
}

/**
 * @brief Função para gerar todas as configurações possíveis
 * 
 * @param configuracoes Matriz de configurações
 * @param total_config Total de configurações possíveis
 * @return void
 */
void metrificarTempo(int matriz[][N_CONFIGS]){
    int startVerticies = 0;
    int endVerticies = N_CONFIGS - 1;

    clock_t startVerticies_time, end_time;
    double time;

    startVerticies_time = clock();

    // Executando Djijkstra 100 vezes para obter a média
    for (int i = 0; i < 1000; i++)
        Dijkstra(matriz, startVerticies, endVerticies);
    end_time = clock();

    time = (double)(end_time - startVerticies_time) * 1000 / CLOCKS_PER_SEC;

    printf("%lf\n", time);
}

int main() {
    int total_config = N_CONFIGS; // Total de configurações possíveis
    int configuracoes[N_CONFIGS][N_DISCOS];
    int matriz_adj[N_CONFIGS][N_CONFIGS], i;

    // Exibir matriz de adjacência
    gerar_configuracoes(configuracoes, total_config);

    matrizAdjacente(configuracoes, matriz_adj);
        
    printf("Tempo de execucao do algoritmo de Djikstra: \n");
    for(i = 0; i < 30; i++)
        metrificarTempo(matriz_adj);
    return 0;
}