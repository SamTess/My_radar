/*
** EPITECH PROJECT, 2023
** mini_printf
** File description:
** printf which only take %d, %i, %s, %c, %%.
*/
#include "include/my.h"
#include <stdlib.h>
#include <stdarg.h>

int how_many(int temp)
{
    int i = 1;

    while (temp > 9) {
        temp /= 10;
        i++;
    }
    return i;
}

static int which_case2(char temp, va_list argument, int nb)
{
    int nbr = 0;

    if (temp == '%') {
        my_putchar('%');
        nb++;
    }
    if (temp == 'd' || temp == 'i') {
        nbr = va_arg(argument, int);
        my_put_nbr(nbr);
        nb += how_many(nbr);
    }
    return nb;
}

static int which_case(char temp, va_list argument, int nb)
{
    char const *str;

    if (temp == 'c') {
        my_putchar(va_arg(argument, int));
        nb++;
    }
    if (temp == 's') {
        str = va_arg(argument, char const *);
        nb += my_strlen(str);
        my_putstr(str);
    }
    return nb;
}

int mini_printf(char const *format, ...)
{
    va_list argument;
    int nb = 0;

    va_start(argument, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] != '%'){
            my_putchar(format[i]);
            nb++;
        }
        if (format[i] == '%') {
            format++;
            nb = which_case2(format[i], argument, nb);
            nb = which_case(format[i], argument, nb);
        }
    }
    va_end(argument);
    return nb;
}
