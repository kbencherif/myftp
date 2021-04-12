/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** make_socket
*/

#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "my_utils.h"

int put_socket_in_set(fd_set *rfds, clients_data_t *clients, int max_socket)
{
    clients_data_t *tmp = clients;

    if (!tmp)
        return max_socket;
    for (; tmp; tmp = tmp->next) {
        if (tmp->fd > 0)
            FD_SET(tmp->fd, rfds);
        if (max_socket < tmp->fd)
            max_socket = tmp->fd;
    }
    return max_socket;
}


int accept_new_client(int server_socket, struct sockaddr_in *server)
{
    int addrlen = sizeof(*server);
    int client_socket = accept(server_socket, (struct sockaddr *)server,
            (socklen_t*)&addrlen);

    if (client_socket < 0) {
        perror("accept");
    } else {
        printf("New connection:\n    ip   :%s\n    port :%d\n\n",
                inet_ntoa(server->sin_addr), ntohs(server->sin_port));
        dprintf(client_socket, "220 Service ready for new user.\r\n");
    }
    return client_socket;
}

void reset_server(int server_socket, fd_set *rfds)
{
    FD_ZERO(rfds);
    FD_SET(server_socket, rfds);
}

int make_socket(int port, struct sockaddr_in *server)
{
    int socket_serv = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    if (socket_serv < 0) {
        perror("socket");
        return socket_serv;
    }
    /*setsockopt(socket_serv, SOL_SOCKET, SO_REUSEADDR |*/
            /*SO_REUSEPORT, (char *)&opt,*/
            /*sizeof(opt));*/
    server->sin_family = AF_INET;
    server->sin_addr.s_addr = htonl(INADDR_ANY);
    server->sin_port = htons(port);
    if (bind(socket_serv, (struct sockaddr *)server , sizeof(*server)) < 0) {
        perror("bind");
        return -1;
    }
    if (listen(socket_serv , FD_SETSIZE)) {
        perror("listen");
        return -1;
    }
    return socket_serv;
}
