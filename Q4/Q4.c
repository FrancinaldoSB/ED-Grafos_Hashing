#include "Q4.h"

Funcionario criarFuncionario() {
    int numero = rand() % 100000;
    Funcionario funcionario;
    funcionario.salario = (float)numero;

    for (int i = TAM_MAT - 1; i >= 0; i--, numero /= 10) {
        int digito_atual = numero % 10;
        funcionario.matricula[i] = '0' + digito_atual;
        funcionario.nome[i] = '0' + digito_atual;
        funcionario.funcao[i] = '0' + digito_atual;
    }

    funcionario.matricula[TAM_MAT] = '\0';
    funcionario.nome[TAM_MAT] = '\0';
    funcionario.funcao[TAM_MAT] = '\0';

    if (funcionario.matricula[0] == '0') {
        funcionario.matricula[0] = '1';
    }

    return funcionario;
}

int charParaInt(char c) {
    return c - '0';
}

void inicializarTabelaHash(EntradaHash* tabela_hash, int tam_hash) {
    for (int i = 0; i < tam_hash; i++) {
        tabela_hash[i].ocupado = 0;
    }
}

int hash1(char matricula[], int tam_hash) {
    printf("Tam_hash: %d\n", tam_hash);
    int valorInteiro = 0;

    for (int i = 0; i < TAM_MAT; i += 2) {
        valorInteiro = (valorInteiro * 10) + charParaInt(matricula[i]);
    }

    return valorInteiro % tam_hash;
}

int hash2(char matricula[], int tam_hash) {
    printf("Tam_hash: %d\n", tam_hash);
    int parte1 = (charParaInt(matricula[0]) * 100) + (charParaInt(matricula[2]) * 10) + charParaInt(matricula[4]);
    int parte2 = (charParaInt(matricula[1]) * 100) + (charParaInt(matricula[3]) * 10) + charParaInt(matricula[5]);

    int soma_partes = parte1 + parte2;
    return soma_partes % tam_hash;
}

int tratarColisaoHash1(int hash, char matricula[], int tam_hash) {
    printf("Tam_hash: %d\n", tam_hash);
    char primeiro_caractere[2] = {matricula[0], '\0'};
    return (hash + atoi(primeiro_caractere)) % tam_hash;
}

int tratarColisaoHash2(int hash, char matricula[], int tam_hash) {
    printf("Tam_hash: %d\n", tam_hash);
    (void)matricula; // Ignorar matricula no tratamento
    return (hash + 7) % tam_hash;
}

int inserirFuncionario(EntradaHash* tabela_hash, int hash, char matricula[], Funcionario funcionario, int (*tratarColisao)(int, char[], int), int tam_hash) {
    int colisoes = 0;
    int novo_hash = hash;

    while (tabela_hash[novo_hash].ocupado && colisoes < tam_hash) {
        colisoes++;
        novo_hash = tratarColisao(novo_hash, matricula, tam_hash);
    }

    if (!tabela_hash[novo_hash].ocupado) {
        tabela_hash[novo_hash].ocupado = 1;
        tabela_hash[novo_hash].funcionario = funcionario;
    }

    return colisoes;
}

void testarHash(int (*calcularHash)(char[], int), int (*tratarColisao)(int, char[], int), int tam_hash) {
    EntradaHash tabela_hash[tam_hash];
    inicializarTabelaHash(tabela_hash, tam_hash);

    int total_colisoes = 0;
    clock_t tempo_total = 0;

    for (int i = 0; i < 1000; i++) {
        Funcionario funcionario = criarFuncionario();

        clock_t inicio = clock();
        int hash = calcularHash(funcionario.matricula, tam_hash);
        total_colisoes += inserirFuncionario(tabela_hash, hash, funcionario.matricula, funcionario, tratarColisao, tam_hash);
        clock_t fim = clock();

        tempo_total += (fim - inicio);
    }

    printf("Tempo para inserção: %f segundos\n", ((double)tempo_total / CLOCKS_PER_SEC));
    printf("Total de colisoes: %d\n", total_colisoes);
}
