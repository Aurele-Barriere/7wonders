/*
  Aurele Barriere & Nathan Tommasset
  ARCSYS 2 
*/


#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include "defines.h"
#include "board.h"


char alea () {
  char r =  rand() % 7;
  printf("Color chose by random AI : %c\n\n\n\n\n", r+97);
  //getchar();
  return r;
}



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

char wrong_greedy(int player) {
  //chooses at random between colors that can make any progress
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



char player_choice(int p) {
  char c;
  //print_board();
  //printf("Score 1 : %d%%\tScore 2 : %d%%\n",score1*100/(BOARD_SIZE*BOARD_SIZE),score2*100/(BOARD_SIZE*BOARD_SIZE));
  printf("What color do you choose, player %d?\n", p);
  printf("Must be between a-g  \n");
  c = getchar();
  getchar();
  c -= 97;
  if (c >= 0 && c < NB_COLORS) {
    return c;}
  else {return player_choice(p);}
}

/** Program entry point */
int main() 
{
  srand(time(NULL));
  int player =  rand() % 2; //which player begins
  printf("<<<<<<<<%d<<<<<<<\n", player);
  int score1 = 0;
  int score2 = 0;
  int limit = BOARD_SIZE * BOARD_SIZE /2 ;
  
  char choice ;
   
   printf("\n\n  Welcome to the 7 wonders of the wonderful world of the 7 wonderful colors\n"
	      "  *****************************************************\n\n"
	 "Current wonderful board state:\n");
   set_sym_board();
   //print_board();

   while(score1 <= limit && score2 <= limit) {
     score1 = score(board,color1);
     score2 = score(board,color2);
     printf("Score 1 : %d%%\tScore 2 : %d%%\n",score1*100/(BOARD_SIZE*BOARD_SIZE),score2*100/(BOARD_SIZE*BOARD_SIZE));
     print_board(board);
     if (player) {choice =greedy(color2);}
     else {choice = player_choice(player);}
     if (player) {update_board(color2, choice, board);}
     else {update_board(color1, choice, board);}
     player = 1-player;
       
   }
   print_board(board);
   printf("Score 1 : %d%%\tScore 2 : %d%%\n",score1*100/(BOARD_SIZE*BOARD_SIZE),score2*100/(BOARD_SIZE*BOARD_SIZE));


   return 0; // Everything went well
}
