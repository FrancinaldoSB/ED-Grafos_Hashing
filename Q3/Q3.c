#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define QUANTIDADE_DE_VERTICES 3
#define INFINITO_NEGATIVO INT_MIN

typedef struct {
    double confiabilidade;
} Aresta;

typedef struct {
    int id;
} Vertice;

typedef struct {
    Vertice vertices[QUANTIDADE_DE_VERTICES];
    Aresta arestas[QUANTIDADE_DE_VERTICES][QUANTIDADE_DE_VERTICES];
} Grafo;

// Inicialização do grafo
void inicializarVerticesDoGrafo(Grafo *grafo) {
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        grafo->vertices[i].id = i;
    }
}

void inicializarArestasDoGrafo(Grafo *grafo) {
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        for (int j = 0; j < QUANTIDADE_DE_VERTICES; j++) {
            grafo->arestas[i][j].confiabilidade = 0;
        }
    }
}

void inicializarGrafoCompleto(Grafo *grafo) {
    inicializarVerticesDoGrafo(grafo);
    inicializarArestasDoGrafo(grafo);
}

// Exibição do grafo
void exibirArestasDoGrafo(const Grafo *grafo) {
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        printf("Vértice %d:\n", grafo->vertices[i].id);
        for (int j = 0; j < QUANTIDADE_DE_VERTICES; j++) {
            printf("  Conexão [%d -> %d]: Confiabilidade = %f\n", i, j, grafo->arestas[i][j].confiabilidade);
        }
    }
}

void exibirGrafoCompleto(const Grafo *grafo) {
    printf("Exibindo as conexões do grafo:\n");
    exibirArestasDoGrafo(grafo);
}

// Popular o grafo
void preencherArestasComConfiabilidadeAleatoria(Grafo *grafo) {
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        for (int j = i + 1; j < QUANTIDADE_DE_VERTICES; j++) {
            double confiabilidade = (double)rand() / RAND_MAX;
            grafo->arestas[i][j].confiabilidade = confiabilidade;
            grafo->arestas[j][i].confiabilidade = confiabilidade;
        }
    }
}

void popularGrafoComValoresAleatorios(Grafo *grafo) {
    preencherArestasComConfiabilidadeAleatoria(grafo);
}

// Algoritmo de Dijkstra
void inicializarParametrosDijkstra(double *distancias, int *visitados, int *predecessor) {
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        distancias[i] = INFINITO_NEGATIVO;
        visitados[i] = 0;
        predecessor[i] = -1;
    }
}

int encontrarVerticeComMaiorConfiabilidade(const double *distancias, const int *visitados) {
    int maiorIndice = -1;
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        if (!visitados[i] && (maiorIndice == -1 || distancias[i] > distancias[maiorIndice])) {
            maiorIndice = i;
        }
    }
    return maiorIndice;
}

void atualizarConfiabilidadesDosVertices(Aresta arestas[QUANTIDADE_DE_VERTICES][QUANTIDADE_DE_VERTICES], double *distancias, int *predecessor, int verticeAtual) {
    for (int v = 0; v < QUANTIDADE_DE_VERTICES; v++) {
        double confiabilidade = arestas[verticeAtual][v].confiabilidade;
        if (confiabilidade > 0 && distancias[verticeAtual] != INFINITO_NEGATIVO &&
            distancias[verticeAtual] + log(confiabilidade) > distancias[v]) {
            distancias[v] = distancias[verticeAtual] + log(confiabilidade);
            predecessor[v] = verticeAtual;
        }
    }
}

void executarDijkstra(int inicio, Aresta arestas[QUANTIDADE_DE_VERTICES][QUANTIDADE_DE_VERTICES], double *distancias, int *predecessor) {
    int visitados[QUANTIDADE_DE_VERTICES];
    inicializarParametrosDijkstra(distancias, visitados, predecessor);
    distancias[inicio] = 0;

    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        int verticeAtual = encontrarVerticeComMaiorConfiabilidade(distancias, visitados);

        bool podeAtualizar = (verticeAtual != -1 && distancias[verticeAtual] != INFINITO_NEGATIVO);

        if (podeAtualizar) {
            visitados[verticeAtual] = 1;
            atualizarConfiabilidadesDosVertices(arestas, distancias, predecessor, verticeAtual);
        }
    }
}

// Exibição do caminho encontrado
void exibirCaminhoDijkstra(int inicio, int fim, const int *predecessor) {
    if (predecessor[fim] == -1) {
        printf("Nenhum caminho foi encontrado entre os vértices %d e %d.\n", inicio, fim);
    } else {
        int caminho[QUANTIDADE_DE_VERTICES];
        int contador = 0;
        for (int v = fim; v != -1; v = predecessor[v]) {
            caminho[contador++] = v;
        }
        printf("Caminho encontrado entre os vértices %d e %d: ", inicio, fim);
        for (int i = contador - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
        }
        printf("\n");
    }
}

// Exibição do menu
void Menu() {
    printf("\nMenu de Operações:\n");
    printf("1. Inicializar Grafo\n");
    printf("2. Popular Grafo\n");
    printf("3. Exibir Grafo\n");
    printf("4. Encontrar Caminho com Dijkstra\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    srand(1);

    Grafo grafo;
    double distancias[QUANTIDADE_DE_VERTICES];
    int predecessor[QUANTIDADE_DE_VERTICES];
    int opcao;

    do {
        Menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inicializarGrafoCompleto(&grafo);
                printf("O grafo foi inicializado com sucesso.\n");
                break;
            case 2:
                popularGrafoComValoresAleatorios(&grafo);
                printf("O grafo foi populado com confiabilidades aleatórias.\n");
                break;
            case 3:
                exibirGrafoCompleto(&grafo);
                break;
            case 4:
                executarDijkstra(0, grafo.arestas, distancias, predecessor);
                exibirCaminhoDijkstra(0, 2, predecessor);
                break;
            case 5:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
