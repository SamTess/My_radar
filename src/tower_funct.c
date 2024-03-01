/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : check control zone of tower
*/

#include "../include/my.h"

static void check_tower_bis(int j, int i, tower_t *all_tower[],
    aircraft_t *all_aircraft[])
{
    double rad = (double)(all_tower[j]->radius) / 2;
    double closest_x = fmax(all_aircraft[i]->pos_aircraft->x,
        fmin((all_tower[j]->pos_x + rad),
        all_aircraft[i]->pos_aircraft->x + 20));
    double closest_y = fmax(all_aircraft[i]->pos_aircraft->y,
        fmin((all_tower[j]->pos_y + rad),
        all_aircraft[i]->pos_aircraft->y + 20));
    double distance_1 = closest_x - (all_tower[j]->pos_x + rad);
    double distance_2 = closest_y - (all_tower[j]->pos_y + rad);
    double result = sqrt(distance_1 * distance_1 + distance_2 * distance_2);

    if (result <= all_tower[j]->radius) {
        all_aircraft[i]->is_in_tower = TRUE;
    }
    if (result > all_tower[j]->radius
        && all_aircraft[i]->is_in_tower != TRUE) {
            all_aircraft[i]->is_in_tower = FALSE;
    }
}

void check_tower_control(tower_t *all_tower[],
    aircraft_t *all_aircraft[], int count_air, int count_tow)
{
    for (int j = 0; j < count_tow; j++) {
        for (int i = 1; i < count_air; i++) {
            check_tower_bis(j, i, all_tower, all_aircraft);
        }
    }
}

static void put_shape(tower_t *all_tower[],
    int count, sfTexture *text, int i)
{
        sfSprite_setTexture(all_tower[i]->sprite_tower, text, sfTrue);
        sfSprite_setPosition(all_tower[i]->sprite_tower,
            (sfVector2f){all_tower[i]->pos_x
            + (sfTexture_getSize(text).y * 0.08),
            all_tower[i]->pos_y + (sfTexture_getSize(text).x * 0.08)});
        sfSprite_setScale(all_tower[i]->sprite_tower,
            (sfVector2f){0.08, 0.08});
        sfCircleShape_setPosition(all_tower[i]->area_tower,
            (sfVector2f){all_tower[i]->pos_x - ((all_tower[i]->radius / 2)),
            all_tower[i]->pos_y - ((all_tower[i]->radius / 2))});
        sfCircleShape_setRadius(all_tower[i]->area_tower,
            all_tower[i]->radius);
        sfCircleShape_setFillColor(all_tower[i]->area_tower, sfTransparent);
        sfCircleShape_setOutlineThickness(all_tower[i]->area_tower, 1);
        sfCircleShape_setOutlineColor(all_tower[i]->area_tower, sfWhite);
}

void print_tower_wind(tower_t *all_tower[], int count)
{
    sfTexture *text = sfTexture_createFromFile("assets/tower.png", NULL);

    if (all_tower == NULL)
        return;
    for (int i = 0; i < count; i++) {
        if (all_tower[i] == NULL)
            continue;
        all_tower[i]->sprite_tower = sfSprite_create();
        all_tower[i]->radius += 100;
        all_tower[i]->area_tower = sfCircleShape_create();
        put_shape(all_tower, count, text, i);
    }
}

void print_tower(tower_t *all_tower[],
    sfRenderWindow *window, int count, main_t *core)
{
    for (int i = 0; i < count; i++) {
        if (core->s_pressed == TRUE) {
            sfRenderWindow_drawSprite(window,
                all_tower[i]->sprite_tower, NULL);
        }
        if (core->hitbox_pressed == TRUE) {
            sfRenderWindow_drawCircleShape(window,
                all_tower[i]->area_tower, NULL);
        }
    }
}
