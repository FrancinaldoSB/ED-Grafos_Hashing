#include "Q3.h"

/**
 * @brief Função para inicializar os vértices do grafo com seus respectivos IDs
 * 
 * @param grafo Grafo
 * @return void
 */
void iniVertices(Grafo *grafo){
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++)
        grafo->vertices[i].id = i;
}

/**
 * @brief Função para inicializar as arestas do grafo com confiabilidade 0
 * 
 * @param grafo Grafo com seus vértices e arestas
 * @return void
 */
void iniArestas(Grafo *grafo){
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        for (int j = 0; j < QUANTIDADE_DE_VERTICES; j++)
            grafo->arestas[i][j].confiabilidade = 0;
    }
}

/**
 * @brief Função para inicializar o grafo completo
 * 
 * @param grafo Grafo com seus vértices e arestas
 * @return void
 */
void iniGrafo(Grafo *grafo){
    iniVertices(grafo);
    iniArestas(grafo);
}

/**
 * @brief Função para exibir as arestas do grafo com suas respectivas confiabilidades
 * 
 * @param grafo Grafo com seus vértices e arestas
 * @return void
 */
void exibirArestas(const Grafo *grafo){
    for(int i = 0; i < QUANTIDADE_DE_VERTICES; i++){
        printf("Vertice %d:\n", grafo->vertices[i].id);
        for(int j = 0; j < QUANTIDADE_DE_VERTICES; j++)
            printf("  Conexão [%d -> %d]: Confiabilidade = %f\n", i, j, grafo->arestas[i][j].confiabilidade);
    }
}

/**
 * @brief Função para exibir o grafo completo
 * 
 * @param grafo Grafo com seus vértices e arestas
 * @return void
 */
void exibirGrafo(const Grafo *grafo){
    printf("Exibindo as conexoes do grafo:\n");
    exibirArestas(grafo);
}

/**
 * @brief Função para preencher as arestas do grafo com confiabilidades aleatórias
 * 
 * @param grafo Grafo com seus vértices e arestas
 * @return void
 */
void preencherArestas(Grafo *grafo){
    for(int i = 0; i < QUANTIDADE_DE_VERTICES; i++){
        for(int j = i + 1; j < QUANTIDADE_DE_VERTICES; j++){
            double confiabilidade = (double)rand() / RAND_MAX;
            grafo->arestas[i][j].confiabilidade = confiabilidade;
            grafo->arestas[j][i].confiabilidade = confiabilidade;
        }
    }
}

/**
 * @brief Função para inicializar os parâmetros do algoritmo de Dijkstra
 * 
 * @param distancias Vetor de distâncias
 * @param visitados Vetor de visitados
 * @param predecessor Vetor de predecessores
 * @return void
 */
void iniDjikstra(double *distancias, int *visitados, int *predecessor) {
    for(int i = 0; i < QUANTIDADE_DE_VERTICES; i++){
        distancias[i] = INFINITO_NEGATIVO;
        visitados[i] = 0;
        predecessor[i] = -1;
    }
}

/**
 * @brief Função para encontrar o vértice com a maior confiabilidade
 * 
 * @param distancias Vetor de distâncias
 * @param visitados Vetor de visitados
 * @return int
 */
int maiorConfiabilidade(const double *distancias, const int *visitados) {
    int maiorIndice = -1;
    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        if (!visitados[i] && (maiorIndice == -1 || distancias[i] > distancias[maiorIndice]))
            maiorIndice = i;
    }
    return maiorIndice;
}

/**
 * @brief Função para atualizar as confiabilidades dos vértices do grafo
 * 
 * @param arestas Matriz de arestas
 * @param distancias Vetor de distâncias
 * @param predecessor Vetor de predecessores
 * @param verticeAtual Vértice atual
 * @return void
 */
void attConfiabilidade(Aresta arestas[QUANTIDADE_DE_VERTICES][QUANTIDADE_DE_VERTICES], double *distancias, int *predecessor, int verticeAtual) {
    for (int v = 0; v < QUANTIDADE_DE_VERTICES; v++) {
        double confiabilidade = arestas[verticeAtual][v].confiabilidade;
        if (confiabilidade > 0 && distancias[verticeAtual] != INFINITO_NEGATIVO &&
            distancias[verticeAtual] + log(confiabilidade) > distancias[v]) {
            distancias[v] = distancias[verticeAtual] + log(confiabilidade);
            predecessor[v] = verticeAtual;
        }
    }
}

/**
 * @brief Função para executar o algoritmo de Dijkstra
 * 
 * @param inicio Vértice de início
 * @param arestas Matriz de arestas
 * @param distancias Vetor de distâncias
 * @param predecessor Vetor de predecessores
 * @return void
 */
void Djikstra(int inicio, Aresta arestas[QUANTIDADE_DE_VERTICES][QUANTIDADE_DE_VERTICES], double *distancias, int *predecessor) {
    int visitados[QUANTIDADE_DE_VERTICES];
    iniDjikstra(distancias, visitados, predecessor);
    distancias[inicio] = 0;

    for (int i = 0; i < QUANTIDADE_DE_VERTICES; i++) {
        int verticeAtual = maiorConfiabilidade(distancias, visitados);

        bool podeAtualizar = (verticeAtual != -1 && distancias[verticeAtual] != INFINITO_NEGATIVO);

        if (podeAtualizar) {
            visitados[verticeAtual] = 1;
            attConfiabilidade(arestas, distancias, predecessor, verticeAtual);
        }
    }
}

/**
 * @brief Função para exibir o caminho encontrado pelo algoritmo de Dijkstra
 * 
 * @param inicio Vértice de início
 * @param fim Vértice de fim
 * @param predecessor Vetor de predecessores
 * @return void
 */
void exibirDjikstra(int inicio, int fim, const int *predecessor){
    if (predecessor[fim] == -1)
        printf("Nenhum caminho foi encontrado entre os vertices %d e %d.\n", inicio, fim);
    else{
        int caminho[QUANTIDADE_DE_VERTICES];
        int contador = 0;
        for(int v = fim; v != -1; v = predecessor[v])
            caminho[contador++] = v;
        printf("Caminho encontrado entre os vertices %d e %d: ", inicio, fim);
        for(int i = contador - 1; i >= 0; i--)
            printf("%d ", caminho[i]);
        printf("\n");
    }
}