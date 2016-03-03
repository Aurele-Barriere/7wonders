#include <stdio.h>
#include <stdlib.h>
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
   printf("Frontier1: %d, Frontier2: %d", frontier(b,color1), frontier(b,color2));
   printf("\n");
   for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	printf("%c ", get_cell(i, j, b)+97);
      printf("\n");
   }
}

//checking board range
int in_board(int x, int y) {
  if (x>=0 && x< BOARD_SIZE && y>=0 && y<BOARD_SIZE) {
    return 1;}
  else {return 0;}
}

//update, given player, choice and board
void update_board(char player, char color, char * b) {

  int i,j;
  int change = 0;
  for (i=0; i<BOARD_SIZE; i++) {
    for (j=0; j<BOARD_SIZE; j++) {
      if (get_cell(i,j,b) == color) {
	if (in_board(i-1,j)) {if (get_cell(i-1,j,b) == player) {set_cell(i,j,player,b); change = 1;}}
	if (in_board(i+1,j)) {if (get_cell(i+1,j,b) == player) {set_cell(i,j,player,b); change = 1;}}
	if (in_board(i,j-1)) {if (get_cell(i,j-1,b) == player) {set_cell(i,j,player,b); change = 1;}}
	if (in_board(i,j+1)) {if (get_cell(i,j+1,b) == player) {set_cell(i,j,player,b); change = 1;}}
      }
    }
  }
  if (change) {update_board(player, color, b );}
  
}

//creates random board
void set_random_board() {
  int i, j;
  int r = 0;
  //RAND_MAX = NB_COLORS;
  for (i = 0; i< BOARD_SIZE; i++){
    for (j=0; j < BOARD_SIZE; j++) {
      r = rand() % NB_COLORS;
      set_cell(i,j,r,board);
    }
  }
  set_cell(0,BOARD_SIZE-1, color1,board);
  set_cell(BOARD_SIZE-1,0, color2,board);
}

//creates symetric board
void set_sym_board() {
  int i, j;
  int r = 0;
  //RAND_MAX = NB_COLORS;
  //first half
  for (i = 0; i< BOARD_SIZE; i++){
    for (j=i; j < BOARD_SIZE; j++) {
      r = rand() % NB_COLORS;
      set_cell(i,j,r,board);
    }
  }
  //second half
  for (i = 0; i<BOARD_SIZE; i++) {
    for (j = 0; j<i; j++) {
      set_cell(i,j,get_cell(j,i,board),board);
    }
  }
  set_cell(0,BOARD_SIZE-1, color1,board);
  set_cell(BOARD_SIZE-1,0, color2,board);
}

//calculates the score of a player on a board
int score (char * b, int color) {
  int i;
  int j;
  int s = 0;
  for (i = 0; i<BOARD_SIZE; i++) {
    for (j = 0; j<BOARD_SIZE; j++) {
      if (get_cell(i,j,b) == color) {
	s += 1;
      }
    }
  }
  return s;
}

//frontier for hegemony
int frontier (char * b, int color) {
  int f = 0;
  int i;
  int j;
  for (i = 0; i<BOARD_SIZE; i++) {
    for (j = 0; j<BOARD_SIZE; j++) {
      if (get_cell(i,j,b) != color) {
	if (in_board(i,j+1)) {
	  if (get_cell(i,j+1,b)==color) {
	    f += 1;
	    break;}}
	if (in_board(i,j-1)) {
	  if (get_cell(i,j-1,b)==color) {
	    f += 1;
	    break;}}
	if (in_board(i+1,j)) {
	  if (get_cell(i+1,j,b)==color) {
	    f += 1;
	    break;}}
	if (in_board(i-1,j)) {
	  if (get_cell(i-1,j,b)==color) {
	    f += 1;
	    break;}}
      }
    }
  }
  return f;
}




