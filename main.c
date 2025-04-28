#include <stdio.h>  // biblioteka do wypisywania/odbierania danych z konsoli (np. printf, scanf)
#include <stdlib.h> // biblioteka do funkcji systemowych np. malloc (alokacja pamieci)
#include "sudoku.h" // moj wlasny plik naglowkowy z definicjami gry
#include "save_load.h"


//Da dieses Sudoku „irritierend“ war (eine Untertreibung, aber höflich),
//werde ich es auf Polnisch und Deutsch kommentieren, damit Sie meine Nervosität spüren können


//funkcja pomocnicza do wyswietlania menu ladnie
void print_menu() {
    printf("\n======= MAIN MENU =======\n");
    printf("1. New Game\n");
    printf("2. Save Game\n");
    printf("3. Load Game\n");
    printf("4. Instructions\n");
    printf("5. Exit\n");
    printf("===========================\n");
    printf("Choose an option: ");
}

//funckja do wyswietlania instrukcji
void print_instructions() {
    printf("\n==== SUDOKU GAME INSTRUCTIONS ====\n");
    printf("Your goal is to fill the entire board with numbers\n");
    printf("so that each number appears exactly once\n");
    printf("in each row, column, and small box.\n\n");

    printf("How to play:\n");
    printf("- First, choose the board size (4x4, 9x9, or 16x16).\n");
    printf("- Then, select the difficulty level.\n");
    printf("- During the game, enter the row number, column number,\n");
    printf("   and the value you want to place.\n");
    printf("- You can save the game and load it later.\n\n");

    printf("Additional information:\n");
    printf("- Boards are generated to always have exactly one solution.\n");
    printf("- Be careful! The program checks the correctness of your moves.\n");

    printf("\nGood luck and have fun! :)\n");
    printf("===============================\n\n");
}

int main() {
    int opcja;
    SudokuGame* game = NULL; // obecna gra- na poczatku brak

    // glowna petla programu -> dziala dopoki uzytkownik nie wybierze 3
    do {
        print_menu();
        scanf("%d", &opcja); // "odbierz wybor uzytkownika" (wpisuje liczbe)

        switch (opcja)
        {
        case 1: {
                int size, difficulty; // rozmiar planszy i poziom trudnosci
                printf("Choose board size (4, 9, 16): ");
                if (scanf("%d", &size) != 1 || (size != 4 && size != 9 && size != 16)) {
                    printf("Invalid board size.\n");
                    while (getchar() != '\n');
                    break;
                }

                if (game != NULL) {
                    free_game(game); // zwolnij poprzednia gre
                }

                game = create_game(size);
                generate_full_board(game);

                // pobieramy poziom trudnosci
                printf("Choose difficulty level (1=Easy, 2=Medium, 3=Hard): ");
                if (scanf("%d", &difficulty) != 1 || (difficulty < 1 || difficulty > 3)) {
                    printf("Invalid difficulty level.\n");
                    free_game(game);
                    game = NULL;
                    while (getchar() != '\n');
                    break;
                }

                remove_numbers(game, difficulty);

                play_game(game);
                break;
        }
        case 2:// ZAPISZ GRE
            if (game == NULL) {
                printf("No game to save.\n");
            } else {
                save_game(game, "sudoku_save.txt");
            }
            break;
        case 3:// WCZYTAJ GRE
            if (game != NULL) {
                free_game(game); // zwolnij poprzednia gre
            }
            game = load_game("sudoku_save.txt");
            if (game != NULL) {
                play_game(game);
            } else {
                printf("Error loading game.\n");
            }
            break;
        case 4:
            print_instructions();
            break;
        case 5:// WYJSCIE
            printf("See you next time!\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }

    } while (opcja != 5); //powtarzamy dopoki uzytwkonik nie wybierze

    if (game != NULL) {
        free_game(game); // na koniec programu zwolnij pamiec bo przyps
    }
    return 0;
}