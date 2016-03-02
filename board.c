#include <stdio.h>
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

//copying board into test_board
void copy_board() {
  int i;
  int j;
  for (i = 0; i<BOARD_SIZE; i++) {
    for (j=0; j<BOARD_SIZE; j++) {
      set_cell(i,j,get_cell(i,j,board),test_board);
    }
  }
}

//prints board
void print_board(char * b) 
{
   int i, j;
   for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	printf("%c ", get_cell(i, j, b)+97);
      printf("\n");
   }
}
