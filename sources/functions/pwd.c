/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** pwd
*/

#include "client_handle.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void pwd(char *value, clients_data_t *client, server_t *server)
{
    char *dir = getcwd(NULL, 0);

    if (!client->is_connected)
        return login_error(client);
    client->return_code = PWD;
    client->msg = malloc(strlen(dir) + 6);
    snprintf(client->msg, strlen(dir) + 6,
            "\"%s\"\r\n", dir);
}
