#include <stdio.h>
#include <stdlib.h>
#include "save_load.h"

// Zapisuje stan gry do pliku
void save_game(SudokuGame *game, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Cannot open file for writing!\n");
        return;
    }

    fprintf(file, "%d %d\n", game->size, game->difficulty);

    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            fprintf(file, "%d ", game->board[i][j]);
        }
        fprintf(file, "\n");
    }

    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            fprintf(file, "%d ", game->fixed[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Game has been saved!\n");
}

// Wczytuje stan gry z pliku
SudokuGame* load_game(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file for reading!\n");
        return NULL;
    }

    int size, difficulty;
    fscanf(file, "%d %d", &size, &difficulty);

    SudokuGame *game = create_game(size);

    game->difficulty = difficulty;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &game->board[i][j]);
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &game->fixed[i][j]);
        }
    }

    fclose(file);
    printf("Game has been loaded!\n");
    return game;
}
