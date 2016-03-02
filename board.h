#ifndef BOARD_H
#define BOARD_H
#include "defines.h"


extern char      board[BOARD_SIZE * BOARD_SIZE];
extern char test_board[BOARD_SIZE * BOARD_SIZE]; // to test things in our AI

/** Retrieves the color of a given board cell */
char get_cell(int x, int y, char * b) ;

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color, char * b);

/** Copying board into test_board to reset testing */
void copy_board();

/** Printing a given board */
void print_board(char *b);

#endif
