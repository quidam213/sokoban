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
#include "linkedlist/linkedlist.h"

//? STRUCTURES
enum type_element {
    NOTHING = ' ',
    PLAYER = 'P',
    WALL = '#',
    BOX = 'X',
    TARGET = 'O'
};

typedef struct element_s {
    //? attributs
    enum type_element type;
    size_t id;
    int x;
    int y;
} element_t;

typedef struct map_s {
    //? attributs
    struct list_s *elements;

    //? methods
    struct element_s * (* get_element) (size_t id);
    bool (* delete_element) (size_t id);
    void (* add_element) (struct element_s *);
} map_t;

//? FILES
//* main.c
int main(void);

//* sokoban.c
int sokoban(void);

#endif /* !SOKOBAN_H_ */
