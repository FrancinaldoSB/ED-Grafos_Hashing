#ifndef Q3_H
#define Q3_H

/*----------------------------------------------------------------------------------------------------------*/

/* Bibliotecas necessárias */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>

/*----------------------------------------------------------------------------------------------------------*/

/* Definição de constantes */

#define QUANTIDADE_DE_VERTICES 3
#define INFINITO_NEGATIVO INT_MIN

/*----------------------------------------------------------------------------------------------------------*/

/* Estruturas */

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

/*----------------------------------------------------------------------------------------------------------*/

/* Protótipos de funções */

void iniVertices(Grafo *grafo);
void iniArestas(Grafo *grafo);
void iniGrafo(Grafo *grafo);
void exibirArestas(const Grafo *grafo);
void exibirGrafo(const Grafo *grafo);
void preencherArestas(Grafo *grafo);
void iniDjikstra(double *distancias, int *visitados, int *predecessor);
int maiorConfiabilidade(const double *distancias, const int *visitados);
void attConfiabilidade(Aresta arestas[QUANTIDADE_DE_VERTICES][QUANTIDADE_DE_VERTICES], double *distancias, int *predecessor, int verticeAtual);
void Djikstra(int inicio, Aresta arestas[QUANTIDADE_DE_VERTICES][QUANTIDADE_DE_VERTICES], double *distancias, int *predecessor);
void exibirDjikstra(int inicio, int fim, const int *predecessor);

/*----------------------------------------------------------------------------------------------------------*/

#endif