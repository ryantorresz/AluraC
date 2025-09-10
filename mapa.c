#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

// Lê o mapa do arquivo texto
void lemapa(MAPA* m) {
    FILE* f = fopen("mapa.text", "r");
    if(f == NULL) {
        printf("Erro na leitura do mapa (arquivo 'mapa.text' não encontrado)\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
    alocamapa(m);

    for(int i = 0; i < m->linhas; i++) {
        fscanf(f, "%s", m->matriz[i]);
    }

    fclose(f);
}

// Aloca memória para o mapa
void alocamapa(MAPA* m) {
    m->matriz = malloc(sizeof(char*) * m->linhas);
    for(int i = 0; i < m->linhas; i++) {
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
    }
}

// Copia um mapa para outro
void copiamapa(MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;
    alocamapa(destino);
    for(int i = 0; i < origem->linhas; i++) {
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}

// Libera a memória do mapa
void liberamapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {
        free(m->matriz[i]);
    }
    free(m->matriz);
}

// Encontra a posição de um caractere no mapa
int encontramapa(MAPA* m, POSICAO* p, char c) {
    for(int i = 0; i < m->linhas; i++) {
        for(int j = 0; j < m->colunas; j++) {
            if(m->matriz[i][j] == c) {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}

// Verifica se pode andar em determinada posição
int podeandar(MAPA* m, char personagem, int x, int y) {
    return 
        ehvalida(m, x, y) && 
        !ehparede(m, x, y) &&
        !ehpersonagem(m, personagem, x, y);
}

// Verifica se a posição é válida
int ehvalida(MAPA* m, int x, int y) {
    if(x < 0 || x >= m->linhas) 
        return 0;
    if(y < 0 || y >= m->colunas) 
        return 0;
    return 1;    
}

// Verifica se há um personagem na posição
int ehpersonagem(MAPA* m, char personagem, int x, int y) {
    return m->matriz[x][y] == personagem;
}

// Verifica se é parede
int ehparede(MAPA* m, int x, int y) {
    return 
        m->matriz[x][y] == PAREDE_VERTICAL ||
        m->matriz[x][y] == PAREDE_HORIZONTAL;
}

// Move um personagem no mapa
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino) {
    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xdestino][ydestino] = personagem;
    m->matriz[xorigem][yorigem] = VAZIO;
}