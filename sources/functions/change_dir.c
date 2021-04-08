/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** change_dir
*/

#include "functions.h"
#include "server.h"
#include <unistd.h>

void change_dir(char *value, clients_data_t *client, server_t *server)
{
    if (!chdir(value)) {
        client->client_dir = getcwd(NULL, 0);
        client->return_code = SUCCESS;
        client->msg = "Directory successfully changed.\r\n";
    } else {
        client->return_code = ERROR;
        client->msg = "Failed to change directory.\r\n";
    }
}

void parent_directory(char *value, clients_data_t *client, server_t *server)
{
    change_dir("../", client, server);
}
