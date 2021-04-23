/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** add_new_client
*/

#include "my_utils.h"
#include <stdlib.h>

clients_data_t *set_up_new_client(int fd, char *dir)
{
    clients_data_t *new_client = NULL;

    if (fd < 0)
        return NULL;
    new_client = malloc(sizeof(clients_data_t));
    new_client->data_fd = -1;
    new_client->fd = fd;
    new_client->is_connected = false;
    new_client->msg = NULL;
    new_client->next = NULL;
    new_client->password = NULL;
    new_client->return_code = -1;
    new_client->user = NULL;
    new_client->client_dir = dir;
    return new_client;
}

clients_data_t *add_new_client(int fd, clients_data_t *clients, char *dir)
{
    clients_data_t *tmp = clients;

    if (!tmp)
        return set_up_new_client(fd, dir);
    for (; tmp->fd != 0 && tmp->next; tmp = tmp->next);
    if (tmp->fd == 0 && fd >0)
        tmp->fd = fd;
    else
        tmp->next = set_up_new_client(fd, dir);
    return clients;
}
