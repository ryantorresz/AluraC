#include <stdio.h>
#include <windows.h> // Para SetConsoleOutputCP

int main() {
    SetConsoleOutputCP(65001); // UTF-8 no Windows

    const int numeroSecreto = 42;
    int chute;
    int tentativas = 0;
    int max_tentativas = 5;
    int tentativas_history[max_tentativas]; // Armazena todos os chutes

    printf("=== Jogo da Adivinhação ===\n");
    printf("Adivinhe o número entre 1 e 100. Você tem %d tentativas.\n\n", max_tentativas);

    while (tentativas < max_tentativas) {
        printf("Tentativa %d/%d: ", tentativas + 1, max_tentativas);
        
        // Validação de entrada
        while (1) {
            if (scanf("%d", &chute) != 1) {
                printf("Entrada inválida! Digite um número: ");
                while (getchar() != '\n'); // Limpa buffer do teclado
                continue; 
            }
            if (chute < 1 || chute > 100) {
                printf("Número deve ser entre 1 e 100. Tente novamente: ");
                continue;
            }
            break;
        }

        tentativas_history[tentativas] = chute;
        tentativas++;

        if (chute == numeroSecreto) {
            printf("\n🎉 Parabéns! Você acertou em %d tentativas!\n", tentativas);
            break;
        } else if (chute < numeroSecreto) {
            printf("⬆️ Muito baixo!\n");
        } else {
            printf("⬇️ Muito alto!\n");
        }
    }

    // Mostra histórico se não acertou
    if (chute != numeroSecreto) {
        printf("\nFim do jogo. O número era: %d\n", numeroSecreto);
    }

    // Mostra todas as tentativas
    printf("\nSeus chutes:\n");
    for (int i = 0; i < tentativas; i++) {
        printf("Tentativa %d: %d", i + 1, tentativas_history[i]);
        if (tentativas_history[i] == numeroSecreto) {
            printf(" ✅ (Acertou!)");
        } else if (tentativas_history[i] < numeroSecreto) {
            printf(" ⬆️ (Baixo)");
        } else {
            printf(" ⬇️ (Alto)");
        }
        printf("\n");
    }

    return 0;
}