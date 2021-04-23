/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** client_handle
*/

#ifndef __CLIENT_HANDLE_H__
#define __CLIENT_HANDLE_H__

#include <sys/select.h>
#include <stdbool.h>
#include <stddef.h>
#include "functions.h"
#include "server.h"

typedef void (*ptr_cmd)(char *value, clients_data_t *client, server_t *server);

typedef struct command_s {
    char *command;
    ptr_cmd exec_cmd;
} command_t;

typedef struct user_s {
    char *name;
    char *password;
    char *directory;
} user_t;

static const command_t COMMANDS[] = {
    {"pass", check_password},
    {"user", check_user},
    {"quit", disconnect},
    {"noop", noop},
    {"pwd", pwd},
    {"cwd", change_dir},
    {"cdup", parent_directory},
    {"pasv", passive_mode},
    {"stor", read_file_from_client},
    {"retr", upload_file},
    {"dele", delete_file},
    {"list", list_directory},
    {"port", active_mode},
    {"help", help_commands},
    {NULL, NULL}
};

static const user_t USERS[] = {
    {"Anonymous", NULL, NULL},
    {NULL, NULL, NULL}
};

void default_error(clients_data_t *clients);
void communicate_with_clients(server_t *server, clients_data_t *clients);
int put_socket_in_set(fd_set *rfds, clients_data_t *clients, int max_socket);
clients_data_t *add_new_client(int fd, clients_data_t *clients, char *dir);
clients_data_t *set_up_new_client(int fd);
void login_error(clients_data_t *clients);
char *read_socket(int fd);

#endif
