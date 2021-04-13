/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** list_directory
*/

#include "functions.h"
#include "client_handle.h"
#include "data_error.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void send_list_data(clients_data_t *client)
{
    struct sockaddr_in addr;
    size_t len = sizeof(addr);
    FILE *file = popen("ls -l", "r");
    int fd;
    char c;

    getpeername(client->fd, (struct sockaddr *)&addr, (socklen_t *)&len);
    fd = accept(client->data_fd,
            (struct sockaddr *)&addr, (socklen_t *)&len);
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n')
            dprintf(fd, "\r\n");
        else
            dprintf(fd, "%c", c);
    }
    dprintf(client->fd, "%i Directory send OK.\r\n", TRANSFER_GOOD);
    close(fd);
    exit(0);

}

void list_directory(char *value, clients_data_t *client, server_t *server)
{
    int cpid = -1;
    char *buf = NULL;

    if (client->data_fd < 0 || !client->is_connected)
        return error_handling(client);
    cpid = fork();
    if (cpid == 0) {
        send_list_data(client);
    } else {
        client->msg = "Here comes the directory listing\r\n";
        client->return_code = 150;
    }
}
