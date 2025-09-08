#include <stdio.h>

#define ROWS 5
#define COLS 10

// Initialize the map
void initializeMap(char map[ROWS][COLS]) {
    // Row 0: |--------|
    for (int j = 0; j < COLS; j++) map[0][j] = (j == 0 || j == COLS-1) ? '|' : '-';
    
    // Row 1: |...|..-.|
    map[1][0] = map[1][COLS-1] = '|';
    map[1][1] = map[1][2] = map[1][3] = map[1][5] = map[1][6] = map[1][8] = '.';
    map[1][4] = '|';
    map[1][7] = '-';
    
    // Row 2: |..-|.@..|
    map[2][0] = map[2][COLS-1] = '|';
    map[2][1] = map[2][2] = map[2][4] = map[2][6] = map[2][7] = map[2][8] = '.';
    map[2][3] = '-';
    map[2][5] = '@';  // Hero
    
    // Row 3: |......-.|
    map[3][0] = map[3][COLS-1] = '|';
    for (int j = 1; j < COLS-1; j++) map[3][j] = (j == 7) ? '-' : '.';
    
    // Row 4: |--------|
    for (int j = 0; j < COLS; j++) map[4][j] = (j == 0 || j == COLS-1) ? '|' : '-';
}

// Print the map
void printMap(char map[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char map[ROWS][COLS];
    initializeMap(map);
    printMap(map);
    return 0;
}