/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : structure quadtree
*/

#ifndef _MY_QUAD_
    #define _MY_QUAD_
    #include "../my.h"
    #define BOOL int
    #define TRUE 1
    #define FALSE 0

typedef struct aircraft_pos_s {
    float x;
    float y;
    float start_x;
    float start_y;
    float end_x;
    float end_y;
}aircraft_pos_t;

typedef struct aircraft_s {
    aircraft_pos_t *pos_aircraft;
    sfSprite *sprite_aircraft;
    sfRectangleShape *rect_aircraft;
    float delay;
    float speed;
    BOOL is_in_tower;
    BOOL is_started;
    BOOL is_destroyed;
}aircraft_t;

typedef struct next_quadtree_s {
    struct quadtree_node_s *top_left;
    struct quadtree_node_s *top_right;
    struct quadtree_node_s *bot_left;
    struct quadtree_node_s *bot_right;
}next_quadtree_t;

typedef struct quadtree_pos_s {
    float x;
    float y;
    float width;
    float height;
}quadtree_pos_t;

typedef struct quadtree_node_s {
    int id;
    int count_aircraft;
    int first;
    BOOL is_divided;
    aircraft_t **aircraftlist;
    quadtree_pos_t *quad_pos;
    next_quadtree_t *next_quad;
    sfRectangleShape *quadtree_rect;
}quadtree_node_t;

#endif /* !_MY_QUAD_ */
