#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h" // dolaczam wlasny pliczek naglowkowy (deklaracje struktur i funkcji)
#include <time.h>
#include <math.h>

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
    // sqrt_size to rozmiar jednego malego kwadratu
    int sqrt_size = (int)sqrt(game->size);

    // drukowanie gornej krawedzi
    printf("\n");
    for (int i = 0; i < game->size * 4 + sqrt_size + 1; i++) {
        printf("-");
    }
    printf("\n");

    // drukowanie zawartosci planszy
    for (int i = 0; i < game->size; i++) {
        printf("|"); // lewa krawedz

        for (int j = 0; j < game->size; j++) {
            if (game->board[i][j] != 0) {
                // jesli w komorce jest liczba to wyswietl ja
                printf(" %2d ", game->board[i][j]);
            } else {
                // jesli w komorce jest puste pole aka zero to wyswietl je
                printf("  . ");
            }

            // dodaj pionowa linie po kazdym bloku
            if ((j + 1) % sqrt_size == 0) {
                printf("|");
            }
        }
        printf("\n");

        // po kazdym malym bloku w poziomie (np. co 3 wiersze) dodaj linie pozioma
        if ((i + 1) % sqrt_size == 0 && i < game->size - 1) {
            for (int k = 0; k < game->size * 4 + sqrt_size + 1; k++) {
                printf("-");
            }
            printf("\n");
        }
    }

    // drukowanie dolnej krawedzi
    for (int i = 0; i < game->size * 4 + sqrt_size + 1; i++) {
        printf("-");
    }
    printf("\n");
}



// funkcja sprawdzajaca czy mozna bezpiecznie wstawic numer w dane miejsce
int is_safe(SudokuGame* game, int row, int col, int num) {
    // sprawdzanie w wierszu
    for (int x = 0; x < game->size; x++) {
        if (game->board[row][x] == num) {
            return 0; // numer juz istnieje w wierszu
        }
    }

    // sprawdzanie w kolumnie
    for (int x = 0; x < game->size; x++) {
        if (game->board[x][col] == num) {
            return 0; // numer juz istnieje w kolumnie
        }
    }

    // sprawdzanie w malym kwadracie - oblicz rozmiar malego kwadratu
    int sqrt_size = 0;
    while (sqrt_size * sqrt_size < game->size) {
        sqrt_size++;
    }

    // znajdz poczatek malego kwadratu - lewa gorna kratka
    int box_start_row = row - row % sqrt_size;
    int box_start_col = col - col % sqrt_size;

    // przeszukaj caly kwadrat
    for (int i = 0; i < sqrt_size; i++) {
        for (int j = 0; j < sqrt_size; j++) {
            if (game->board[box_start_row + i][box_start_col + j] == num) {
                return 0; // numer juz istnieje w kwadracie
            }
        }
    }

    // jesli nigdzie nie znaleziono konfliktu to zwracamy 1 (jest bezpiecznie)
    return 1;
}


// funkcja rozwiazuje Sudoku uzywajac backtrackingu
int solve_sudoku(SudokuGame* game, int row, int col) {
    // jesli dotarlismy poza ostatni wiersz to sudoku jest wypelnione
    if (row == game->size) {
        return 1; // sukces
    }

    // jesli dotarlismy do konca wiersza to przechodzimy do nastepnego
    if (col == game->size) {
        return solve_sudoku(game, row + 1, 0);
    }

    // jesli pole jest juz wypelnione (przy innych zastosowaniach solve)
    if (game->board[row][col] != 0) {
        return solve_sudoku(game, row, col + 1);
    }

    // probujemy wstawic kazda mosliwa liczbe od 1 do size
    for (int num = 1; num <= game->size; num++) {
        if (is_safe(game, row, col, num)) {
            game->board[row][col] = num; // wstawiamy numer

            // rekurencyjnie probujemy uzupelnić reszte planszy
            if (solve_sudoku(game, row, col + 1)) {
                return 1; // sukces
            }

            // jeśli sie nie udalo to wycofujemy się (backtrack)
            game->board[row][col] = 0;
        }
    }

    // jesli zadna liczba nie pasuje to zwracamy 0 (brak rozwiazania sad)
    return 0;
}

// funkcja (na razie puste) odpowiedzialna za generowanie kompletnej planszy sudoku
void generate_full_board(SudokuGame* game) {
    solve_sudoku(game, 0, 0); // wywoluje solve od poczatku planszy
}



// funkcja do usuwania pewnej liczby liczb z planszy
// w zaleznosci od wybranego poziomu trudnosci
void remove_numbers(SudokuGame* game, int difficulty) {
    int size = game->size;
    int total_cells = size * size;

    // Na podstawie poziomu trudnocci ustalam ile liczb usunac
    int numbers_to_remove;

    if (difficulty == 1) { // easy
        numbers_to_remove = total_cells * 0.3; // usuwa 30% liczb
    } else if (difficulty == 2) { // medium
        numbers_to_remove = total_cells * 0.5; // usuwa 50% liczb
    } else if (difficulty == 3) { // hard
        numbers_to_remove = total_cells * 0.7; // usuwa 70% liczb
    } else {
        numbers_to_remove = total_cells * 0.5; // domyslnie sredni poziom
    }

    srand(time(NULL)); // inicjalizacja generatora liczb losowych

    while (numbers_to_remove > 0) {
        int row = rand() % size; // losowy wiersz
        int col = rand() % size; // losowa kolumna

        if (game->board[row][col] != 0) {
            game->board[row][col] = 0; // usuwa liczbe (wstawia 0 = puste pole)
            game->fixed[row][col] = 0; // zaznaczam ze to pole nie jest stale
            numbers_to_remove--;
        }
        // jesli trafimy na puste juz miejsce to losuje znowu :p
    }
}


int make_move(SudokuGame* game, int row, int col, int num) {
    if (game->fixed[row][col]) {
        printf("Nie mozesz zmieniac tej liczby!\n");
        return 0;
    }
    if (is_safe(game, row, col, num)) {
        game->board[row][col] = num;
        return 1;
    } else {
        printf("Nieprawidlowy ruch!\n");
        return 0;
    }
}

// funkcja sprawdzajaca czy sudoku jest w pelni rozwiazane
int is_game_complete(SudokuGame* game) {
    // sprawdzanie wierszy
    for (int i = 0; i < game->size; i++) {
        int seen[17] = {0}; // zakładam, że sudoku ma max size 9x9
        for (int j = 0; j < game->size; j++) {
            int num = game->board[i][j];
            if (num == 0 || seen[num]) {
                return 0;
            }
            seen[num] = 1;
        }
    }

    // sprawdzanie kolumn
    for (int j = 0; j < game->size; j++) {
        int seen[17] = {0};
        for (int i = 0; i < game->size; i++) {
            int num = game->board[i][j];
            if (num == 0 || seen[num]) {
                return 0;
            }
            seen[num] = 1;
        }
    }

    // sprawdzanie małych kwadratów
    int block_size = (int)sqrt(game->size); // np. 3 dla 9x9 sudoku
    for (int row = 0; row < game->size; row += block_size) {
        for (int col = 0; col < game->size; col += block_size) {
            int seen[10] = {0};
            for (int i = 0; i < block_size; i++) {
                for (int j = 0; j < block_size; j++) {
                    int num = game->board[row+i][col+j];
                    if (num == 0 || seen[num]) {
                        return 0;
                    }
                    seen[num] = 1;
                }
            }
        }
    }
    return 1; // wszystko git
}

void play_game(SudokuGame* game) {
    int row, col, num;

    while (1) {
        printf("\nTwoja plansza:\n");
        print_board(game);

        if (is_game_complete(game)) { // sprawdzenie, czy gra zakończona
            printf("\nGratulacje! Ukonczyles Sudoku!\n");
            break;
        }

        printf("Wykonaj ruch (wiersz kolumna liczba) lub wpisz -1 aby wyjsc: ");

        if (scanf("%d", &row) != 1) {
            printf("Nieprawidlowe dane.\n");
            while (getchar() != '\n');
            continue;
        }

        if (row == -1) {
            printf("Powrot do menu glownego.\n");
            break;
        }

        if (scanf("%d %d", &col, &num) != 2) {
            printf("Nieprawidlowe dane.\n");
            while (getchar() != '\n');
            continue;
        }

        row--; // dostosowanie do indeksu 0
        col--; // dostosowanie do indeksu 0

        if (row >= 0 && row < game->size && col >= 0 && col < game->size && num >= 1 && num <= game->size) {
            make_move(game, row, col, num);
            printf("Dobry ruch!\n");
        } else {
            printf("Nieprawidlowe dane. Sprobuj ponownie.\n");
        }
    }
}