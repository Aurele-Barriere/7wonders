/* Template of the 7 wonders of the world of the 7 colors assigment. */

/* Cf. http://people.irisa.fr/Anne-Cecile.Orgerie/teaching2015.html  */

#include <stdio.h>  /* printf */
#include <stdlib.h>
#include <time.h>


/* We want a 30x30 board game by default */
#define BOARD_SIZE 50 
#define NB_COLORS 7
#define color1 -3
#define color2 64-97


/** Represent the actual current board game 
 * 
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *  an appropriate data structure would also be preferred), but don't worry. 
 *  For this first assignment, no dinosaure will get you if you do that. 
 */
char      board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros
char test_board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // to test things in our AI

/** Retrieves the color of a given board cell */
char get_cell(int x, int y, char * b) 
{
   return b[y*BOARD_SIZE + x];
}

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color, char * b) 
{
   b[y*BOARD_SIZE + x] = color;
}
   
/** Prints the current state of the board on screen
 * 
 * Implementation note: It would be nicer to do this with ncurse or even 
 * SDL/allegro, but this is not really the purpose of this assignment.
 */
void print_board() 
{
   int i, j;
   for (i=0; i<BOARD_SIZE; i++) {
      for (j=0; j<BOARD_SIZE; j++) 
	printf("%c ", get_cell(i, j, board)+97);
      printf("\n");
   }
}

int in_board(int x, int y) {
  if (x>=0 && x< BOARD_SIZE && y>=0 && y<BOARD_SIZE) {
    return 1;}
  else {return 0;}
}


void update_board(char player, char color, char * b) {
  int i,j;
  int change = 0;
  for (i=0; i<BOARD_SIZE; i++) {
    for (j=0; j<BOARD_SIZE; j++) {
      if (get_cell(i,j,board) == color) {
	if (in_board(i-1,j)) {if (get_cell(i-1,j,board) == player) {set_cell(i,j,player,b); change = 1;}}
	if (in_board(i+1,j)) {if (get_cell(i+1,j,board) == player) {set_cell(i,j,player,b); change = 1;}}
	if (in_board(i,j-1)) {if (get_cell(i,j-1,board) == player) {set_cell(i,j,player,b); change = 1;}}
	if (in_board(i,j+1)) {if (get_cell(i,j+1,board) == player) {set_cell(i,j,player,b); change = 1;}}
      }
    }
  }
  if (change) {update_board(player, color, board );}	
}

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

char greedy(int player) {
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
  printf("\nColor chose by greedy AI : %c\n", letter+97);
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
     print_board();
     if (player) {choice =greedy(color2);}
     else {choice = player_choice(player);}
     if (player) {update_board(color2, choice, board);}
     else {update_board(color1, choice, board);}
     player = 1-player;
       
   }
   print_board();
   printf("Score 1 : %d%%\tScore 2 : %d%%\n",score1*100/(BOARD_SIZE*BOARD_SIZE),score2*100/(BOARD_SIZE*BOARD_SIZE));


   return 0; // Everything went well
}