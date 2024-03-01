/*
** EPITECH PROJECT, 2023
** B-MUL-100
** File description:
** My_radar : main
*/
#include "../include/my.h"
int id_quad;

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

static int check_coo(char *buffer, int count)
{
    int count_nbr = 0;

    if (buffer[count] == '\n' || buffer[count] == '\0')
        return 0;
    for (int i = count; buffer[i] != '\n'; i++) {
        if (buffer[i] == ' ' &&
            (buffer[i + 1] >= '0' && buffer[i + 1] <= '9')) {
                count_nbr++;
        }
        if (buffer[i + 1] == '\0')
            break;
        count++;
    }
    if (count_nbr % 6 != 0 && count_nbr % 3 != 0) {
        return 84;
    } else {
        if (check_coo(buffer, count + 1) == 84)
            return 84;
    }
    return 0;
}

static int valid_data(char *buffer, int buff, int check)
{
    int check_read = read(check, buffer, buff);

    if (check_read == -1)
        return 84;
    buffer[check_read - 1] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n' && buffer[i + 1] != 'A'
            && buffer[i + 1] != 'T' && buffer[i + 1] != '\0'
            && buffer[i + 1] != '\n') {
                return 84;
        }
        if ((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != 'T'
            && buffer[i] != 'A' && buffer[i] != 32 && buffer[i] != '\n') {
                return 84;
        }
    }
    if (check_coo(buffer, 0) == 84)
        return 84;
    return 0;
}

static int check_script(char const *filepath)
{
    off_t buff = set_buff(filepath);
    char *buffer = malloc(buff + 1);
    int check = open(filepath, O_RDONLY);

    if (check == -1 || buff == -1) {
        close(check);
        return 84;
    } else {
        if (valid_data(buffer, buff + 1, check) == 84) {
            close(check);
            return 84;
        }
    }
    close(check);
    free(buffer);
    return 0;
}

static int check_valid_script(char const *filepath, sfEvent **event)
{
    if (check_script(filepath) == 84) {
        mini_printf("./my_radar : bad arguments : 84 is given ");
        mini_printf("but 0 is required.\n retry with -h\n");
        return 84;
    } else {
        if (alloc_struct(filepath, event, 1920, 1080) == 84) {
            return 84;
        }
    }
    return 0;
}

static void print_h(void)
{
    mini_printf("Air traffic simulation pannel\n\n");
    mini_printf("USAGE\n");
    mini_printf("  ./my_radar [OPTIONS] path_to_script\n");
    mini_printf("   path_to_script      path to the script.\n\n");
    mini_printf("OPTIONS\n");
    mini_printf("  -h              print the usage and quit.\n\n");
    mini_printf("USER INTERACTIONS\n");
    mini_printf("  'L' key         enable/disable hitboxes and areas.\n");
    mini_printf("  'S' key         enable/disable sprites.\n");
}

int main(int argc, char const *argv[])
{
    sfEvent *event;

    id_quad = 0;
    if (argc != 2) {
        mini_printf("./my_radar : bad arguments : 84 is given ");
        mini_printf("but 0 is required.\n retry with -h\n");
        return 84;
    }
    if (argc == 2) {
        if (argv[1][0] == '-' && argv[1][1] == 'h') {
            print_h();
            return 0;
        }
        event->type = sfEvtClosed;
        if (check_valid_script(argv[1], &event) == 84) {
            return 84;
        } else {
            return 0;
        }
    }
}
