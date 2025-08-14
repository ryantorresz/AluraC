#include <stdio.h>

int main() {
    int numeroSecreto = 42;  // Número a ser adivinhado
    int chute;

    for(int i = 0; i <= 3; i++) {
        printf("Tentativa %d de 3\n", i);
        printf("Adivinhe o número secreto (1-100): ");
        scanf("%d", &chute);

        printf("Você chutou: %d\n", chute);

        if (chute == numeroSecreto) {
            printf("Parabéns! Acertou!\n");
            return 0;  // Termina o programa se acertar
        } else {
            if (chute > numeroSecreto) {
                printf("Muito alto! Tente novamente.\n");
            } else {  // Não precisa do if, pois já sabemos que é menor
                printf("Muito baixo! Tente novamente.\n");
            }
        }   
    }
    
    printf("Fim do jogo.\n");
    return 0;
}
// Fim do código