##
## EPITECH PROJECT, 2025
## sokoban
## File description:
## Makefile
##

CFILES = $(shell find ./src -name "*.c")

# CFLAGS = -Wall -Wextra -Werror

CLIBS = -lncurses -L./src/linkedlist/ -l:linkedlist.a

NAME = sokoban

all:
	make -C ./src/linkedlist
	gcc -o $(NAME) $(CFILES) $(CFLAGS) $(CLIBS)

clean:
# rm -f $(OFILES)
	make -C ./src/linkedlist clean

fclean: clean
	rm -f $(NAME)
	make -C ./src/linkedlist fclean

re: fclean all
	make -C ./src/linkedlist re

.PHONY: all clean fclean re
