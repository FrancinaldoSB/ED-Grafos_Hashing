#include "./src/Q4.h"

int main(){
    const int TAM_HASH = 150;
    const int TAM_HASH2 = 101;

    srand(time(NULL)); // Para garantir números aleatórios

    printf("Teste com Hash 1:\n");
    testarHash(hash1, tratarColisaoHash1, TAM_HASH);

    printf("\nTeste com Hash 2:\n");
    testarHash(hash2, tratarColisaoHash2, TAM_HASH);

    printf("\nTeste com Hash 1 (Tamanho 101):\n");
    testarHash(hash1, tratarColisaoHash1, TAM_HASH2);

    printf("\nTeste com Hash 2 (Tamanho 101):\n");
    testarHash(hash2, tratarColisaoHash2, TAM_HASH2);
    
    return 0;
}
