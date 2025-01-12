#include "./src/Q3.h"

/**
 * @brief Função para exibir o menu de operações
 * 
 * @return void
 */
void menu(){
    printf("\nMenu de Operações:\n");
    printf("1. Inicializar Grafo\n");
    printf("2. Popular Grafo\n");
    printf("3. Exibir Grafo\n");
    printf("4. Encontrar Caminho com Dijkstra\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

int main(){
    srand(1);

    Grafo grafo;
    double distancias[QUANTIDADE_DE_VERTICES];
    int predecessor[QUANTIDADE_DE_VERTICES];
    int opcao;

    do{
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniGrafo(&grafo);
                printf("O grafo foi inicializado com sucesso.\n");
                break;
            case 2:
                preencherArestas(&grafo);
                printf("O grafo foi populado com confiabilidades aleatórias.\n");
                break;
            case 3:
                exibirGrafo(&grafo);
                break;
            case 4:
                Djikstra(0, grafo.arestas, distancias, predecessor);
                exibirDjikstra(0, 2, predecessor);
                break;
            case 5:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }while(opcao != 5);

    return 0;
}