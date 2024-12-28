#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>   

#define N_DISCOS 4
#define N_PINOS 3
#define N_CONFIGS 81



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

void FillMatrizAdj(int configuracoes[N_CONFIGS][N_DISCOS], int matriz[N_CONFIGS][N_CONFIGS]) {
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

void Dijkstra(int matriz[][N_CONFIGS], int startVerticies, int endVerticies)
{
    int distancias[N_CONFIGS];
    int visitados[N_CONFIGS], i, count, v;

    for (i = 0; i < N_CONFIGS; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    distancias[startVerticies] = 0;

    for (count = 0; count < N_CONFIGS - 1; count++)
    {
        int u = -1;

        for (i = 0; i < N_CONFIGS; i++)
        {
            if (!visitados[i] && (u == -1 || distancias[i] < distancias[u]))
            {
                u = i;
            }
        }

        visitados[u] = 1;

        for (v = 0; v < N_CONFIGS; v++)
        {
            if (!visitados[v] && matriz[u][v] && distancias[u] != INT_MAX &&
                distancias[u] + matriz[u][v] < distancias[v])
            {
                distancias[v] = distancias[u] + matriz[u][v];
            }
        }
    }

    printf("Menor caminho de %d para %d: %d\n", startVerticies, endVerticies, distancias[endVerticies]);
}

int encontrar_configuracao(int configuracoes[][N_DISCOS], int pino_inicial) {
    for (int i = 0; i < N_CONFIGS; i++) {
        int valido = 1;
        for (int j = 0; j < N_DISCOS; j++) {
            if (configuracoes[i][j] != pino_inicial) {
                valido = 0;
                break;
            }
        }
        if (valido) return i;
    }
    return -1; // Não encontrado
}

void metrificarTempo(int matriz[][N_CONFIGS])
{
    int startVerticies = 0;
    int endVerticies = N_CONFIGS - 1;

    clock_t startVerticies_time, end_time;
    double time;

    startVerticies_time = clock();

    // Executando Djijkstra 10 vezes para obter a média
    for (int i = 0; i < 100; i++) {
        Dijkstra(matriz, startVerticies, endVerticies);
    }
    end_time = clock();

    time = (double)(end_time - startVerticies_time) / CLOCKS_PER_SEC;

    printf("Tempo gasto - Dijkstra Executando 100 vezes: %lf ms\n", time * 1000);
    printf("\n");
}

int main() {
    int total_config = N_CONFIGS; // Total de configurações possíveis
    int configuracoes[N_CONFIGS][N_DISCOS];
    int matriz_adj[N_CONFIGS][N_CONFIGS];

    // Exibir Matriz de Adjacência
    gerar_configuracoes(configuracoes, total_config);

    FillMatrizAdj(configuracoes, matriz_adj);
        
    metrificarTempo(matriz_adj);

    return 0;
}