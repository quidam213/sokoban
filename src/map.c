/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** map
*/

#include "sokoban.h"

// element_t *init_element(enum type_element type, int x, int y, size_t id)
// {
//     element_t *elt = malloc(sizeof(element_t));

//     elt->id = id;
//     elt->type = type;
//     elt->x = x;
//     elt->y = y;
//     return elt;
// }

static element_t *map_get_element(map_t *this, size_t x, size_t y)
{
    if (!this) {
        return NULL;
    }
    if (this->getWidth(this) <= x) {
        return NULL;
    }
    if (this->getHeight(this) <= y) {
        return NULL;
    }
    return this->elts[y][x];
}

static size_t map_get_height(map_t *this)
{
    size_t i = 0;

    if (!this) {
        return i;
    }
    while (this->elts[i]) {
        i ++;
    }
    return i;
}

static size_t map_get_width(map_t *this)
{
    size_t i = 0, j, max_j = 0;

    if (!this) {
        return i;
    }
    while (this->elts[i]) {
        j = 0;
        while (this->elts[i][j]) {
            j ++;
        }
        if (max_j < j) {
            max_j = j;
        }
    }
    return j;
}

static size_t map_count_elements(map_t *this, enum type_element type)
{
    size_t i = 0, j, n = 0;

    if (!this) {
        return n;
    }
    while (this->elts[i]) {
        j = 0;
        while (this->elts[i][j]) {
            if (this->elts[i][j]->type == type) {
                n ++;
            }
            j ++;
        }
        i ++;
    }
    return n;
}

static size_t map_get_player_x(map_t *this)
{
    size_t i = 0, j;

    if (!this) {
        return 0;
    }
    while (this->elts[i]) {
        j = 0;
        while (this->elts[i][j]) {
            if (this->elts[i][j]->type == PLAYER) {
                return j;
            }
            j ++;
        }
        i ++;
    }
    return 0;
}

static size_t map_get_player_y(map_t *this)
{
    size_t i = 0, j;

    if (!this) {
        return 0;
    }
    while (this->elts[i]) {
        j = 0;
        while (this->elts[i][j]) {
            if (this->elts[i][j]->type == PLAYER) {
                return i;
            }
            j ++;
        }
        i ++;
    }
    return 0;
}

static element_t ***init_elements(char **content)
{
    size_t i = 0, j;
    element_t ***elts = NULL;

    if (!content) {
        return NULL;
    }
    elts = malloc(sizeof(element_t **) * (array_len(content) + 1));
    while (content[i]) {
        j = 0;
        elts[i] = malloc(sizeof(element_t *) * (strlen(content[i]) + 1));
        while (content[i][j] != '\0') {
            elts[i][j] = malloc(sizeof(element_t));
            elts[i][j]->type = content[i][j];
            j ++;
        }
        elts[i][j] = NULL;
        i ++;
    }
    elts[i] = NULL;
    return elts;
}

static void init_methods(map_t **this)
{
    (*this)->getElement = &map_get_element;
    (*this)->getHeight = &map_get_height;
    (*this)->getWidth = &map_get_width;
    (*this)->countElements = &map_count_elements;
    (*this)->getPlayerX = &map_get_player_x;
    (*this)->getPlayerY = &map_get_player_y;
}

map_t *map_constructor(char **content)
{
    map_t *this = malloc(sizeof(map_t));

    init_methods(&this);
    this->elts = init_elements(content);
    if (!this->elts) {
        free(this);
        return NULL;
    }
    return this;
}

void map_destructor(map_t *this)
{
    size_t i = 0, j;

    if (!this) {
        return;
    }
    if (this->elts) {
        while (this->elts[i]) {
            j = 0;
            while (this->elts[i][j]) {
                free(this->elts[i][j]);
                j ++;
            }
            free(this->elts[i]);
            i ++;
        }
        free(this->elts);
    }
    free(this);
}
