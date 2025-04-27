#ifndef SUDOKU_H //zabezpieczenie przed podwojnym zaladowaniem pliku
#define SUDOKU_H

#define MAX_SIZE 16

//struktura ktora reprezentuje gre sudoku
typedef struct {
    int size;
    int difficulty;
    int** board;   // podwjony wskaznik - dynamiczna tablica tablic (plansza)
    int** fixed; // 1 jeśli komorka jest podpowiedzią
} SudokuGame;

//funkcje do obslugi gry
SudokuGame* create_game(int size);  // erstellt ein Spiel
void free_game(SudokuGame* game); // Gibt Speicher nach dem Spiel frei
void print_board(SudokuGame* game); // Zeigt das Board an
void generate_full_board(SudokuGame* game); // Erzeugt ein vollständiges Board (Lösung)
void remove_numbers(SudokuGame* game, int difficulty); // // Entfernt Zahlen entsprechend der Ebene
void play_game(SudokuGame* game);

int make_move(SudokuGame* game, int row, int col, int num);
int is_game_complete(SudokuGame* game);



#endif //SUDOKU_H
