/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** my_socket
*/

#ifndef __SERVER_H__
#define __SERVER_H__

#include <bits/types/struct_timeval.h>
#include <netinet/in.h>

typedef struct server_s {
    int socket;
    struct sockaddr_in address;
    fd_set rfds;
    int max_socket;
    struct timeval tv;
} server_t;

typedef struct port_s {
    int p1;
    int p2;
} port_t;

void reset_server(int server_socket, fd_set *rfds);
int make_socket(int port, struct sockaddr_in *server);
int accept_new_client(int server_socket, struct sockaddr_in *server);
int create_passive_socket(int ip, port_t port);

#endif
