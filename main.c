#include <stdio.h>  // biblioteka do wypisywania/odbierania danych z konsoli (np. printf, scanf)
#include <stdlib.h> // biblioteka do funkcji systemowych np. malloc (alokacja pamieci)
#include "sudoku.h" // moj wlasny plik naglowkowy z definicjami gry


//Da dieses Sudoku „irritierend“ war (eine Untertreibung, aber höflich),
//werde ich es auf Polnisch und Deutsch kommentieren, damit Sie meine Nervosität spüren können

// Header funktioniert bei mir nicht, weil Clion ihre Periode hat

//funkcja pomocnicza do wyswietlania menu ladnie
void print_menu() {
    printf("\n==== MENU SUDOKU ====\n");
    printf("1. Nowa gra\n");
    printf("2. Instrukcja\n");
    printf("3. Wyjscie\n");
    printf("Wybierz opcje: ");
}

//funckja do wyswietlania instrukcji
void print_instructions() {
    printf("\n--- INSTRUKCJA ---\n");
    printf("Celem jest wypelnienie planszy liczbami zgodnie z zasadami Sudoku.\n");
    // moze dodaj tu lepsza instrukcje idk
    printf("Wybierz rozmiar planszy i poziom trudnosci, nastepnie graj!\n");
}

int main() {
    int opcja;

    // glowna petla programu -> dziala dopoki uzytkownik nie wybierze 3
    do {
        print_menu();
        scanf("%d", &opcja); // "odbierz wybor uzytkownika" (wpisuje liczbe)

        switch (opcja) {
        case 1: {
                int size, difficulty; // rozmiar planszy i poziom trudnosci
                printf("Wybierz rozmiar planszy (4, 9, 16): ");
                scanf("%d", &size); //pobierz rozmiar

                // tworzenie nowej gry - dynamiczne alokowanie planszy w pamieci
                SudokuGame* game = create_game(size);

                // generowanie wypelnionej planszy sudoku (z rozwiazaniem)
                generate_full_board(game);

                // pobieramy poziom trudnosci
                printf("Wybierz poziom trudnosci (1=latwy, 2=sredni, 3=trudny): ");
                scanf("%d", &difficulty);

                // usuwa liczby z planszy zgodnie z wybranym poziomem trudnosci
                remove_numbers(game, difficulty);

                print_board(game);

                //sprzatanko zwalniamy pamiec
                free_game(game);
                break;
        }
        case 2:
            print_instructions();
            break;
        case 3:
            //papa
            printf("Do zobaczenia!\n");
            break;
        default:
            printf("Nieprawidlowa opcja.\n");
        }
    } while (opcja != 3); //powtarzamy dopoki uzytwkonik nie wybierze

    return 0;
}