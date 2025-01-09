#include "Q4.h"

Funcionario criarFuncionario() {
    int numero = rand() % 100000;
    Funcionario funcionario;
    funcionario.salario = (float) numero;

    for (int i = 0; i < TAM_MAT; i++, numero /= 10)
    {
        int digito_atual = numero % 10;
        funcionario.matricula[i] = (char) digito_atual + '0';
        funcionario.nome[i] = (char) digito_atual + '0';
        funcionario.funcao[i] = (char) digito_atual + '0';
    }

    funcionario.matricula[TAM_MAT] = '\0';
    funcionario.nome[TAM_MAT] = '\0';
    funcionario.funcao[TAM_MAT] = '\0';

    // Evitar matriculas comecando com 0, motivo: hash_1
    if (funcionario.matricula[0] == '0')
        funcionario.matricula[0] = '1';

    return funcionario;
}

int charParaInt(char c) {
    return (int) c - '0';
}

void inicializarTabelaHash(EntradaHash* tabela_hash, int tam_hash) {
    for (int i = 0; i < tam_hash; i++) {
        tabela_hash[i].ocupado = -1;
    }
}

int hash1(char matricula[], int tam_hash)
{
  char aux[TAM_MAT];

  aux[0] = matricula[TAM_MAT - 2];
  aux[1] = matricula[TAM_MAT - 1];
  for (int index_matricula_velha = 0, idx_matricula_new = 2;
       index_matricula_velha < TAM_MAT - 2;
       index_matricula_velha++, idx_matricula_new++) 
    aux[idx_matricula_new] = matricula[index_matricula_velha];

  int valorInteiro = atoi((char[]){aux[1], aux[3], aux[5]});
  return valorInteiro % tam_hash;
}

int hash2(char matricula[], int tam_hash)
{
    int parte1 = (charParaInt(matricula[1 - 1]) * 100) + (charParaInt(matricula[3 - 1]) * 10) + (charParaInt(matricula[6 - 1]));
    int parte2 = (charParaInt(matricula[2 - 1]) * 100) + (charParaInt(matricula[4 - 1]) * 10) + (charParaInt(matricula[5 - 1]));

    int soma_partes = parte1 + parte2;
    return soma_partes % tam_hash;
}

int tratarColisaoHash1(int hash, char matricula[], int tam_hash) {
    char primeiro_caractere[2] = {matricula[0], '\0'};
    return (hash + atoi(primeiro_caractere));
}

int tratarColisaoHash2(int hash, char matricula[], int tam_hash) {
    (void)matricula; // Ignorar matricula no tratamento
    return (hash + 7);
}

int inserirFuncionario(EntradaHash* tabela_hash, int hash, char matricula[], Funcionario funcionario, int (*tratarColisao)(int, char[], int), int tam_hash) {
    int colisao = 0, inseriu = 0;
    int novo_hash = hash;

    while (novo_hash < tam_hash && inseriu == 0) { // Evita loops infinitos limitando o número de colisões
        if (tabela_hash[novo_hash].ocupado == -1) { 
            tabela_hash[novo_hash].ocupado = novo_hash; // Marca como ocupado
            tabela_hash[novo_hash].funcionario = funcionario;
            inseriu = 1; // Marca a inserção como bem-sucedida
        } else {
            colisao++; // Incrementa o número de colisões
            novo_hash = tratarColisao(novo_hash, matricula, tam_hash); // Calcula novo índice
        }
    }

    if (inseriu == 0)
    {
        tabela_hash[hash].ocupado = hash;
        tabela_hash[hash].funcionario = funcionario;
    }

    return colisao; 
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
