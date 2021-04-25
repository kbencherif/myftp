/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** active_mode
*/

#include "functions.h"
#include "my_utils.h"
#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char **get_data(char *value)
{
    int size = get_size(value);
    char **to_return = NULL;
    char *test = NULL;

    if (size != 5)
        return NULL;
    to_return = calloc(sizeof(char *) * (size + 2), 1);
    to_return[0] = strtok(value, ",");
    for (int i = 1; (test = strtok(NULL, ",")) != NULL; i++)
        to_return[i] = strdup(test);
    if (to_return[size] == NULL)
        return NULL;
    to_return[size][strlen(to_return[size]) - 1] = '\0';
    to_return[size + 1] = NULL;
    to_return[0] += 1;
    return to_return;
}

bool is_valid_data(char **data)
{
    if (!data)
        return false;
    for (int i = 0; data[i]; i++) {
        if (!is_number(data[i]))
            return false;
    }
    return true;
}

int create_pass_socket(int ip, port_t port)
{
    int	sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    size_t addrlen = 0;

    if (sock == -1)
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

struct sockaddr_in set_up_address(char **data)
{
    struct sockaddr_in address;

    size_t size = strlen(data[0]) + strlen(data[1]) +
        strlen(data[2]) + strlen(data[3]) + 4;
    char *add = calloc(size, 1);

    for (int i = 0; data[i] && i != 4; i++) {
        add = strcat(add, data[i]);
        if (i != 3)
            strcat(add, ".");
    }
    dprintf(1, "%s\n", add);
    inet_aton(add, &address.sin_addr);
    return address;
}


void active_mode(char *value, clients_data_t *client, server_t *server)
{
    char **data = get_data(value);
    struct sockaddr_in address;
    port_t port;

    if (!data)
        return error_command(client);
    if (!is_valid_data(data))
        return bad_argument_error(client);
    address = set_up_address(data);
    port.p1 = atoi(data[4]);
    port.p2 = atoi(data[5]);
    client->data_fd = create_passive_socket(address.sin_addr.s_addr, port);
    client->msg = "PORT command successful\r\n";
    client->return_code = NOOP;
}
