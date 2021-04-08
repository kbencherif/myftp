/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** put
*/

#include "client_handle.h"
#include "data_error.h"
#include "server.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

void get_file_from_client(clients_data_t *client, int file_fd)
{
    struct sockaddr_in address;
    size_t addrlen = sizeof(address);
    int fd = -1;
    fd_set rfds;
    char *file_content;

    if (file_fd < 0) {
        dprintf(client->fd, "%i Failed to open file.\r\n", ERROR);
        exit(0);
    }
    getpeername(client->fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    reset_server(client->data_fd, &rfds);
    select(client->data_fd + 1, &rfds, NULL, NULL, NULL);
    fd = accept(client->data_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    file_content = read_socket(fd);
    dprintf(file_fd, "%s", file_content);
    close(file_fd);
    close(fd);
}

void read_file_from_client
    (char *value, clients_data_t *client, server_t *server)
{
    int cpid = -1;
    int new_file = open(value, O_CREAT | O_RDWR, 0666);

    if (!client->is_connected || client->data_fd < 0)
        return error_handling(client);
    cpid = fork();
    if (cpid == 0) {
        get_file_from_client(client, new_file);
        dprintf(client->fd, "%i Transfer complete.\r\n", TRANSFER_GOOD);
        exit(0);
    } else {
        client->msg = "Opening Binary mode data connection.\r\n";
        client->return_code = 150;
    }
}