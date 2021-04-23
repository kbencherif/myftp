/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "print_usage.h"
#include "server.h"
#include "my_utils.h"
#include "client_handle.h"

server_t set_up_server(int port)
{
    server_t server;
    struct timeval tv = {0, 0};

    server.socket = make_socket(port, &server.address);
    server.max_socket = server.socket;
    server.tv = tv;
    return server;
}

int run_ftp(int port, char *dir)
{
    server_t server = set_up_server(port);
    clients_data_t *clients_list = NULL;

    if (server.socket < 0)
        return 84;
    while(true) {
        reset_server(server.socket, &server.rfds);
        server.max_socket = put_socket_in_set
            (&server.rfds, clients_list, server.max_socket);
        if (select(server.max_socket + 1, &server.rfds,
                    NULL, NULL, &server.tv) < 0) {
            perror("select");
            continue;
        }
        if (FD_ISSET(server.socket, &server.rfds))
            clients_list = add_new_client(
                    accept_new_client(server.socket, &server.address),
                 clients_list, dir);
        communicate_with_clients(&server, clients_list);
    }
}

#ifndef __TESTS_RUN__
int main(int argc , char *argv[], char *env[])
{
    int status = 0;

    if (argc == 2 && !strcmp(argv[1], "-help"))
        return print_usage();
    if (argc == 3 && is_number(argv[1]) && is_valid_dir(argv[2]))
        return run_ftp(atoi(argv[1]),  getcwd(NULL, 0));
    return 84;
}
#endif
