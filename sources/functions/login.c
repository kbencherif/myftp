/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** login
*/

#include "functions.h"
#include "client_handle.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

void find_user(char *value, clients_data_t *client)
{
    for (int i = 0; USERS[i].name; i++) {
        if (!strcasecmp(client->user, USERS[i].name)
                && (!USERS[i].password || !strcmp(value, USERS[i].password))) {
            client->password = USERS[i].password;
            client->is_connected = true;
            client->return_code = USER_LOG;
            client->msg = "Login successful.\r\n";
            client->client_dir = !strcasecmp("Anonymous", client->user) ?
                client->client_dir : USERS[i].directory;
            chdir(client->client_dir);
            return;
        }
    }
    client->user = NULL;
    client->return_code = INCORRECT;
    client->msg = "Login incorrect.\r\n";
    return;
}

void check_password(char *value, clients_data_t *client, server_t *server)
{
    if (!client->user) {
        client->return_code = USER_FIRST;
        client->msg = "Login with USER first.\r\n";
    } else {
        find_user(value, client);
    }
    return;
}

void check_user(char *value, clients_data_t *client, server_t *server)
{
    client->user = strdup(value);
    client->return_code = SPECIFY_PASS;
    client->msg = "Please specify the password.\r\n";
    return;
}

void disconnect(char *value, clients_data_t *client, server_t *server)
{
    client->return_code = DISCONNECT_USER;
    client->msg = "Goodbye.\r\n";
    if (client->user) {
        free(client->user);
        client->user = NULL;
    }
    if (client->password) {
        free(client->password);
        client->password = NULL;
    }
    dprintf(client->fd, "%i %s", client->return_code, client->msg);
    close(client->fd);
    close(client->data_fd);
    client->fd = 0;
    return;
}
