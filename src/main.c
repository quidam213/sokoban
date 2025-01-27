/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** main
*/

#include "sokoban.h"

int main(void)
{
    map_t *map = map_constructor();

    sokoban(map);
    map_destructor(map);
    return 0;
}
