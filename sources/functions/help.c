/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** help
*/

#include "functions.h"

void help_commands(char *value, clients_data_t *client, server_t *server)
{
    client->msg = "USER, PASS, CWD, CDUP, QUIT, PORT, PASV, STOR, RETR, LIST,\
                   DELE, PWD, HELP, NOOP\r\n";
    client->return_code = HELP_OK;
}
