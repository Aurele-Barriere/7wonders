#include <stdio.h>
#include <stdlib.h>
#include "strategy.h"
#include "board.h"

//random
char alea () {
  char r =  rand() % 7;
  printf("Color chose by random AI : %c\n", r+97);
  //getchar();
  return r;
}

//random between useful colors
char alea_useful_colors(int player) {
  //chooses at random between colors that can make any progress
  int useful[NB_COLORS] = {0};
  int i,j;
  char color;
  int c;
  
  for (i = 0; i< BOARD_SIZE; i++) {
    for (j = 0; j< BOARD_SIZE; j++) {
      color = get_cell(i,j,board);
      if (color>=0 && color < BOARD_SIZE) {
	c = (int) color;
	if (useful[c]==0) {
	  if (in_board(i-1,j)) {if (get_cell(i-1,j,board) == player)  {useful[c] = 1;}}
	  if (in_board(i+1,j)) {if (get_cell(i+1,j,board) == player)  {useful[c] = 1;}}
	  if (in_board(i,j-1)) {if (get_cell(i,j-1,board) == player)  {useful[c] = 1;}}
	  if (in_board(i,j+1)) {if (get_cell(i,j+1,board) == player)  {useful[c] = 1;}}
	}
      }
    }
  }
  int sum = 0;
  for (i = 0; i< NB_COLORS; i++) {
    if (useful[i]) {sum++;}
  }
  int r =  rand() % sum;
  
  char decision;
  int choice = -1;
  for (i=0; i< NB_COLORS; i++) {
    if (useful[i]) {choice++;}
    if (choice == r) {decision = (char) i;break;} 
  }
  printf("\nColor chose by random_useful AI : %c\n", i+97);
  return decision;
}

//wrong greedy
char wrong_greedy(int player) {
  int occurrences[NB_COLORS] = {0};
  int i,j;
  char color;
  int c;
  
  for (i = 0; i< BOARD_SIZE; i++) {
    for (j = 0; j< BOARD_SIZE; j++) {
      color = get_cell(i,j,board);
      if (color>=0 && color < BOARD_SIZE) {
	c = (int) color;
	
	if (in_board(i-1,j)) {if (get_cell(i-1,j,board) == player)  {occurrences[c]++;}}
	if (in_board(i+1,j)) {if (get_cell(i+1,j,board) == player)  {occurrences[c]++;}}
	if (in_board(i,j-1)) {if (get_cell(i,j-1,board) == player)  {occurrences[c]++;}}
	if (in_board(i,j+1)) {if (get_cell(i,j+1,board) == player)  {occurrences[c]++;}}
	
      }
    }
  }
  int max = 0;
  char letter = 0;
  for (i = 0; i<NB_COLORS; i++) {
    if (occurrences[i] > max) {
      max = occurrences[i];
      letter = i;
    }
  }
  printf("\nColor chose by wrong greedy AI : %c\n", letter+97);
  return letter;
}

//true greedy ai
char greedy(int player) {
  int i =0;
  int val[NB_COLORS] = { 0 };
  for (i = 0; i< NB_COLORS; i++) {
    copy_board();
    update_board(player, i, test_board);
    val[i] = score(test_board, player);
  }
  printf("\n");
  int max = 0;
  char choice = 0;
  for (i=0; i<NB_COLORS; i++) {
    if (val[i]>=max) {
      max = val[i];
      choice = i;
    }
  }
  printf("color chose by true greedy AI : %c\n", choice +97);
  return choice;
}

//ask for the playe's choice
char player_choice(int player) {
  char c;
  printf("What color do you choose, player %d?\n", player);
  printf("Must be between a-g  \n");
  c = getchar();
  getchar();
  c -= 97;
  if (c >= 0 && c < NB_COLORS) {
    return c;}
  else {return player_choice(player);}
}
