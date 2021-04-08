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

void list_directory(char *value, clients_data_t *client, server_t *server)
{
    int cpid = -1;
    int fd;
    struct sockaddr_in address;
    size_t addrlen = sizeof(address);
    FILE *file = popen("ls -l", "r");
    char *buf = NULL;
    char c;

    if (client->data_fd < 0 || !client->is_connected)
        return error_handling(client);
    cpid = fork();
    if (cpid == 0) {
        getpeername(client->fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        fd = accept(client->data_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        while ((c = fgetc(file)) != EOF) {
            if (c == '\n')
                dprintf(fd, "\r\n");
            else
                dprintf(fd, "%c", c);
		}
        dprintf(client->fd, "%i Directory send OK.\r\n", TRANSFER_GOOD);
        close(fd);
        exit(0);
    } else {
        client->msg = "Here comes the directory listing\r\n";
        client->return_code = 150;
    }
}
