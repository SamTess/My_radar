/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : main header
*/

#ifndef _MY_H_
    #define _MY_H_
    #include <SFML/Graphics.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/System/Time.h>
    #include <SFML/Window/WindowHandle.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Clock.h>
    #include <stdio.h>
    #include <SFML/System/Export.h>
    #include <SFML/System/Time.h>
    #include <SFML/System/Types.h>
    #include <SFML/Config.h>
    #include <SFML/Config.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <assert.h>
    #include <math.h>
    #include "../include/my_struct.h"
    #include "../include/structure/quadtree.h"
    #define BOOL int
    #define TRUE 1
    #define FALSE 0
    #define QUAD_LIMIT 50

int mini_printf(char const *format, ...);
int my_put_nbr(int nb);
void my_putchar(char c);
int my_putstr(char const *str);
int my_strlen(char const *str);
void generation_window(window_t *wind);
int alloc_struct(char const *filepath,
    sfEvent **event, int width, int height);
void generate_quadtree(main_t *main,
    quadtree_node_t **quadtree, aircraft_t *all_aircraft[], int count_air);
int count_tower(char const *filepath);
int count_aircraft(char const *filepath);
int put_list(aircraft_t *all_aircraft[],
    tower_t *all_tower[], char const *filepath);
void check_tower_control(tower_t *all_tower[],
    aircraft_t *all_aircraft[], int count_air, int count_tow);
void create_subrectangle_topleft(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft);
void create_subrectangle_topright(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft);
void create_subrectangle_botleft(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft);
void create_subrectangle_botright(quadtree_node_t *parent,
    quadtree_node_t **child, aircraft_t *all_aircraft[], int count_aircraft);
void generate_quadtree_recursive(quadtree_node_t **quadtree,
    aircraft_t *all_aircraft[], int count_aircraft);
void print_aircraft_quad(sfRenderWindow *window,
    quadtree_node_t **quadtree, sfClock *my_clock, main_t *core);
void print_wind(aircraft_t *all_aircraft[],
    int count_aairc, tower_t *all_tower[], int count_tox);
void create_rect(quadtree_node_t *quadtree);
int detection_collision(aircraft_t *current, aircraft_t *next);
void print_tower_wind(tower_t *all_tower[], int count);
void print_tower(tower_t *all_tower[],
    sfRenderWindow *window, int count, main_t *core);
void check_collision(quadtree_node_t **quadtree);
void check_end(quadtree_node_t **quadtree);
void put_finished_aircraft(aircraft_t *all_aircraft[],
    quadtree_node_t *quadtree, sfClock *my_clock, int count);
void reset_is_in_tower(aircraft_t *all_aircraft[], int count);
void free_quadtree_recursive(quadtree_node_t **quadtree);
void my_timer(sfClock *my_clock, sfRenderWindow *window, main_t *core);
void start_timer(main_t **core);
extern int id_quad;

#endif /* !_MY_H_ */
