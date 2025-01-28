/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** sokoban
*/

#include "sokoban.h"

map_t *map_constructor(char **content)
{
    map_t *this = malloc(sizeof(map_t));

    this->elements = NULL;
    this->get_element = &map_get_element;
    this->add_element = &map_add_element;
    this->delete_element = &map_delete_element;
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

element_t *map_get_element(map_t *this, size_t id)
{
    list_t *tmp;

    if (!this) {
        return NULL;
    }
    tmp = this->elements;
    while (tmp) {
        element_t *elt = (element_t *)tmp->data;
        if (elt->id == id) {
            return elt;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void map_add_element(map_t *this, element_t *elt)
{
    if (!this) {
        return;
    }
    add_element(&this->elements, (void *)elt, &base_free_node);
}

bool map_delete_element(map_t *this, size_t id)
{
    list_t *tmp;
    size_t i = 0;

    if (!this) {
        return false;
    }
        tmp = this->elements;
    while (tmp) {
        element_t *elt = (element_t *)tmp->data;
        if (elt->id == id) {
            return delete_element_by_index(&this->elements, i);
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
        refresh();
    }
    endwin();
    return 0;
}
