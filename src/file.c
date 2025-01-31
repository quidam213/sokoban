/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** file
*/

#include "sokoban.h"

size_t count_words(char *str, char *delim)
{
    size_t n = 0, i = 0;
    bool in_word = false;

    if (!str) {
        return 0;
    }
    while (str[i] != '\0') {
        if (strchr(delim, str[i]) == NULL) {
            if (!in_word) {
                n++;
                in_word = true;
            }
        } else {
            in_word = false;
        }
        i ++;
    }
    return n;
}

char **my_str_to_word_array(char *str, char *delim)
{
    char **array = NULL;
    char *token = NULL, *rest = str;
    size_t i = 0;

    if (!str || !delim) {
        return NULL;
    }
    array = malloc(sizeof(char *) * (count_words(str, delim) + 1));
    while ((token = __strtok_r(rest, delim, &rest))) {
        array[i] = strdup(token);
        i ++;
    }
    array[i] = NULL;
    return array;
}

void free_string_array(char **array)
{
    if (!array) {
        return;
    }
    for (size_t i = 0; array[i]; i ++) {
        free(array[i]);
    }
    free(array);
}

char **parse_file(char *filepath)
{
    int fd;
    struct stat st;
    char *content = NULL, **array = NULL;

    if (!filepath) {
        return NULL;
    }
    if (stat(filepath, &st) == -1) {
        return NULL;
    }
    if ((st.st_mode & S_IFMT) != S_IFREG) {
        return NULL;
    }
    if ((fd = open(filepath, O_RDONLY)) == -1) {
        return NULL;
    }
    content = malloc(sizeof(char) * (st.st_size + 1));
    if (!content) {
        return NULL;
    }
    if (read(fd, content, st.st_size) == -1) {
        free(content);
        return NULL;
    }
    content[st.st_size] = '\0';
    array = my_str_to_word_array(content, "\n");
    free(content);
    return array;
}

size_t array_len(char **array)
{
    size_t i = 0;

    if (!array) {
        return i;
    }
    while (array[i]) {
        i ++;
    }
    return i;
}
