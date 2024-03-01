/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : Quadtree
*/
#include "../include/my.h"

void create_rect(quadtree_node_t *quadtree)
{
    quadtree->quadtree_rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(quadtree->quadtree_rect, sfTransparent);
    sfRectangleShape_setOutlineColor(quadtree->quadtree_rect, sfYellow);
    sfRectangleShape_setOutlineThickness(quadtree->quadtree_rect, 1);
    sfRectangleShape_setPosition(quadtree->quadtree_rect,
        (sfVector2f){quadtree->quad_pos->x, quadtree->quad_pos->y});
    sfRectangleShape_setSize(quadtree->quadtree_rect,
        (sfVector2f){quadtree->quad_pos->width, quadtree->quad_pos->height});
}

void new_quadtree_node(quadtree_node_t **quadtree, main_t *main)
{
    (*quadtree)->quad_pos->x = 0;
    (*quadtree)->quad_pos->y = 0;
    (*quadtree)->quad_pos->width = main->size.width;
    (*quadtree)->quad_pos->height = main->size.height;
    (*quadtree)->id = id_quad;
    (*quadtree)->aircraftlist = malloc(sizeof(aircraft_t *) * QUAD_LIMIT);
    for (int i = 0; i < QUAD_LIMIT; ++i) {
        (*quadtree)->aircraftlist[i] = NULL;
    }
    id_quad += 1;
    (*quadtree)->count_aircraft = 0;
    (*quadtree)->is_divided = FALSE;
    create_rect((*quadtree));
}

static void check_aircraft_gen(aircraft_t *all_aircraft[],
    int i, quadtree_node_t *quadtree)
{
    if (all_aircraft[i]->pos_aircraft->x >= quadtree->quad_pos->x &&
        all_aircraft[i]->pos_aircraft->x <
        quadtree->quad_pos->x + quadtree->quad_pos->width &&
        all_aircraft[i]->pos_aircraft->y >= quadtree->quad_pos->y &&
        all_aircraft[i]->pos_aircraft->y <
        quadtree->quad_pos->y + quadtree->quad_pos->height
        && all_aircraft[i]->is_started == TRUE
        && all_aircraft[i]->is_destroyed == FALSE) {
            quadtree->aircraftlist[quadtree->count_aircraft] = all_aircraft[i];
            quadtree->count_aircraft += 1;
    }
}

static void go_in_quad_gen(quadtree_node_t **quadtree,
    aircraft_t *all_aircraft[], int count_aircraft)
{
    sfRectangleShape_destroy((*quadtree)->quadtree_rect);
    (*quadtree)->is_divided = TRUE;
    (*quadtree)->count_aircraft = 0;
    (*quadtree)->aircraftlist = NULL;
    (*quadtree)->next_quad = malloc(sizeof(next_quadtree_t));
    create_subrectangle_topleft((*quadtree),
        (&(*quadtree)->next_quad->top_left), all_aircraft, count_aircraft);
    create_subrectangle_topright((*quadtree),
        (&(*quadtree)->next_quad->top_right), all_aircraft, count_aircraft);
    create_subrectangle_botleft((*quadtree),
        (&(*quadtree)->next_quad->bot_left), all_aircraft, count_aircraft);
    create_subrectangle_botright((*quadtree),
        (&(*quadtree)->next_quad->bot_right), all_aircraft, count_aircraft);
}

void generate_quadtree_recursive(quadtree_node_t **quadtree,
    aircraft_t *all_aircraft[], int count_aircraft)
{
    int j = 0;

    for (int i = 1; i < count_aircraft; i++) {
        check_aircraft_gen(all_aircraft, i, (*quadtree));
        if ((*quadtree)->count_aircraft == QUAD_LIMIT)
            break;
        j = i;
    }
    if ((*quadtree)->count_aircraft == QUAD_LIMIT) {
        go_in_quad_gen(quadtree, all_aircraft, count_aircraft);
        return;
    }
}

void free_quadtree_recursive(quadtree_node_t **quadtree)
{
    if ((*quadtree)->is_divided == TRUE) {
        free_quadtree_recursive((&(*quadtree)->next_quad->top_left));
        free_quadtree_recursive((&(*quadtree)->next_quad->top_right));
        free_quadtree_recursive((&(*quadtree)->next_quad->bot_right));
        free_quadtree_recursive((&(*quadtree)->next_quad->bot_left));
    }
    (*quadtree)->next_quad = NULL;
    for (int i = 0; i < QUAD_LIMIT; ++i) {
        free((*quadtree)->aircraftlist[i]);
    }
    (*quadtree)->quad_pos = NULL;
    sfRectangleShape_destroy((*quadtree)->quadtree_rect);
    (*quadtree)->next_quad = NULL;
    free((*quadtree));
}

void generate_quadtree(main_t *main,
    quadtree_node_t **quadtree, aircraft_t *all_aircraft[], int count_air)
{
    sfTime time = sfClock_getElapsedTime(main->my_clock);
    int second = sfTime_asSeconds(time);

    new_quadtree_node(quadtree, main);
    put_finished_aircraft(all_aircraft, (*quadtree),
        main->my_clock, count_air);
    generate_quadtree_recursive(quadtree, all_aircraft, count_air);
    check_end(quadtree);
    print_aircraft_quad(main->window, quadtree, main->my_clock, main);
    check_collision(quadtree);
    if ((*quadtree)->count_aircraft == 0
    && (*quadtree)->is_divided == FALSE && second > 1) {
        sfRenderWindow_close(main->window);
    }
    if ((*quadtree)->first != 1) {
        free_quadtree_recursive(quadtree);
    }
    reset_is_in_tower(all_aircraft, count_air);
    sfRenderWindow_display(main->window);
}
