/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** sokoban
*/

#include "sokoban.h"

static void display_map(map_t *map) {
    size_t i = 0, j;

    if (!map || !map->elts) {
        return;
    }
    while (map->elts[i]) {
        j = 0;
        while (map->elts[i][j]) {
            mvaddch(i, j, map->elts[i][j]->type);
            j ++;
        }
        i ++;
    }
}

int sokoban(map_t *map)
{
    initscr();
    while (true) {
        display_map(map);
        refresh();
    }
    endwin();
    return 0;
}
