/** Strategies that can be used in the game */
#ifndef STRATEGY_H
#define STRATEGY_H

/** Chooses at random between all colors */
char alea();

/** Chosses at random between colors that are useful at this turn */
char alea_useful_colors(int player);

/** Bad attempt at greedy strategy */
char wrong_greedy(int player);

/** Good attempt at greedy strategy */
char greedy(int player);

/** Ask the player his choice */
char player_choice(int player);

/** Maximize the frontier */
char hegemony(int player);


#endif
