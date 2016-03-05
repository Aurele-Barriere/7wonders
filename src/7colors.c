/*
  Aurele Barriere & Nathan Tommasset
  ARCSYS 2
*/

extern int printing;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"
#include "board.h"
#include "strategy.h"


/** Victory condition */
int victory(int score1, int score2) {
  int limit = (BOARD_SIZE*BOARD_SIZE)/2;
  if (score1>limit || score2>limit) {
    return 1;
  }
  return 0;
}


/** Draw condition */
int draw(int score1, int score2) {
  int limit = (BOARD_SIZE*BOARD_SIZE)/2;
  if (score1 == limit && score2 == limit) {
    return 1;
  }
  return 0;
}

/** Game. returns the number of the winner (1 or 2 or 0 for draw). Specify with boolean printing if the programm should print anything */
int game(int print) {
  printing = print;
  int player =  rand() % 2; //which player begins
  int score1 = 0;
  int score2 = 0;
  char choice ;

  if(printing){printf("\n\n  Welcome to the 7 wonders of the wonderful world of the 7 wonderful colors\n");}
   set_sym_board();

   while(!victory(score1, score2) && !draw(score1,score2)) {
     if(printing){print_board(board);}
     if (player) {choice =greedy(color2);}
     else {choice = starve(color1);}
     if (player) {update_board(color2, choice, board);}
     else {update_board(color1, choice, board);}
     player = 1-player;
     score1 = score(board,color1);
     score2 = score(board,color2);
     if(printing){printf("Score 1 : %d%%\tScore 2 : %d%%\n",score1*100/(BOARD_SIZE*BOARD_SIZE),score2*100/(BOARD_SIZE*BOARD_SIZE));}
   }

   if (draw(score1, score2)) {return 0;}
   if (score1>score2) {return 1;}
   if (score2>score1) {return 2;}

  return 0;
}


/** Program entry point */
int main()
{
  srand(time(NULL)); //initializing random
  int i;

  for (i = 0; i<100; i++) {
    printf("%d\n", game(0));
  }
  return 0;
}
