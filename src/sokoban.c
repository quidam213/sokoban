/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** sokoban
*/

#include "sokoban.h"

element_t *init_element(enum type_element type, int x, int y, size_t id)
{
    element_t *elt = malloc(sizeof(element_t));

    elt->id = id;
    elt->type = type;
    elt->x = x;
    elt->y = y;
    return elt;
}

void free_element(list_t *node)
{
    element_t *elt = (element_t *)node->data;

    if (!elt) {
        return;
    }
    free(elt);
}

map_t *map_constructor(char **content)
{
    map_t *this = malloc(sizeof(map_t));
    size_t id = 0;

    this->elements = NULL;
    this->get_element = &map_get_element;
    this->add_element = &map_add_element;
    this->delete_element = &map_delete_element;
    for (size_t i = 0; content[i]; i ++) {
        for (size_t j = 0; content[i][j]; j ++) {
            this->add_element(&this, init_element(content[i][j], j, i, id));
            id ++;
        }
    }
    return this;
}

void map_destructor(map_t *this)
{
    if (!this) {
        return;
    }
    free_list(&this->elements);
    free(this);
}

element_t *map_get_element(map_t **this, size_t id)
{
    list_t *tmp;

    if (!(*this)) {
        return NULL;
    }
    tmp = (*this)->elements;
    while (tmp) {
        element_t *elt = (element_t *)tmp->data;
        if (elt->id == id) {
            return elt;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void map_add_element(map_t **this, element_t *elt)
{
    if (!(*this)) {
        return;
    }
    add_element(&(*this)->elements, (void *)elt, &free_element);
}

bool map_delete_element(map_t **this, size_t id)
{
    list_t *tmp;
    size_t i = 0;

    if (!(*this)) {
        return false;
    }
        tmp = (*this)->elements;
    while (tmp) {
        element_t *elt = (element_t *)tmp->data;
        if (elt->id == id) {
            return delete_element_by_index(&(*this)->elements, i);
        }
        tmp = tmp->next;
        i ++;
    }
    return false;
}

int sokoban(map_t *map)
{
    initscr();
    while (true) {
        for (list_t *tmp = map->elements; tmp; tmp = tmp->next) {
            element_t *elt = (element_t *)tmp->data;
            mvaddch(elt->y, elt->x, elt->type);
        }
        refresh();
    }
    endwin();
    return 0;
}
