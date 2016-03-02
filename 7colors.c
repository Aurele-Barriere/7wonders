/*
  Aurele Barriere & Nathan Tommasset
  ARCSYS 2 
*/

#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include "defines.h"
#include "board.h"
#include "strategy.h"

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
