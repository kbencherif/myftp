/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** active_utils
*/

#include "functions.h"

int get_size(char *value)
{
    int nb = 0;

    if (!value)
        return 0;
    for (int i = 0; value[i]; i++) {
        if (value[i] == ',')
            nb++;
    }
    return nb;
}

void bad_argument_error(clients_data_t *client)
{
    client->msg = "Bad argument.\n\r";
    client->return_code = BAD_ARGUMENT;
}

void error_command(clients_data_t *client)
{
    client->return_code = 520;
    client->msg = "Illegal PORT command\r\n";
}
