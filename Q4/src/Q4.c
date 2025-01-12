#include "Q4.h"

/**
 * @brief Função para criar um funcionário com matrícula, nome, função e salário aleatórios
 * 
 * @return Funcionario
 */
Funcionario criarFuncionario(){
    int numero = rand() % 100000, i;
    Funcionario funcionario;
    funcionario.salario = (float) numero;

    for(i = 0; i < TAM_MAT; i++, numero /= 10){
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

/**
 * @brief Função para converter um caractere numérico em inteiro
 * 
 * @param c Caractere numérico
 * @return int
 */
int charParaInt(char c) {
    return (int) c - '0';
}

/**
 * @brief Função para inicializar a tabela hash
 * 
 * @param tabela_hash Tabela hash
 * @param tam_hash Tamanho da tabela hash
 * @return void
 */
void inicializarTabelaHash(EntradaHash* tabela_hash, int tam_hash){
    for (int i = 0; i < tam_hash; i++)
        tabela_hash[i].ocupado = -1;
}

/**
 * @brief Função para calcular o hash 1
 * 
 * @param matricula Matrícula do funcionário
 * @param tam_hash Tamanho da tabela hash
 * @return int
 */
int hash1(char matricula[], int tam_hash){
    char aux[TAM_MAT];

    aux[0] = matricula[TAM_MAT - 2];
    aux[1] = matricula[TAM_MAT - 1];
    for(int iMatVelha = 0, iMatNova = 2; iMatVelha < TAM_MAT - 2; iMatVelha++, iMatNova++) 
        aux[iMatNova] = matricula[iMatVelha];

    int valorInteiro = atoi((char[]){aux[1], aux[3], aux[5]});
    return valorInteiro % tam_hash;
}

/**
 * @brief Função para calcular o hash 2
 * 
 * @param matricula Matrícula do funcionário
 * @param tam_hash Tamanho da tabela hash
 * @return int
 */
int hash2(char matricula[], int tam_hash){
    int parte1 = (charParaInt(matricula[1 - 1]) * 100) + (charParaInt(matricula[3 - 1]) * 10) + (charParaInt(matricula[6 - 1]));
    int parte2 = (charParaInt(matricula[2 - 1]) * 100) + (charParaInt(matricula[4 - 1]) * 10) + (charParaInt(matricula[5 - 1]));

    int soma_partes = parte1 + parte2;
    return soma_partes % tam_hash;
}

/**
 * @brief Função para tratar colisões no hash 1
 * 
 * @param hash Valor do hash
 * @param matricula Matrícula do funcionário
 * @param tam_hash Tamanho da tabela hash
 * @return int
 */
int tratarColisaoHash1(int hash, char matricula[], int tam_hash) {
    char primeiro_caractere[2] = {matricula[0], '\0'};
    return (hash + atoi(primeiro_caractere));
}

/**
 * @brief Função para tratar colisões no hash 2
 * 
 * @param hash Valor do hash
 * @param matricula Matrícula do funcionário
 * @param tam_hash Tamanho da tabela hash
 * @return int
 */
int tratarColisaoHash2(int hash, char matricula[], int tam_hash) {
    (void)matricula; // Ignorar matricula no tratamento
    return (hash + 7);
}

/**
 * @brief Função para inserir um funcionário na tabela hash
 * 
 * @param tabela_hash Tabela hash
 * @param hash Valor do hash
 * @param matricula Matrícula do funcionário
 * @param funcionario Funcionário
 * @param tratarColisao Função para tratar colisões
 * @param tam_hash Tamanho da tabela hash
 * @return int
 */
int inserirFuncionario(EntradaHash* tabela_hash, int hash, char matricula[], Funcionario funcionario, int (*tratarColisao)(int, char[], int), int tam_hash) {
    int colisao = 0, inseriu = 0;
    int novo_hash = hash;

    while(novo_hash < tam_hash && inseriu == 0){
        if (tabela_hash[novo_hash].ocupado == -1) { 
            tabela_hash[novo_hash].ocupado = novo_hash;
            tabela_hash[novo_hash].funcionario = funcionario;
            inseriu = 1;
        } 
        else {
            colisao++;
            novo_hash = tratarColisao(novo_hash, matricula, tam_hash);
        }
    }

    if(inseriu == 0){
        tabela_hash[hash].ocupado = hash;
        tabela_hash[hash].funcionario = funcionario;
    }

    return colisao; 
}

/**
 * @brief Função para testar a tabela hash
 * 
 * @param calcularHash Função para calcular o hash
 * @param tratarColisao Função para tratar colisões
 * @param tam_hash Tamanho da tabela hash
 * @return void
 */
void testarHash(int (*calcularHash)(char[], int), int (*tratarColisao)(int, char[], int), int tam_hash) {
    EntradaHash tabela_hash[tam_hash];
    inicializarTabelaHash(tabela_hash, tam_hash);

    int total_colisoes = 0, i;
    clock_t tempo_total = 0;

    for(int i = 0; i < 1000; i++){
        Funcionario funcionario = criarFuncionario();

        clock_t inicio = clock();
        int hash = calcularHash(funcionario.matricula, tam_hash);
        total_colisoes += inserirFuncionario(tabela_hash, hash, funcionario.matricula, funcionario, tratarColisao, tam_hash);
        clock_t fim = clock();

        tempo_total += (fim - inicio);
    }

    printf("Tempo para insercao: %f segundos\n", ((double)tempo_total / CLOCKS_PER_SEC));
    printf("Total de colisoes: %d\n", total_colisoes);
}
