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
    struct element_s * (* get_element) (struct map_s *, size_t);
    void (* add_element) (struct map_s *, struct element_s *);
    bool (* delete_element) (struct map_s *, size_t);
} map_t;

//? FILES
//* main.c
int main(void);

//* sokoban.c
int sokoban(map_t *map);
map_t *map_constructor(void);
void map_destructor(map_t *this);
element_t *map_get_element(map_t *this, size_t id);
void map_add_element(map_t *this, element_t *elt);
bool map_delete_element(map_t *this, size_t id);

#endif /* !SOKOBAN_H_ */
