#include <stdio.h>  // biblioteka do wypisywania/odbierania danych z konsoli (np. printf, scanf)
#include <stdlib.h> // biblioteka do funkcji systemowych np. malloc (alokacja pamieci)
#include "sudoku.h" // moj wlasny plik naglowkowy z definicjami gry
#include "save_load.h"


//Da dieses Sudoku „irritierend“ war (eine Untertreibung, aber höflich),
//werde ich es auf Polnisch und Deutsch kommentieren, damit Sie meine Nervosität spüren können


//funkcja pomocnicza do wyswietlania menu ladnie
void print_menu() {
    printf("\n======= MENU GLOWNE =======\n");
    printf("1. Nowa gra\n");
    printf("2. Zapisz gre\n");
    printf("3. Wczytaj gre\n");
    printf("4. Instrukcja\n");
    printf("5. Wyjscie\n");
    printf("===========================\n");
    printf("Wybierz opcje: ");
}

//funckja do wyswietlania instrukcji
void print_instructions() {
    printf("\n==== INSTRUKCJA GRY SUDOKU ====\n");
    printf("Twoim celem jest wypelnienie calej planszy cyframi,\n");
    printf("tak aby kazda cyfra wystepowala dokladnie raz\n");
    printf("w kazdym wierszu, kolumnie i malym kwadracie.\n\n");

    printf("Jak grac:\n");
    printf("- Najpierw wybierz rozmiar planszy (4x4, 9x9 lub 16x16).\n");
    printf("- Nastepnie wybierz poziom trudnosci.\n");
    printf("- Podczas gry podajesz numer wiersza, kolumny i wartosc,\n");
    printf("  ktora chcesz wprowadzic.\n");
    printf("- Mozesz usuwac swoje ruchy (podajac 0 jako wartosc).\n");
    printf("- Mozesz zapisac i pozniej wczytac gre.\n\n");

    printf("Dodatkowe informacje:\n");
    printf("- Plansze sa generowane tak, by mialy zawsze jedno rozwiazanie.\n");
    printf("- Badz ostrozny! Program sprawdza poprawnosc Twoich ruchow.\n");
    printf("- Jesli utkniesz, mozesz poprosic o podpowiedz (opcjonalnie).\n");

    printf("\nPowodzenia i milej zabawy! :)\n");
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
                printf("Wybierz rozmiar planszy (4, 9, 16): ");
                if (scanf("%d", &size) != 1 || (size != 4 && size != 9 && size != 16)) {
                    printf("Nieprawidlowy rozmiar planszy.\n");
                    while (getchar() != '\n');
                    break;
                }

                if (game != NULL) {
                    free_game(game); // zwolnij poprzednia gre
                }

                game = create_game(size);
                generate_full_board(game);

                // pobieramy poziom trudnosci
                printf("Wybierz poziom trudnosci (1=latwy, 2=sredni, 3=trudny): ");
                if (scanf("%d", &difficulty) != 1 || (difficulty < 1 || difficulty > 3)) {
                    printf("Nieprawidlowy poziom trudnosci.\n");
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
                printf("Brak gry do zapisania.\n");
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
                printf("Blad podczas wczytywania gry.\n");
            }
            break;
        case 4:
            print_instructions();
            break;
        case 5:// WYJSCIE
            printf("Do zobaczenia!\n");
            break;
        default:
            printf("Nieprawidlowa opcja. Sprobuj ponownie.\n");
        }

    } while (opcja != 5); //powtarzamy dopoki uzytwkonik nie wybierze

    if (game != NULL) {
        free_game(game); // na koniec programu zwolnij pamiec bo przyps
    }
    return 0;
}