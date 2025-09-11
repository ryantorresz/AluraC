#include <stdio.h>
#include "mapa.h"

// Constantes para dimensões dos desenhos
#define ALTURA_DESENHO 4
#define LARGURA_DESENHO 7

// Desenhos dos elementos do jogo
char desenhoparede[ALTURA_DESENHO][LARGURA_DESENHO] = {
    {"......"},
    {"......"},
    {"......"},
    {"......"}
};

char desenhofantasma[ALTURA_DESENHO][LARGURA_DESENHO] = {
    {" .-.  "},
    {"| OO| "},
    {"|   | "},
    {"'^^^' "}
};

char desenhoheroi[ALTURA_DESENHO][LARGURA_DESENHO] = {
    {" .--. "},
    {"/ _.-'"},
    {"\\  '-."},
    {" '--' "}
};

char desenhopilula[ALTURA_DESENHO][LARGURA_DESENHO] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhovazio[ALTURA_DESENHO][LARGURA_DESENHO] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

// Função auxiliar para obter o desenho correto
char (*obtemdesenho(char elemento))[LARGURA_DESENHO] {
    switch(elemento) {
        case FANTASMA:           return desenhofantasma;
        case HEROI:              return desenhoheroi;
        case PILULA:             return desenhopilula;
        case PAREDE_VERTICAL:
        case PAREDE_HORIZONTAL:  return desenhoparede;
        case VAZIO:
        default:                 return desenhovazio;
    }
}

// Imprime uma parte do desenho
void imprimeparte(char desenho[ALTURA_DESENHO][LARGURA_DESENHO], int parte) {
    printf("%s", desenho[parte]);
}

// Imprime o mapa inteiro com desenhos
void imprimemapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {
        for(int parte = 0; parte < ALTURA_DESENHO; parte++) {
            for(int j = 0; j < m->colunas; j++) {
                char elemento = m->matriz[i][j];
                imprimeparte(obtemdesenho(elemento), parte);
            }
            printf("\n");
        }
    }
}