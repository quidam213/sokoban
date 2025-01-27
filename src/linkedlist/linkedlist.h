/*
** EPITECH PROJECT, 2025
** linkedlist
** File description:
** linkedlist
*/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

//? INCLUDES
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//? STRUCTURES
typedef struct list_s {
    void *data;
    struct list_s *next;
    void (* freer) (struct list_s *);
} list_t;

//? FILES
//* list.c
void add_element(list_t **head, void *data, void (* node_freer) (struct list_s *));
bool delete_element_by_index(list_t **head, size_t i);
size_t get_list_len(list_t *head);
void free_list(list_t **head);
void char_displayer(void *data);
void str_displayer(void *data);
void display_list(list_t *head, void (*displayer) (void *));
bool char_equality(void *a_ptr, void *b_ptr);
bool is_in_list(list_t *head, void *data, bool (* equality) (void *, void *));
void reverse_list(list_t **head);
void sort_list(list_t **head, bool (* sort_checker) (list_t *), void (* operation) (list_t **));
void base_free_node(list_t *node);

#endif /* !LINKEDLIST_H_ */
