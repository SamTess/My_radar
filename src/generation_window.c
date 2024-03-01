/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : generation main_window
*/
#include "../include/my.h"

void generation_window(window_t *wind)
{
    sfVector2f scale = {1, 1};

    wind->text_bk = sfTexture_createFromFile("assets/bk4.png", NULL);
    wind->sprite_bk = sfSprite_create();
    sfSprite_setTexture(wind->sprite_bk, wind->text_bk, sfTrue);
    sfSprite_setScale(wind->sprite_bk, scale);
}
