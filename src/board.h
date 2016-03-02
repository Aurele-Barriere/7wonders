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

/** Is an element within the BOARD_SIZE range? */
int in_board(int x, int y);

/** Given a player and its choice, update the given board */
void update_board(char player, char color, char * b);

/** Creates a completely random board */
void set_random_board();

/** Creates a symetric board */
void set_sym_board();

/** Calculates score for a given player on a given board */
int score (char * b, int color);


#endif
