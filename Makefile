##
## EPITECH PROJECT, 2025
## sokoban
## File description:
## Makefile
##

CFILES = $(shell find ./src -name "*.c")

# CFLAGS = -Wall -Wextra -Werror

CLIBS = -lncurses

NAME = sokoban

all:
	gcc -o $(NAME) $(CFILES) $(CFLAGS) $(CLIBS)

clean:
# rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
