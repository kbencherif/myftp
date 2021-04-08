/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** noop
*/

#include "client_handle.h"
#include "functions.h"

void noop(char *value, clients_data_t *client, server_t *server)
{
    if (!client->is_connected)
        return login_error(client);
    client->return_code = NOOP;
    client->msg = "NOOP ok.\r\n";
    return;
}
