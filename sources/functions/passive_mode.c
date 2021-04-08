/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** passive_mode
*/

#include "functions.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>

port_t generate_port(void)
{
    port_t port;

    srand(time(NULL));
    port.p1 = rand() % 200;
    port.p2 = rand() % 150;
    return port;
}

int create_passive_socket(int ip, port_t port)
{
    int	sock = -1;
    struct sockaddr_in addr;
    size_t addrlen = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (-1);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip;
    addr.sin_port = htons(port.p1 * 256 + port.p2);
    addrlen = sizeof(addr);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1 ||
            listen(sock, FD_SETSIZE) == -1)
        return (-1);
    return sock;
}

int setup_passive_socket(port_t port, clients_data_t *client)
{
    int sock = -1;
    struct sockaddr_in address;
    size_t addrlen = sizeof(address);

    getpeername(client->fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    while ((sock = create_passive_socket
                (address.sin_addr.s_addr, port)) == -1)
        port = generate_port();
    return sock;
}

char *replace_dot_with_comma(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '.')
            str[i] = ',';
    return str;
}

void passive_mode(char *value, clients_data_t *client, server_t *server)
{
    port_t port = generate_port();
    client->data_fd = setup_passive_socket(port, client);
    struct sockaddr_in address;
    size_t addrlen = sizeof(address);
    size_t size = 0;

    getpeername(client->fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (!client->is_connected) {
        client->return_code = INCORRECT;
        client->msg = "Please login with USER and PASS.\r\n";
        return;
    } else {
        client->return_code = PASSIV_MOD;
        size = 35 + strlen(inet_ntoa(address.sin_addr));
        client->msg = malloc(sizeof(char) * size);
        snprintf(client->msg, size, "Entering Passive Mode (%s,%i,%i)\r\n",
                replace_dot_with_comma(inet_ntoa(address.sin_addr)),
                port.p1, port.p2);
    }
}
