#ifndef Q4_H
#define Q4_H

/*----------------------------------------------------------------------------------------------------------*/

/* Bibliotecas necessárias */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*----------------------------------------------------------------------------------------------------------*/

/* Definição de constantes */

#define TAM_MAT 6

/*----------------------------------------------------------------------------------------------------------*/

/* Estruturas */

typedef struct {
    char matricula[TAM_MAT + 1];
    char nome[TAM_MAT + 1];
    char funcao[TAM_MAT + 1];
    float salario;
} Funcionario;

typedef struct {
    int ocupado;
    Funcionario funcionario;
} EntradaHash;

/*----------------------------------------------------------------------------------------------------------*/

/* Protótipos de funções */

Funcionario criarFuncionario();

void testarHash(int (*calcularHash)(char[], int), int (*tratarColisao)(int, char[], int), int tam_hash);

// A
int hash1(char matricula[], int tam_hash);

int tratarColisaoHash1(int hash, char matricula[], int tam_hash);

// B
int hash2(char matricula[], int tam_hash);

int tratarColisaoHash2(int hash, char matricula[], int tam_hash);

/*----------------------------------------------------------------------------------------------------------*/

#endif
