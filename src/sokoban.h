/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** sokoban
*/

#ifndef SOKOBAN_H_
#define SOKOBAN_H_

//? INCLUDES
#include <ncurses.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IDLE 0
#define WIN 1
#define LOOSE 2

#define SMALL_TERM "X"

//? STRUCTURES
enum type_element {
    NOTHING = ' ',
    PLAYER = 'P',
    WALL = '#',
    BOX = 'X',
    TARGET = 'O',
    POINT = 'V'
};

typedef struct element_s {
    //? attributs
    enum type_element type;
} element_t;

typedef struct map_s {
    //? attributs
    struct element_s ***elts;

    //? methods
    struct element_s * (* getElement) (struct map_s *, size_t, size_t);
    size_t (* countElements) (struct map_s *, enum type_element);
    size_t (* getPlayerX) (struct map_s *);
    size_t (* getPlayerY) (struct map_s *);
    size_t (* getHeight) (struct map_s *);
    size_t (* getWidth) (struct map_s *);
} map_t;

//? FILES
//* main.c
int main(int main, char **av);

//* sokoban.c
int sokoban(map_t *map);

//* map.c
map_t *map_constructor(char **content);
void map_destructor(map_t *this);

//* file.c
char **parse_file(char *filepath);
char **my_str_to_word_array(char *str, char *delim);
size_t count_words(char *str, char *delim);
void free_string_array(char **array);
size_t array_len(char **array);

#endif /* !SOKOBAN_H_ */
