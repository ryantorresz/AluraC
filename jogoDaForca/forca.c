#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRA 20
#define MAX_TENTATIVAS 26
#define MAX_ERROS 6

void abertura() {
    printf("/***********************/\n");
    printf("/     JOGO DA FORCA     /\n");
    printf("/***********************/\n\n");
}

void desenha_forca(int erros) {
    printf("\n");
    printf("  _______     \n");
    printf(" |/      |    \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), 
                              (erros >= 1 ? '_' : ' '), 
                              (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 2 ? '\\' : ' '),
                              (erros >= 3 ? '|' : ' '),
                              (erros >= 4 ? '/' : ' '));
    printf(" |       %c    \n", (erros >= 5 ? '|' : ' '));
    printf(" |      %c %c  \n", (erros >= 6 ? '/' : ' '), 
                              (erros >= 6 ? '\\' : ' '));
    printf(" |           \n");
    printf("_|___        \n");
    printf("\n");
}

int letra_ja_chutada(char letra, char chutes[], int tentativas) {
    letra = toupper(letra);
    for(int i = 0; i < tentativas; i++) {
        if(chutes[i] == letra) {
            return 1;
        }
    }
    return 0;
}

int verifica_vitoria(char palavrasecreta[], char chutes[], int tentativas) {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        int achou = 0;
        for(int j = 0; j < tentativas; j++) {
            if(toupper(chutes[j]) == palavrasecreta[i]) {
                achou = 1;
                break;
            }
        }
        if(!achou) {
            return 0;
        }
    }
    return 1;
}

void mostra_palavra(char palavrasecreta[], char chutes[], int tentativas) {
    printf("\nPalavra: ");
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        int achou = 0;
        for(int j = 0; j < tentativas; j++) {
            if(toupper(chutes[j]) == palavrasecreta[i]) {
                printf("%c ", palavrasecreta[i]);
                achou = 1;
                break;
            }
        }
        if(!achou) {
            printf("_ ");
        }
    }
    printf("\n");
}

void mostra_chutes(char chutes[], int tentativas) {
    if(tentativas > 0) {
        printf("Letras chutadas: ");
        for(int i = 0; i < tentativas; i++) {
            printf("%c ", toupper(chutes[i]));
        }
        printf("\n");
    }
}

int main() {
    char palavrasecreta[MAX_PALAVRA];
    strcpy(palavrasecreta, "MELANCIA");
    
    // Converter para maiúsculas
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        palavrasecreta[i] = toupper(palavrasecreta[i]);
    }

    int acertou = 0;
    int enforcou = 0;
    int erros = 0;

    char chutes[MAX_TENTATIVAS];
    int tentativas = 0;

    abertura();
    printf("Dica: Fruta verde por fora e vermelha por dentro!\n");

    do {
        printf("\n=====================================\n");
        
        desenha_forca(erros);
        mostra_palavra(palavrasecreta, chutes, tentativas);
        mostra_chutes(chutes, tentativas);
        printf("Erros: %d/%d\n", erros, MAX_ERROS);

        if(acertou || enforcou) {
            break;
        }

        char chute;
        printf("\nQual letra? ");
        scanf(" %c", &chute);
        
        // Validar entrada
        if(!isalpha(chute)) {
            printf("Por favor, digite apenas letras!\n");
            continue;
        }

        chute = toupper(chute);

        // Verificar se letra já foi chutada
        if(letra_ja_chutada(chute, chutes, tentativas)) {
            printf("Você já chutou a letra %c!\n", chute);
            continue;
        }

        chutes[tentativas] = chute;
        tentativas++;

        // Verificar se a letra existe na palavra
        int letra_existe = 0;
        for(int i = 0; i < strlen(palavrasecreta); i++) {
            if(palavrasecreta[i] == chute) {
                letra_existe = 1;
                break;
            }
        }

        if(!letra_existe) {
            erros++;
            printf("A letra %c não existe na palavra!\n", chute);
        }

        // Verificar condições de vitória/derrota
        acertou = verifica_vitoria(palavrasecreta, chutes, tentativas);
        enforcou = (erros >= MAX_ERROS);

    } while (!acertou && !enforcou);

    printf("\n=====================================\n");
    
    if(acertou) {
        printf("\n🎉 PARABÉNS! Você acertou a palavra: ");
        for(int i = 0; i < strlen(palavrasecreta); i++) {
            printf("%c", palavrasecreta[i]);
        }
        printf("\n");
    } else {
        desenha_forca(erros);
        printf("\n💀 GAME OVER! A palavra era: %s\n", palavrasecreta);
    }

    printf("\nJogue novamente!\n");

    return 0;
}