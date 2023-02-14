
FLAGS = -Wall -g

wish: wish_parse.c
	gcc -o wish wish_parse.c $(FLAGS)
