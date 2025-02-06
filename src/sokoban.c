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

static bool update_xy(int input, size_t *x, size_t *y)
{
    switch (input) {
        case 'z':
        case KEY_UP:
            (*y) --;
            break;
        case 's':
        case KEY_DOWN:
            (*y) ++;
            break;
        case 'q':
        case KEY_LEFT:
            (*x) --;
            break;
        case 'd':
        case KEY_RIGHT:
            (*x) ++;
            break;
        default:
            return false;
    }
    return true;
}

static void update_next_pos(element_t *prev_elt, element_t *next_elt)
{
    enum type_element prev_type = prev_elt->type;

    prev_elt->type = next_elt->type;
    next_elt->type = prev_type;
}

static void handle_box(
    map_t **map,
    element_t *prev_elt,
    element_t *next_elt,
    size_t x,
    size_t y
)
{
    enum type_element next_type;
    element_t *next_next_elt = NULL;
    size_t x_offset = x + (x - (*map)->getPlayerX(*map));
    size_t y_offset = y + (y - (*map)->getPlayerY(*map));

    next_next_elt = (*map)->getElement(*map, x_offset, y_offset);
    if (!next_next_elt) {
        return;
    }
    switch (next_next_elt->type) {
        case NOTHING:
            next_next_elt->type = BOX;
            break;
        case TARGET:
            next_next_elt->type = POINT;
            break;
        default:
            return;
    }
    prev_elt->type = NOTHING;
    next_elt->type = PLAYER;
}

static bool interpret_movements(
    map_t **map,
    element_t *prev_elt,
    element_t *next_elt,
    size_t x,
    size_t y
)
{
    switch (next_elt->type) {
        case BOX:
            handle_box(map, prev_elt, next_elt, x, y);
            break;
        case NOTHING:
            update_next_pos(prev_elt, next_elt);
            break;
        default:
            break;
    }
}

static bool handle_movements_input(map_t **map, int input)
{
    size_t x = (*map)->getPlayerX(*map);
    size_t y = (*map)->getPlayerY(*map);
    element_t *prev_elt = (*map)->getElement(*map, x, y);
    element_t *next_elt = NULL;

    if (!update_xy(input, &x, &y)) {
        return false;
    }
    next_elt = (*map)->getElement(*map, x, y);
    if (!prev_elt || !next_elt) {
        return true;
    }
    interpret_movements(map, prev_elt, next_elt, x, y);
    return true;
}

static void handle_input(map_t **map, int input)
{
    if (handle_movements_input(map, input)) {
        return;
    }
}

int sokoban(map_t *map)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    while (true) {
        clear();
        //! win/lose conds
        //! center display
        //! handle when terminal is too small
        display_map(map);
        handle_input(&map, getch());
        refresh();
    }
    endwin();
    return 0;
}
