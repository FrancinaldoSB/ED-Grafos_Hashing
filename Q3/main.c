#include "./src/Q3.h"

/**
 * @brief Função para exibir o menu de operações
 * 
 * @return void
 */
void menu(){
    printf("\nMenu de Operações:\n");
    printf("1. Exibir Grafo\n");
    printf("2. Encontrar Caminho com Dijkstra\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

int main(){
    srand(1);

    Grafo grafo;
    double distancias[QUANTIDADE_DE_VERTICES];
    int predecessor[QUANTIDADE_DE_VERTICES];
    int opcao, inicio, fim;

    iniGrafo(&grafo);

    preencherArestas(&grafo);

    do{
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirGrafo(&grafo);
                break;
            case 2:
                printf("Digite o vertice de início: ");
                scanf("%d", &inicio);
                printf("Digite o vertice de fim: ");
                scanf("%d", &fim);
                Djikstra(inicio, grafo.arestas, distancias, predecessor);
                exibirDjikstra(inicio, fim, predecessor);
                break;
            case 3:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }while(opcao != 3);

    return 0;
}