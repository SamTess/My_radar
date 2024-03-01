/*
** EPITECH PROJECT, 2023
** Libmy
** File description:
** my_strlen
*/
#include "include/my.h"

int my_strlen(char const *str)
{
    int len_char = 0;

    while (str[len_char] != '\0'){
        len_char++;
    }
    return (len_char);
}
