/*
** EPITECH PROJECT, 2024
** B-MUL-100
** File description:
** My_radar : timer functions
*/
#include "../include/my.h"

static int get_length_time(float seconds)
{
    int count = 0;
    int int_seconds = (int)seconds;

    while (int_seconds > 0) {
        int_seconds /= 10;
        count++;
    }
    return count;
}

static void sec_in_arr(char timer[], float seconds)
{
    int minutes = (int)seconds / 60;
    int remain_sec = (int)seconds % 60;

    timer[0] = '0' + minutes / 10;
    timer[1] = '0' + minutes % 10;
    timer[2] = ':';
    timer[3] = '0' + remain_sec / 10;
    timer[4] = '0' + remain_sec % 10;
    timer[5] = '\0';
}

void my_timer(sfClock *my_clock, sfRenderWindow *window, main_t *core)
{
    sfTime elapsed_time = sfClock_getElapsedTime(my_clock);
    float seconds = sfTime_asSeconds(elapsed_time);
    char timer[5];

    sec_in_arr(timer, seconds);
    sfText_setString(core->timer_text, timer);
    sfRenderWindow_drawText(window, core->timer_text, NULL);
}

void start_timer(main_t **core)
{
    (*core)->font = sfFont_createFromFile("assets/arial.ttf");
    (*core)->timer_text = sfText_create();
    sfText_setFont((*core)->timer_text, (*core)->font);
    sfText_setCharacterSize((*core)->timer_text, 48);
    sfText_setPosition((*core)->timer_text,
        (sfVector2f){((*core)->size.width - 140), 10});
}
