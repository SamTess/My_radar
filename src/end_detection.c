/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : end detections functions
*/
#include "../include/my.h"

static int check_to_far(aircraft_pos_t *position)
{
    if (position->start_x >= position->end_x
        && position->start_y >= position->end_y) {
            return 1;
        }
    if (position->start_x <= position->end_x
        && position->start_y >= position->end_y) {
            return 2;
        }
    if (position->start_x >= position->end_x
        && position->start_y <= position->end_y) {
            return 3;
        }
    if (position->start_x <= position->end_x
        && position->start_y <= position->end_y) {
            return 4;
        }
}

static void check_end_continue(quadtree_node_t *quadtree, int i, int check)
{
    if (check == 3 && quadtree->aircraftlist[i]->pos_aircraft->x
        <= quadtree->aircraftlist[i]->pos_aircraft->end_x
        && quadtree->aircraftlist[i]->pos_aircraft->y
        >= quadtree->aircraftlist[i]->pos_aircraft->end_y) {
            if (quadtree->aircraftlist[i] != NULL) {
                quadtree->aircraftlist[i]->is_destroyed = TRUE;
            }
    }
    if (check == 4 && quadtree->aircraftlist[i]->pos_aircraft->x
        >= quadtree->aircraftlist[i]->pos_aircraft->end_x
        && quadtree->aircraftlist[i]->pos_aircraft->y
        >= quadtree->aircraftlist[i]->pos_aircraft->end_y) {
            if (quadtree->aircraftlist[i] != NULL) {
                quadtree->aircraftlist[i]->is_destroyed = TRUE;
            }
    }
}

static void check_end_bis(quadtree_node_t *quadtree, int i)
{
    int check = check_to_far(quadtree->aircraftlist[i]->pos_aircraft);

    if (check == 1 && quadtree->aircraftlist[i]->pos_aircraft->x
        <= quadtree->aircraftlist[i]->pos_aircraft->end_x
        && quadtree->aircraftlist[i]->pos_aircraft->y
        <= quadtree->aircraftlist[i]->pos_aircraft->end_y) {
            if (quadtree->aircraftlist[i] != NULL) {
                quadtree->aircraftlist[i]->is_destroyed = TRUE;
            }
    }
    if (check == 2 && quadtree->aircraftlist[i]->pos_aircraft->x
        >= quadtree->aircraftlist[i]->pos_aircraft->end_x
        && quadtree->aircraftlist[i]->pos_aircraft->y
        <= quadtree->aircraftlist[i]->pos_aircraft->end_y) {
            if (quadtree->aircraftlist[i] != NULL) {
                quadtree->aircraftlist[i]->is_destroyed = TRUE;
            }
    }
    check_end_continue(quadtree, i, check);
}

static void go_in_quad_end(quadtree_node_t **quadtree)
{
    if ((*quadtree)->next_quad == NULL)
        return;
    if (&((*quadtree)->next_quad->top_left) != NULL) {
        check_end(&(*quadtree)->next_quad->top_left);
    }
    if (&((*quadtree)->next_quad->top_right) != NULL) {
        check_end(&(*quadtree)->next_quad->top_right);
    }
    if (&((*quadtree)->next_quad->bot_left) != NULL) {
        check_end(&(*quadtree)->next_quad->bot_left);
    }
    if (&((*quadtree)->next_quad->bot_right) != NULL) {
        check_end(&(*quadtree)->next_quad->bot_right);
    }
}

void check_end(quadtree_node_t **quadtree)
{
    if ((*quadtree) == NULL || ((*quadtree)->count_aircraft == 0
        && (*quadtree)->is_divided == FALSE)) {
        return;
    }
    if ((*quadtree)->is_divided == TRUE) {
        go_in_quad_end(quadtree);
    }
    for (int i = 0; i < (*quadtree)->count_aircraft; i++) {
        if ((*quadtree)->aircraftlist[i] != NULL
        && (*quadtree)->aircraftlist[i]->pos_aircraft != NULL) {
            check_end_bis((*quadtree), i);
        }
    }
}
