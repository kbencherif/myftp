/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** data_transfer_error
*/

#include "client_handle.h"

void no_mode_error(clients_data_t *client)
{
    client->return_code = DATA_TRANSFER_ERROR;
    client->msg = "Use PORT or PASV first.\r\n";
}

void error_handling(clients_data_t *client)
{
    if (!client->is_connected)
        return login_error(client);
    if (client->data_fd < 0)
        return no_mode_error(client);
}

