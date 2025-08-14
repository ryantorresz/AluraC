#include <stdio.h>

int main() {
    int numeroSecreto = 42;  // Número a ser adivinhado
    int chute;

    printf("Adivinhe o número secreto (1-100): ");
    scanf("%d", &chute);

    printf("Você chutou: %d\n", chute);

    if (chute == numeroSecreto) {
        printf("Parabéns! Acertou!\n");
    } else {
        printf("Errou! O número era %d\n", numeroSecreto);
    }

    return 0;
}