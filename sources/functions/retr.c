/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** retr
*/

#include "functions.h"
#include "client_handle.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "data_error.h"

char *read_file(int fd)
{
    struct stat st;
    char *buff = NULL;

    fstat(fd, &st);
    buff = malloc(st.st_size);
    read(fd, buff, st.st_size);
    buff[st.st_size] = 0;
    return buff;
}

void send_file_to_client(clients_data_t *client, int file_fd)
{
    struct sockaddr_in addr;
    size_t addrlen = sizeof(addr);
    int fd = -1;
    fd_set rfds;
    char *file_content;

    if (file_fd < 0) {
        dprintf(client->fd, "%i Failed to open file.\r\n", ERROR);
        exit(0);
    }
    getpeername(client->fd, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
    reset_server(client->data_fd, &rfds);
    select(client->data_fd + 1, &rfds, NULL, NULL, NULL);
    fd = accept(client->data_fd,
            (struct sockaddr *)&addr, (socklen_t *)&addrlen);
    file_content = read_file(file_fd);
    dprintf(fd, "%s", file_content);
    close(file_fd);
    close(fd);
}

void upload_file(char *value, clients_data_t *client, server_t *server)
{
    int cpid = -1;
    int new_file = open(value, O_RDWR);

    if (!client->is_connected || client->data_fd < 0)
        return error_handling(client);
    cpid = fork();
    if (cpid == 0) {
        send_file_to_client(client, new_file);
        dprintf(client->fd, "%i Transfer complete.\r\n", TRANSFER_GOOD);
        exit(0);
    } else {
        client->msg = "Opening Binary mode data connection.\r\n";
        client->return_code = 150;
    }
}
