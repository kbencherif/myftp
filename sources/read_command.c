/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** read_command
*/

#include "my_utils.h"
#include "client_handle.h"
#include "server.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void exec_command(char *cmd, clients_data_t *clients, server_t *server)
{
    int size = 0;

    for (int i = 0; COMMANDS[i].command; i++) {
        size = strlen(COMMANDS[i].command);
        if (!strncasecmp(COMMANDS[i].command, cmd, size)) {
            if (cmd[size] == '\0' || cmd[size + 1] == '\0')
                return COMMANDS[i].exec_cmd(NULL, clients, server);
            else
                return COMMANDS[i].exec_cmd(cmd + size + 1, clients, server);
        }
    }
    default_error(clients);
}

char *read_socket(int fd)
{
    char *buffer = calloc(2, 1);
    char *needle = strdup("\r\n");
    char *buf = calloc(2, 1);

    while (!strstr(buf, needle)) {
        read(fd, buffer, 1);
        strcat(buf, buffer);
        buf = realloc(buf, strlen(buf) + 2);
    }
    free(needle);
    return buf;
}

void communicate_with_clients(server_t *server, clients_data_t *clients)
{
    clients_data_t *tmp = clients;
    char *buffer = NULL;

    if (!tmp)
        return;
    for (; tmp; tmp = tmp->next) {
        if (FD_ISSET(tmp->fd, &server->rfds)) {
            chdir(tmp->client_dir);
            FD_CLR(tmp->fd, &server->rfds);
            buffer = read_socket(tmp->fd);
            buffer = clean_str(buffer);
            exec_command(buffer, tmp, server);
            if (tmp->return_code != DISCONNECT_USER)
                dprintf(tmp->fd, "%i %s", tmp->return_code, tmp->msg);
            dprintf(1,"buffer: %s\n%i %s\n", buffer, tmp->return_code, tmp->msg);
            free(buffer);
        }
    }
}
