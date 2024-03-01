/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : dection of collisions functions
*/

#include "../include/my.h"

int detection_collision(aircraft_t *current, aircraft_t *next)
{
    int x1 = current->pos_aircraft->x;
    int y1 = current->pos_aircraft->y;
    int x2 = next->pos_aircraft->x;
    int y2 = next->pos_aircraft->y;

    if (x1 <= x2 + 20 && x1 + 20 >= x2
        && y1 <= y2 + 20 && y1 + 20 >= y2
        && current->is_started == TRUE
        && next->is_started == TRUE
        && current->is_in_tower == FALSE
        && next->is_in_tower == FALSE) {
            return TRUE;
        } else {
            return FALSE;
    }
}

static void check_collision_quad(quadtree_node_t *quadtree)
{
    if (quadtree->next_quad == NULL)
        return;
    if (&(quadtree->next_quad->top_left) != NULL) {
        check_collision((&(quadtree->next_quad->top_left)));
    }
    if (&(quadtree->next_quad->top_right) != NULL) {
        check_collision((&(quadtree->next_quad->top_right)));
    }
    if (&(quadtree->next_quad->top_left) != NULL) {
        check_collision((&(quadtree->next_quad->bot_left)));
    }
    if (&(quadtree->next_quad->top_left) != NULL) {
        check_collision((&(quadtree->next_quad->bot_right)));
    }
}

static void check_collision_bis(quadtree_node_t **quadtree,
    aircraft_t *current, int i)
{
    aircraft_t *next = NULL;

    for (int j = 0; j < (*quadtree)->count_aircraft
        && current != NULL; j++) {
        if (current == (*quadtree)->aircraftlist[j])
            continue;
        if ((*quadtree)->aircraftlist[j] != NULL) {
            next = (*quadtree)->aircraftlist[j];
        } else {
            next = NULL;
            continue;
        }
        if (detection_collision(current, next) == TRUE) {
            (*quadtree)->aircraftlist[i]->is_destroyed = TRUE;
            (*quadtree)->aircraftlist[j]->is_destroyed = TRUE;
            j = (*quadtree)->count_aircraft;
        }
        next = NULL;
    }
}

void check_collision(quadtree_node_t **quadtree)
{
    aircraft_t *current = NULL;

    if ((*quadtree) == NULL)
        return;
    if ((*quadtree)->is_divided == TRUE)
        check_collision_quad((*quadtree));
    for (int i = 0; i < (*quadtree)->count_aircraft; i++) {
        if ((*quadtree)->aircraftlist[i] != NULL) {
            current = (*quadtree)->aircraftlist[i];
        } else {
            current = NULL;
        }
        check_collision_bis(quadtree, current, i);
        current = NULL;
    }
}

void put_finished_aircraft(aircraft_t *all_aircraft[],
    quadtree_node_t *quadtree, sfClock *my_clock, int count)
{
    sfTime time_elapsed = sfClock_getElapsedTime(my_clock);
    float second = sfTime_asSeconds(time_elapsed);

    for (int i = 0; i < count; i++) {
        if (all_aircraft[i] == NULL) {
            continue;
        }
        if (second > all_aircraft[i]->delay) {
            all_aircraft[i]->is_started = TRUE;
        } else {
            all_aircraft[i]->is_started = FALSE;
        }
    }
}

void reset_is_in_tower(aircraft_t *all_aircraft[], int count)
{
    for (int i = 0; i < count; i++) {
        if (all_aircraft[i] == NULL)
            continue;
        all_aircraft[i]->is_in_tower = FALSE;
    }
}
