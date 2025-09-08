#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Para _kbhit e _getch no Windows
#include <windows.h> // Para a função Sleep()

// --- Constantes do Jogo ---
#define MAP_WIDTH 21
#define MAP_HEIGHT 11
#define MAX_GHOSTS 4

// --- Variáveis de Estado do Jogo ---
char map[MAP_HEIGHT][MAP_WIDTH] = {
    "####################",
    "#........#.........#",
    "#.##.###.#.###.##.#",
    "#o.#.#o..o..o#.#o.#",
    "#o##.##.#.#.##.##o#",
    "#o...#...#...#...o#",
    "#.###.##.#.##.###.#",
    "#.#o...o.O.o...o#.#",
    "#.##.##.#####.##.##",
    "#....#...#...#....#",
    "####################"
};
int pacmanX, pacmanY;
int score = 0;
int lives = 3;
int foodCount = 0;

// --- Estrutura do Fantasma ---
typedef struct {
    int x, y;
    int dir; // 0: cima, 1: baixo, 2: esquerda, 3: direita
    int isAlive;
    char originalChar; // O caractere sobre o qual o fantasma está (ex: '.', ' ')
} Ghost;

Ghost ghosts[MAX_GHOSTS];

// --- Protótipos das Funções ---
void initGame();
void drawMap();
void updateGame();
void processInput();
void movePacman(int dx, int dy);
void moveGhosts();
void checkCollisions();
void updateDisplay();
int isWall(int x, int y);
void gameOver();
void resetGame();

// --- Loop Principal do Jogo ---
int main() {
    srand(time(NULL));
    initGame();

    while (lives > 0 && foodCount > 0) {
        processInput();
        moveGhosts();
        checkCollisions();
        updateDisplay();

        // Pequeno atraso para controlar a velocidade do jogo
        Sleep(200); // 200 milissegundos
    }

    gameOver();
    return 0;
}

// --- Implementação das Funções ---
void initGame() {
    // Posição inicial do Pac-Man
    pacmanX = 10;
    pacmanY = 8;
    map[pacmanY][pacmanX] = 'P';

    // Conta a comida e inicializa os fantasmas
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == '.' || map[y][x] == 'o') {
                foodCount++;
            }
        }
    }

    // Inicializa os fantasmas
    ghosts[0] = (Ghost){1, 1, 0, 1, '.'};
    map[ghosts[0].y][ghosts[0].x] = 'G';
    ghosts[1] = (Ghost){MAP_WIDTH - 2, 1, 0, 1, '.'};
    map[ghosts[1].y][ghosts[1].x] = 'G';
    ghosts[2] = (Ghost){1, MAP_HEIGHT - 2, 0, 1, '.'};
    map[ghosts[2].y][ghosts[2].x] = 'G';
    ghosts[3] = (Ghost){MAP_WIDTH - 2, MAP_HEIGHT - 2, 0, 1, '.'};
    map[ghosts[3].y][ghosts[3].x] = 'G';

    updateDisplay();
}

void updateDisplay() {
    system("cls"); // Limpa a tela no Windows
    drawMap();
    printf("Pontuação: %d | Vidas: %d\n", score, lives);
}

void drawMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        printf("%s\n", map[y]);
    }
}

void processInput() {
    int ch;
    if (_kbhit()) {
        ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                movePacman(0, -1);
                break;
            case 's':
            case 'S':
                movePacman(0, 1);
                break;
            case 'a':
            case 'A':
                movePacman(-1, 0);
                break;
            case 'd':
            case 'D':
                movePacman(1, 0);
                break;
            case 'q':
            case 'Q':
                lives = 0; // Sai do jogo
                break;
        }
    }
}

void movePacman(int dx, int dy) {
    int nextX = pacmanX + dx;
    int nextY = pacmanY + dy;

    if (!isWall(nextX, nextY)) {
        // Limpa a posição anterior do Pac-Man
        map[pacmanY][pacmanX] = ' ';

        // Verifica para onde o Pac-Man está se movendo
        if (map[nextY][nextX] == '.') {
            score += 10;
            foodCount--;
        } else if (map[nextY][nextX] == 'o') {
            score += 50;
            foodCount--;
        }

        // Atualiza a posição do Pac-Man
        pacmanX = nextX;
        pacmanY = nextY;
        map[pacmanY][pacmanX] = 'P';
    }
}

void moveGhosts() {
    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (ghosts[i].isAlive) {
            // Restaura o caractere em que o fantasma estava
            map[ghosts[i].y][ghosts[i].x] = ghosts[i].originalChar;

            // Movimento aleatório simples do fantasma
            int dx = 0, dy = 0;
            do {
                dx = rand() % 3 - 1; // -1, 0, ou 1
                dy = rand() % 3 - 1;
            } while (dx == 0 && dy == 0 || isWall(ghosts[i].x + dx, ghosts[i].y + dy));

            ghosts[i].x += dx;
            ghosts[i].y += dy;

            // Salva o caractere para o qual o fantasma vai se mover
            ghosts[i].originalChar = map[ghosts[i].y][ghosts[i].x];
            
            // Coloca o fantasma na nova posição
            map[ghosts[i].y][ghosts[i].x] = 'G';
        }
    }
}

void checkCollisions() {
    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (ghosts[i].isAlive) {
            // Verifica se um fantasma está no mesmo tile que o Pac-Man
            if (pacmanX == ghosts[i].x && pacmanY == ghosts[i].y) {
                printf("\nVocê foi pego!\n");
                lives--;
                if (lives > 0) {
                    resetGame();
                }
                return;
            }
        }
    }
}

int isWall(int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return 1; // Fora dos limites é uma parede
    }
    return map[y][x] == '#';
}

void resetGame() {
    // Limpa o mapa e redefine as posições
    map[pacmanY][pacmanX] = ' ';
    pacmanX = 10;
    pacmanY = 8;
    map[pacmanY][pacmanX] = 'P';

    for (int i = 0; i < MAX_GHOSTS; i++) {
        map[ghosts[i].y][ghosts[i].x] = ghosts[i].originalChar;
        // Reinicializa as posições dos fantasmas
        ghosts[i].x = 1 + i;
        ghosts[i].y = 1;
        ghosts[i].originalChar = map[ghosts[i].y][ghosts[i].x];
        map[ghosts[i].y][ghosts[i].x] = 'G';
    }

    updateDisplay();
    printf("Você perdeu uma vida! Pressione qualquer tecla para continuar...\n");
    _getch();
}

void gameOver() {
    updateDisplay();
    if (foodCount == 0) {
        printf("\n\nPARABÉNS! Você comeu toda a comida! Você venceu!\n\n");
    } else {
        printf("\n\nFIM DE JOGO! Você ficou sem vidas.\n\n");
    }
}
