
FLAGS = -Wall -g

wish: wish.c
	gcc -o wish wish.c $(FLAGS)
