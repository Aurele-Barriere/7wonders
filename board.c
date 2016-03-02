#include "board.h"
#include "defines.h"


char      board[BOARD_SIZE * BOARD_SIZE] = { 0 };
char test_board[BOARD_SIZE * BOARD_SIZE] = { 0 }; 

//get function. b points to a board
char get_cell(int x, int y, char * b) 
{
   return b[y*BOARD_SIZE + x];
}

//set function. b points to a board
void set_cell(int x, int y, char color, char * b) 
{
   b[y*BOARD_SIZE + x] = color;
}
