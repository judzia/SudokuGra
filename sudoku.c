#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h" // dolaczam wlasny pliczek naglowkowy (deklaracje struktur i funkcji)

// funkcja tworzy nowa gre sudoku o zadanym rozmiarze planszy
SudokuGame* create_game(int size) {
    // alokujemy pamiec na strukture sudokugame
    SudokuGame* game = malloc(sizeof(SudokuGame));
    // ustawiamy rozmiar planszy
    game->size = size;

    // alokujemy pamiec na tablice wskaznikow (wiersze planszy)
    game->board = malloc(size * sizeof(int*));
    game->fixed = malloc(size * sizeof(int*));

    // tworzymy tablice wskaznikow dla wierszy planszy
    // dla kazdego wiersza
    for (int i = 0; i < size; i++) {
        // alokujemy pamiec na kolumny i inicjalizujemy je zerami (calloc)
        game->board[i] = calloc(size, sizeof(int));
        game->fixed[i] = calloc(size, sizeof(int));
    }
    //zwracamy wskaznik na utworzona gre woohooo
    return game;
}

// funkcja zwalnia pamiec przydzielona dla gry sudoku
void free_game(SudokuGame* game) {
    // dla kazdego wiersza
    for (int i = 0; i < game->size; i++) {
        // zwolnij pamiec kolumn dla planszy i planszy fixed (pola stale)
        free(game->board[i]);
        free(game->fixed[i]);
    }
    // zwolnij pamiec dla tablicy wierszy
    free(game->board);
    free(game->fixed);
    // zwolnij pamiec dla samej struktury gry
    free(game);
}

// funkcja drukuje aktualny stan planszy sudoku na ekranie
void print_board(SudokuGame* game) {
    printf("\n");
    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            if (game->board[i][j] != 0)
                // jesli w komorce jest liczba rozna od zera to wyswietl ja
                printf("%2d ", game->board[i][j]);
            else
                // jesli komorka jest pusta to wyswietl kropke
                printf(" . ");
        }
        printf("\n");
    }
}

// funkcja (na razie puste) odpowiedzialna za generowanie kompletnej planszy sudoku
void generate_full_board(SudokuGame* game) {
    // Tu generator sudoku z backtrackingiem bydzie
}

// funkcja (na razie pusta) do usuwania pewnej liczby liczb z planszy
// w zaleznosci od wybranego poziomu trudnosci
void remove_numbers(SudokuGame* game, int difficulty) {
    // Tu usuwa liczby w zaleznosci od trudnosci
}
