/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : print aircraft
*/
#include "../include/my.h"

static void go_in_quad(sfRenderWindow *window,
    quadtree_node_t *quadtree, sfClock *my_clock, main_t *core)
{
    if (quadtree->next_quad == NULL)
        return;
    if (&(quadtree->next_quad->top_left) != NULL) {
        print_aircraft_quad(window,
            (&(quadtree->next_quad->top_left)), my_clock, core);
    }
    if (&(quadtree->next_quad->top_right) != NULL) {
        print_aircraft_quad(window,
            (&(quadtree->next_quad->top_right)), my_clock, core);
    }
    if (&(quadtree->next_quad->top_left) != NULL) {
        print_aircraft_quad(window,
            (&(quadtree->next_quad->bot_left)), my_clock, core);
    }
    if (&(quadtree->next_quad->top_left) != NULL) {
        print_aircraft_quad(window,
            (&(quadtree->next_quad->bot_right)), my_clock, core);
    }
}

static void render_wind_air(main_t *core, quadtree_node_t *quadtree, int i)
{
    if (quadtree->aircraftlist[i] == NULL)
        return;
    if (quadtree->aircraftlist[i]->sprite_aircraft == NULL)
        return;
    if (quadtree->aircraftlist[i]->rect_aircraft == NULL)
        return;
    if (core->s_pressed == TRUE) {
        sfRenderWindow_drawSprite(core->window,
            quadtree->aircraftlist[i]->sprite_aircraft, NULL);
    }
    if (core->hitbox_pressed == TRUE) {
        sfRenderWindow_drawRectangleShape(core->window,
            quadtree->aircraftlist[i]->rect_aircraft, NULL);
    }
}

static void set_new_pose(quadtree_node_t *quadtree, float second, int i)
{
    float pos_end_x = quadtree->aircraftlist[i]->pos_aircraft->end_x;
    float pos_end_y = quadtree->aircraftlist[i]->pos_aircraft->end_y;
    float pos_start_x = quadtree->aircraftlist[i]->pos_aircraft->start_x;
    float pos_start_y = quadtree->aircraftlist[i]->pos_aircraft->start_y;
    float distance = pos_end_x - pos_start_x;
    float distance2 = pos_end_y - pos_start_y;
    float bef_time = sqrt(distance * distance + distance2 * distance2);
    float time = bef_time / quadtree->aircraftlist[i]->speed;
    float t = second / time;

    quadtree->aircraftlist[i]->pos_aircraft->x = pos_start_x + (t * distance);
    quadtree->aircraftlist[i]->pos_aircraft->y = pos_start_y + (t * distance2);
    sfSprite_setPosition(quadtree->aircraftlist[i]->sprite_aircraft,
        (sfVector2f){quadtree->aircraftlist[i]->pos_aircraft->x,
        quadtree->aircraftlist[i]->pos_aircraft->y});
    sfRectangleShape_setPosition(quadtree->aircraftlist[i]->rect_aircraft,
        (sfVector2f){quadtree->aircraftlist[i]->pos_aircraft->x,
        quadtree->aircraftlist[i]->pos_aircraft->y});
}

static void set_outline_color(quadtree_node_t *quadtree, int i)
{
    if (quadtree->aircraftlist[i]->is_in_tower == TRUE) {
        sfRectangleShape_setOutlineColor(quadtree
        ->aircraftlist[i]->rect_aircraft, sfBlue);
    } else {
        sfRectangleShape_setOutlineColor(quadtree->aircraftlist[i]
        ->rect_aircraft, sfRed);
    }
}

static void print_air_quad(main_t *core,
    quadtree_node_t *quadtree, float second)
{
    for (int i = 0; i < quadtree->count_aircraft; i++) {
        if (quadtree->aircraftlist[i] == NULL)
            return;
        if (i < 0 || i >= quadtree->count_aircraft)
            return;
        if (quadtree->aircraftlist[i]->is_destroyed == FALSE
            && quadtree->aircraftlist[i]->sprite_aircraft != NULL
            && quadtree->aircraftlist[i]->pos_aircraft != NULL
            && quadtree->count_aircraft != 0) {
                render_wind_air(core, quadtree, i);
                set_new_pose(quadtree, second, i);
        }
        if (quadtree->aircraftlist[i]->rect_aircraft != NULL
        && quadtree->count_aircraft != 0
        && quadtree->aircraftlist[i]->is_destroyed == FALSE) {
            set_outline_color(quadtree, i);
        }
    }
}

void print_aircraft_quad(sfRenderWindow *window,
    quadtree_node_t **quadtree, sfClock *my_clock, main_t *core)
{
    sfTime time_elapsed = sfClock_getElapsedTime(my_clock);
    float second = sfTime_asSeconds(time_elapsed);

    if ((*quadtree)->is_divided == TRUE) {
        go_in_quad(window, (*quadtree), my_clock, core);
    }
    if (core->quad_pressed == TRUE && (*quadtree)->quadtree_rect != NULL
    && (*quadtree)->is_divided == FALSE)
        sfRenderWindow_drawRectangleShape(window,
            (*quadtree)->quadtree_rect, NULL);
    if (second > 0.01) {
        print_air_quad(core, (*quadtree), second);
    }
}

static void set_shape(aircraft_t *all_aircraft[], int i, sfTexture *text)
{
    sfSprite_setTexture(all_aircraft[i]->sprite_aircraft, text, sfTrue);
    sfSprite_setPosition(all_aircraft[i]->sprite_aircraft,
        (sfVector2f){all_aircraft[i]->pos_aircraft->x,
        all_aircraft[i]->pos_aircraft->y});
    sfRectangleShape_setSize(all_aircraft[i]->rect_aircraft,
        (sfVector2f){20, 20});
    sfRectangleShape_setPosition(all_aircraft[i]->rect_aircraft,
        (sfVector2f){all_aircraft[i]->pos_aircraft->x,
        all_aircraft[i]->pos_aircraft->y});
    sfRectangleShape_setFillColor(all_aircraft[i]->rect_aircraft,
        sfTransparent);
    sfRectangleShape_setOutlineThickness(all_aircraft[i]->rect_aircraft, 1);
    sfRectangleShape_setOutlineColor(all_aircraft[i]->rect_aircraft, sfRed);
}

static void print_aircraft_wind(aircraft_t *all_aircraft[], int count)
{
    sfTexture *text = sfTexture_createFromFile("assets/plane2.png", NULL);

    if (all_aircraft == NULL)
        return;
    for (int i = 0; i < count; i++) {
        if (all_aircraft[i] == NULL)
            continue;
        all_aircraft[i]->sprite_aircraft = sfSprite_create();
        all_aircraft[i]->rect_aircraft = sfRectangleShape_create();
        set_shape(all_aircraft, i, text);
    }
}

void print_wind(aircraft_t *all_aircraft[], int count_aairc,
    tower_t *all_tower[], int count_tox)
{
    print_aircraft_wind(all_aircraft, count_aairc);
    print_tower_wind(all_tower, count_tox);
}
