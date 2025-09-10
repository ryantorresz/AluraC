#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

// Definições de comandos
#define ESQUERDA 'a'
#define CIMA     'w'
#define BAIXO    's'
#define DIREITA  'd'
#define BOMBA    'b'

MAPA m;
POSICAO heroi;
int tempilula = 0;

// Verifica se o jogo acabou
int acabou() {
    POSICAO pos;
    int perdeu = !encontramapa(&m, &pos, HEROI);
    int ganhou = !encontramapa(&m, &pos, FANTASMA);
    return ganhou || perdeu;
}

// Verifica se o comando é uma direção válida
int ehdirecao(char direcao) {
    return direcao == ESQUERDA || direcao == CIMA || direcao == BAIXO || direcao == DIREITA;
}

// Verifica se é parede
int ehparede(MAPA* m, int x, int y) {
    return m->matriz[x][y] == PAREDE_VERTICAL || m->matriz[x][y] == PAREDE_HORIZONTAL;
}

// Move o herói
void move(char direcao) {
    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch(direcao) {
        case ESQUERDA: proximoy--; break;
        case CIMA:     proximox--; break;
        case BAIXO:    proximox++; break;
        case DIREITA:  proximoy++; break;
    }

    if(!podeandar(&m, HEROI, proximox, proximoy))
        return;

    if(ehpersonagem(&m, PILULA, proximox, proximoy)) {
        tempilula = 1;
    }

    andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;
}

// Decide para onde o fantasma vai
int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino) {
    int opcoes[4][2] = {
        { xatual   , yatual+1 },
        { xatual+1 , yatual   },
        { xatual   , yatual-1 },
        { xatual-1 , yatual   }
    };

    for(int i = 0; i < 10; i++) {
        int posicao = rand() % 4;
        if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}

// Move todos os fantasmas
void fantasmas() {
    MAPA copia;
    copiamapa(&copia, &m);

    for(int i = 0; i < copia.linhas; i++) {
        for(int j = 0; j < copia.colunas; j++) {
            if(copia.matriz[i][j] == FANTASMA) {
                int xdestino, ydestino;
                int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);
                if(encontrou) {
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
            }
        }
    }
    liberamapa(&copia);
}

// Função recursiva para explosão da pílula
void explodepilula2(int x, int y, int somax, int somay, int qtd) {
    if(qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;

    if(!ehvalida(&m, novox, novoy)) return;
    if(ehparede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd-1);
}

// Explode a pílula nas quatro direções
void explodepilula() {
    if(!tempilula) return;

    explodepilula2(heroi.x, heroi.y, 0, 1, 3);
    explodepilula2(heroi.x, heroi.y, 0, -1, 3);
    explodepilula2(heroi.x, heroi.y, 1, 0, 3);
    explodepilula2(heroi.x, heroi.y, -1, 0, 3);

    tempilula = 0;
}

int main() {
    srand(time(0)); // Inicializa o gerador de números aleatórios

    lemapa(&m);

    // TESTE: Verifica se o mapa foi carregado corretamente
    printf("=== TESTE: MAPA CARREGADO ===\n");
    imprimemapa(&m);

    if (!encontramapa(&m, &heroi, HEROI)) {
        printf("Erro: herói não encontrado no mapa!\n");
        liberamapa(&m);
        return 1;
    }

    do {
        printf("Pílula: %s\n", (tempilula ? "SIM" : "NÃO"));
        imprimemapa(&m);

        char comando;
        scanf(" %c", &comando);

        if(ehdirecao(comando)) move(comando);
        if(comando == BOMBA) explodepilula();

        fantasmas();

    } while (!acabou());

    liberamapa(&m);
    printf("Fim de jogo!\n");
    return 0;
}