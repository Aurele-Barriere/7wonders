all: 7colors

7colors: 7colors.o board.o strategy.o
	gcc 7colors.o board.o strategy.o -o 7colors

7colors.o: 7colors.c
	gcc -Wall -Werror -Wextra 7colors.c -c -g

board.o: board.c
	gcc -Wall -Werror -Wextra board.c -c -g

strategy.o: strategy.c
	gcc -Wall -Werror -Wextra strategy.c -c -g
