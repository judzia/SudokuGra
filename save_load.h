#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "sudoku.h"

void save_game(SudokuGame *game, const char *filename);
SudokuGame* load_game(const char *filename);

#endif
