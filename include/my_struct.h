/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : struct header
*/

#ifndef _MY_HEADER_
    #define _MY_HEADER_
    #include "../include/my.h"
    #include "../include/structure/quadtree.h"
    #define BOOL int
    #define TRUE 1
    #define FALSE 0

typedef struct tower_s {
    sfSprite *sprite_tower;
    int pos_x;
    int pos_y;
    sfVector2f position;
    float radius;
    int count_tower;
    sfCircleShape *area_tower;
}tower_t;

typedef struct window {
    sfTexture *text_bk;
    sfSprite *sprite_bk;
    BOOL sprite_status;
    BOOL hitbox_status;
}window_t;

typedef struct main_s {
    sfFont *font;
    sfText *timer_text;
    tower_t *tower;
    sfVideoMode size;
    sfRenderWindow *window;
    window_t *wind;
    quadtree_node_t *quadtree;
    aircraft_t *aircraft;
    sfClock *my_clock;
    BOOL s_pressed;
    BOOL quad_pressed;
    BOOL hitbox_pressed;
}main_t;

#endif /* !_MY_HEADER_ */
