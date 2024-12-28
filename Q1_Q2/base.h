#ifndef base_H
#define base_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>   

#define N_DISCOS 4
#define N_PINOS 3
#define N_CONFIGS 81


void gerar_configuracoes(int configuracoes[][N_DISCOS], int total_config);

void matrizAdjacente(int configuracoes[N_CONFIGS][N_DISCOS], int matriz[N_CONFIGS][N_CONFIGS]);


#endif