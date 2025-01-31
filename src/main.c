/*
** EPITECH PROJECT, 2025
** sokoban
** File description:
** main
*/

#include "sokoban.h"

static void dash_help(void)
{
    printf(
        "USAGE\n     " \
        "./my_sokoban [map]\n" \
        "DESCRIPTION\n     " \
        "map file representing the warehouse map, " \
        "containing ‘#’ for walls,\n     " \
        "‘P’ for the player, ‘X’ for boxes and ‘O’ " \
        "for storage locations.\n"
    );
}

static bool check_args(int ac, char **av)
{
    if (ac != 2) {
        dash_help();
        return false;
    }
    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0) {
        dash_help();
        return false;
    }
    return true;
}

int main(int ac, char **av)
{
    map_t *map = NULL;
    char **file_content = NULL;

    if (!check_args(ac, av)) {
        return 84;
    }
    file_content = parse_file(av[1]);
    if (!file_content) {
        return 84;
    }
    map = map_constructor(file_content);
    free_string_array(file_content);
    if (!map || map->countElements(map, PLAYER) != 1) {
        return 84;
    }
    sokoban(map);
    map_destructor(map);
    return 0;
}
