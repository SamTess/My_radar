/*
** EPITECH PROJECT, 2023
** Libmy
** File description:
** my_putstr.c
*/
#include "../include/my.h"

int my_putstr(char const *str)
{
    int nb_char = 0;

    while (str[nb_char] != '\0') {
        my_putchar(str[nb_char]);
        nb_char++;
    }
    return 0;
}
