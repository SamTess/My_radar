/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : count functions
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

static int count_aircraft_bis(char *buffer, int buff, int file_desc)
{
    int count = 0;
    int check_read = read(file_desc, buffer, buff);

    buffer[check_read - 1] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == 'A') {
            count += 1;
        }
    }
    return count;
}

int count_aircraft(char const *filepath)
{
    off_t buff = set_buff(filepath);
    char *buffer = malloc(buff + 1);
    int check = open(filepath, O_RDONLY);
    int count = 0;

    if (check == -1) {
        close(check);
        return 84;
    } else {
        count = count_aircraft_bis(buffer, buff + 1, check);
        free(buffer);
        close(check);
        return count;
    }
}

static int count_tower_bis(char *buffer, int buff, int file_desc)
{
    int count = 0;
    int check_read = read(file_desc, buffer, buff);

    buffer[check_read - 1] = '\0';
    for (int i = 0; buffer[i] != '\0'; i ++) {
        if (buffer[i] == 'T') {
            count += 1;
        }
    }
    return count;
}

int count_tower(char const *filepath)
{
    off_t buff = set_buff(filepath);
    char *buffer = malloc(buff + 1);
    int check = open(filepath, O_RDONLY);
    int count = 0;

    if (check == -1) {
        close(check);
        return 84;
    } else {
        count = count_tower_bis(buffer, buff + 1, check);
        free(buffer);
        close(check);
        return count;
    }
    close(check);
    return 0;
}
