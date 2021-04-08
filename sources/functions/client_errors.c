/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** client_errors
*/

#include "client_handle.h"

void default_error(clients_data_t *clients)
{
    if (clients->is_connected) {
        clients->return_code = UNKNOWN_CMD;
        clients->msg = "Unknown command.\r\n";
    } else {
        login_error(clients);
    }
}

void login_error(clients_data_t *clients)
{
    clients->return_code = INCORRECT;
    clients->msg = "Please login with USER and PASS.\r\n";
}
