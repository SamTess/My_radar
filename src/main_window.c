/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : main window function
*/
#include "../include/my.h"

static void free_struct(main_t *core)
{
    free(core->aircraft->pos_aircraft);
    free(core->aircraft);
    free(core->quadtree->next_quad);
    free(core->quadtree->quad_pos);
    free(core->quadtree);
    free(core->wind);
    free(core);
}

static void key_pressed_desac(main_t **core, sfEvent *event)
{
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyG && (*core)->quad_pressed == TRUE) {
            (*core)->quad_pressed = FALSE;
            return;
        }
        if (event->key.code == sfKeyG && (*core)->quad_pressed == FALSE) {
            (*core)->quad_pressed = TRUE;
            return;
        }
    }
}

static void key_pressed_active(main_t **core, sfEvent *event)
{
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyS && (*core)->s_pressed == FALSE) {
            (*core)->s_pressed = TRUE;
            return;
        }
        if (event->key.code == sfKeyS && (*core)->s_pressed == TRUE) {
            (*core)->s_pressed = FALSE;
            return;
        }
        if (event->key.code == sfKeyL && (*core)->hitbox_pressed == FALSE) {
            (*core)->hitbox_pressed = TRUE;
            return;
        }
        if (event->key.code == sfKeyL && (*core)->hitbox_pressed == TRUE) {
            (*core)->hitbox_pressed = FALSE;
            return;
        }
    }
}

static void close_window(sfEvent *event, int count,
    main_t **core, aircraft_t *all_aircraft[])
{
    if (event->type == sfEvtClosed) {
        sfRenderWindow_close((*core)->window);
    }
    key_pressed_active(core, event);
    key_pressed_desac(core, event);
}

static void alloc_core_quad(main_t **core)
{
    if ((*core)->quadtree->first != 1) {
        (*core)->quadtree = malloc(sizeof(quadtree_node_t));
        (*core)->quadtree->quad_pos = malloc(sizeof(quadtree_pos_t));
        (*core)->quadtree->next_quad = malloc(sizeof(next_quadtree_t));
    }
    sfRenderWindow_clear((*core)->window, sfTransparent);
    sfRenderWindow_drawSprite((*core)->window, (*core)->wind->sprite_bk, NULL);
    my_timer((*core)->my_clock, (*core)->window, (*core));
}

static void end_sim(main_t **core)
{
    sfRenderWindow_destroy((*core)->window);
    sfTexture_destroy((*core)->wind->text_bk);
    sfSprite_destroy((*core)->wind->sprite_bk);
    sfClock_destroy((*core)->my_clock);
    free_struct((*core));
}

static void generation_window_clock(main_t **core)
{
    (*core)->window = sfRenderWindow_create
        ((*core)->size, "My_radar", sfResize | sfClose, NULL);
    generation_window((*core)->wind);
    (*core)->my_clock = sfClock_create();
}

static void start_sim(char const *filepath, sfEvent **event, main_t *core)
{
    int count_air = count_aircraft(filepath);
    int count_tow = count_tower(filepath);
    aircraft_t *all_aircraft[count_air];
    tower_t *all_tower[count_tow];

    generation_window_clock(&core);
    if (put_list(all_aircraft, all_tower, filepath) == 84)
        return;
    print_wind(all_aircraft, count_air, all_tower, count_tow);
    sfWindow_setFramerateLimit(core->window, 20);
    while (sfRenderWindow_isOpen(core->window)) {
        while (sfRenderWindow_pollEvent(core->window, (*event)))
            close_window((*event), count_air, &core, all_aircraft);
        alloc_core_quad(&core);
        check_tower_control(all_tower, all_aircraft, count_air, count_tow);
        print_tower(all_tower, core->window, count_tow, core);
        generate_quadtree(core, (&core->quadtree), all_aircraft, count_air);
    }
    end_sim(&core);
}

int alloc_struct(char const *filepath, sfEvent **event, int width, int height)
{
    main_t *core = malloc(sizeof(main_t));

    core->aircraft = malloc(sizeof(aircraft_t));
    core->aircraft->pos_aircraft = malloc(sizeof(aircraft_pos_t));
    core->quadtree = malloc(sizeof(quadtree_node_t));
    core->quadtree->quad_pos = malloc(sizeof(quadtree_pos_t));
    core->quadtree->next_quad = malloc(sizeof(next_quadtree_t));
    core->quadtree->first = 1;
    core->wind = malloc(sizeof(window_t));
    core->size.bitsPerPixel = 32;
    core->size.height = height;
    core->size.width = width;
    core->hitbox_pressed = TRUE;
    core->quad_pressed = FALSE;
    core->s_pressed = TRUE;
    start_timer(&core);
    start_sim(filepath, event, core);
}
