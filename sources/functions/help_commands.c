/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** help_commands
*/

#include "client_handle.h"
#include "functions.h"

void help_commands(char *value, clients_data_t *client, server_t *server)
{
    if (!client->is_connected)
        return login_error(client);
    client->msg = "Help OK.\r\n";
    client->return_code = HELP_OK;
}
