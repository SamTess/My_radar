/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : put in list
*/
#include "../include/my.h"


static off_t set_buff(char const *filepath)
{
    struct stat buf;
    int result = stat(filepath, &buf);
    off_t size;

    if (result == -1)
        return -1;
    size = buf.st_size;
    return (size);
}

static int put_nb_int(char *buffer, int *i)
{
    int nb = 0;

    while (buffer[*i] < '0' || buffer[*i] > '9') {
        *i += 1;
    }
    while (buffer[*i] >= '0' && buffer[*i] <= '9') {
        nb = nb * 10 + (buffer[*i] - '0');
        *i += 1;
    }
    return nb;
}

static float put_nb(char *buffer, int *i)
{
    float nb = 0;

    while (buffer[*i] < '0' || buffer[*i] > '9') {
        *i += 1;
    }
    while (buffer[*i] >= '0' && buffer[*i] <= '9') {
        nb = nb * 10 + (buffer[*i] - '0');
        *i += 1;
    }
    return nb;
}

static int put_aircraft(char *buffer, aircraft_t **aircraft, int i)
{
    (*aircraft)->pos_aircraft = malloc(sizeof(aircraft_pos_t));
    (*aircraft)->pos_aircraft->start_x = put_nb(buffer, &i);
    (*aircraft)->pos_aircraft->start_y = put_nb(buffer, &i);
    (*aircraft)->pos_aircraft->end_x = put_nb(buffer, &i);
    (*aircraft)->pos_aircraft->end_y = put_nb(buffer, &i);
    (*aircraft)->pos_aircraft->x = (*aircraft)->pos_aircraft->start_x;
    (*aircraft)->pos_aircraft->y = (*aircraft)->pos_aircraft->start_y;
    (*aircraft)->speed = put_nb(buffer, &i);
    (*aircraft)->delay = put_nb(buffer, &i);
    (*aircraft)->is_in_tower = FALSE;
    (*aircraft)->is_started = FALSE;
    (*aircraft)->is_destroyed = FALSE;
    return i;
}

static int put_list_aircraft_bis(char *buffer, int buff,
    aircraft_t *all_aircraft[], int file_desc)
{
    int count_de = 0;
    ssize_t check_read = read(file_desc, buffer, buff);
    int i = 0;

    if (check_read == -1) {
        return 84;
    }
    buffer[check_read] = '\0';
    while (buffer[i] != '\0') {
        if (buffer[i] == 'A') {
            all_aircraft[count_de] = malloc(sizeof(aircraft_t));
            i = put_aircraft(buffer, &all_aircraft[count_de], i);
            count_de++;
        } else {
            i++;
        }
    }
    all_aircraft[count_de] = NULL;
    return 0;
}

static int put_list_aircraft(aircraft_t *all_aircraft[], char const *filepath)
{
    off_t buff = set_buff(filepath);
    char *buffer = malloc(buff + 1);
    int check = open(filepath, O_RDONLY);
    int count = 0;

    if (check == -1 || buff == -1) {
        close(check);
        return 84;
    } else {
        if (put_list_aircraft_bis(buffer, buff, all_aircraft, check) == 84) {
            close(check);
            free(buffer);
            return 84;
        }
        close(check);
        free(buffer);
        return 0;
    }
}

static int put_tower(char *buffer, tower_t **tower, int i)
{
    (*tower) = malloc(sizeof(tower_t));
    (*tower)->pos_x = put_nb_int(buffer, &i);
    (*tower)->pos_y = put_nb_int(buffer, &i);
    (*tower)->radius = put_nb(buffer, &i);
    return i;
}

static int put_list_tower_bis(char *buffer, int buff,
    tower_t *all_tower[], int file_desc)
{
    int count = 0;
    ssize_t check_read = read(file_desc, buffer, buff);

    if (check_read == -1)
        return 84;
    buffer[check_read] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == 'T') {
            i = put_tower(buffer, &all_tower[count], i);
            count++;
        }
    }
    free(buffer);
    all_tower[count] = NULL;
}

static int put_list_tower(tower_t *all_tower[], char const *filepath)
{
    off_t buff = set_buff(filepath);
    char *buffer = malloc(buff + 1);
    int check = open(filepath, O_RDONLY);
    int count = 0;

    if (check == -1 || buff == -1) {
        close(check);
        return 84;
    } else {
        if (put_list_tower_bis(buffer, buff, all_tower, check) == 84) {
            close(check);
            return 84;
        } else {
            close(check);
            return 0;
        }
    }
    close(check);
}

int put_list(aircraft_t *all_aircraft[],
    tower_t *all_tower[], char const *filepath)
{
    int check_air = put_list_aircraft(all_aircraft, filepath);
    int check_tow = put_list_tower(all_tower, filepath);

    if (check_air == 84 || check_tow == 84) {
        return 84;
    } else {
        return 0;
    }
}
