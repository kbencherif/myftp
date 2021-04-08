/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** delete
*/

#include "functions.h"
#include "client_handle.h"
#include <stdio.h>

void delete_file(char *value, clients_data_t *client, server_t *server)
{
    if (!client->is_connected)
        return login_error(client);

    if (remove(value) == -1) {
        client->return_code = ERROR;
        client->msg = "Requested action not taken.\r\n";
    } else {
        client->return_code = SUCCESS;
        client->msg = "File remove.\r\n";
    }
}
