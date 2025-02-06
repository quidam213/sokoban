/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** sokoban
*/

#include "sokoban.h"

static void display_map(map_t *map) {
    size_t x = 0, y = 0;
    size_t w = 0, h = 0;
    size_t i = 0, j, k, l, p;

    if (!map || !map->elts) {
        return;
    }
    h = map->getHeight(map);
    w = map->getWidth(map);
    getmaxyx(stdscr, y, x);
    if (h > y || w > x) {
        return;
    }
    k = (y / 2) - (h / 2);
    while (map->elts[i]) {
        j = 0;
        l = (x / 2) - (w / 2);
        p = 0;
        while (map->elts[i][j]) {
            attron(COLOR_PAIR(map->elts[i][j]->type));
            mvaddch(k, l + p, ' ');
            mvaddch(k, l + p + 1, ' ');
            attron(COLOR_PAIR(NOTHING));
            j ++;
            l ++;
            p ++;
        }
        i ++;
        k ++;
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

static bool handle_others_input(map_t **map, int input, int *st)
{
    switch (input) {
        case 27: //? escape key
            (*st) = LOOSE;
            break;
        default:
            return false;
    }
    return true;
}

static void handle_input(int *st, map_t **map, int input)
{
    if (handle_movements_input(map, input)) {
        return;
    }
    if (handle_others_input(map, input, st)) {
        return;
    }
}

static int game_status(map_t *map)
{
    size_t n_target = map->countElements(map, TARGET);

    if (!map->countElements(map, TARGET)) {
        return WIN;
    }
    return IDLE;
}

static void init_ncurses(void)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    //? colors
    start_color();
    init_pair(NOTHING, COLOR_WHITE, COLOR_BLACK);
    init_pair(PLAYER, COLOR_BLUE, COLOR_BLUE);
    init_pair(BOX, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(POINT, COLOR_GREEN, COLOR_GREEN);
    init_pair(TARGET, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(WALL, COLOR_RED, COLOR_RED);
}

static void end_ncurses(void)
{
    endwin();
}

int sokoban(map_t *map)
{
    int st = 0;

    init_ncurses();
    while (!(st = game_status(map))) {
        clear();
        display_map(map);
        handle_input(&st, &map, getch());
        refresh();
    }
    end_ncurses();
    return st;
}
