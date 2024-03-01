/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar, function that create each subrectangle
*/
#include "../include/my.h"

void create_subrectangle_topleft(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft)
{
    double half_width = parent->quad_pos->width / 2.0;
    double half_height = parent->quad_pos->height / 2.0;

    *child = malloc(sizeof(quadtree_node_t));
    (*child)->quad_pos = malloc(sizeof(quadtree_pos_t));
    (*child)->next_quad = NULL;
    (*child)->aircraftlist = malloc(QUAD_LIMIT * sizeof(aircraft_t *));
    for (int i = 0; i < QUAD_LIMIT; ++i) {
        (*child)->aircraftlist[i] = NULL;
    }
    (*child)->quad_pos->x = parent->quad_pos->x;
    (*child)->quad_pos->y = parent->quad_pos->y;
    (*child)->quad_pos->width = half_width;
    (*child)->quad_pos->height = half_height;
    (*child)->count_aircraft = 0;
    create_rect(*child);
    generate_quadtree_recursive(child, all_aircraft, count_aircraft);
}

void create_subrectangle_topright(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft)
{
    double half_width = parent->quad_pos->width / 2.0;
    double half_height = parent->quad_pos->height / 2.0;

    *child = malloc(sizeof(quadtree_node_t));
    (*child)->quad_pos = malloc(sizeof(quadtree_pos_t));
    (*child)->next_quad = NULL;
    (*child)->aircraftlist = malloc(QUAD_LIMIT * sizeof(aircraft_t *));
    for (int i = 0; i < QUAD_LIMIT; ++i) {
        (*child)->aircraftlist[i] = NULL;
    }
    (*child)->quad_pos->x = parent->quad_pos->x + half_width;
    (*child)->quad_pos->y = parent->quad_pos->y;
    (*child)->quad_pos->width = half_width;
    (*child)->quad_pos->height = half_height;
    (*child)->count_aircraft = 0;
    create_rect(*child);
    generate_quadtree_recursive(child, all_aircraft, count_aircraft);
}

void create_subrectangle_botleft(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft)
{
    double half_width = parent->quad_pos->width / 2.0;
    double half_height = parent->quad_pos->height / 2.0;

    *child = malloc(sizeof(quadtree_node_t));
    (*child)->quad_pos = malloc(sizeof(quadtree_pos_t));
    (*child)->next_quad = NULL;
    (*child)->aircraftlist = malloc(QUAD_LIMIT * sizeof(aircraft_t *));
    for (int i = 0; i < QUAD_LIMIT; ++i) {
        (*child)->aircraftlist[i] = NULL;
    }
    (*child)->quad_pos->x = parent->quad_pos->x;
    (*child)->quad_pos->y = parent->quad_pos->y + half_height;
    (*child)->quad_pos->width = half_width;
    (*child)->quad_pos->height = half_height;
    (*child)->count_aircraft = 0;
    create_rect(*child);
    generate_quadtree_recursive(child, all_aircraft, count_aircraft);
}

void create_subrectangle_botright(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft)
{
    double half_width = parent->quad_pos->width / 2.0;
    double half_height = parent->quad_pos->height / 2.0;

    *child = malloc(sizeof(quadtree_node_t));
    (*child)->quad_pos = malloc(sizeof(quadtree_pos_t));
    (*child)->next_quad = NULL;
    (*child)->aircraftlist = malloc(QUAD_LIMIT * sizeof(aircraft_t *));
    for (int i = 0; i < QUAD_LIMIT; ++i) {
        (*child)->aircraftlist[i] = NULL;
    }
    (*child)->quad_pos->x = parent->quad_pos->x + half_width;
    (*child)->quad_pos->y = parent->quad_pos->y + half_height;
    (*child)->quad_pos->width = half_width;
    (*child)->quad_pos->height = half_height;
    (*child)->count_aircraft = 0;
    create_rect(*child);
    generate_quadtree_recursive(child, all_aircraft, count_aircraft);
}
