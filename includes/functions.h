/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** functions
*/

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "server.h"
#include <stdio.h>
#include <stdbool.h>

typedef int CODE;

enum CODE {
    NOOP = 200,
    HELP_OK = 214,
    TRANSFER_GOOD = 226,
    PASSIV_MOD = 227,
    USER_LOG = 230,
    SUCCESS = 250,
    PWD = 257,
    SPECIFY_PASS = 331,
    DATA_TRANSFER_ERROR = 425,
    UNKNOWN_CMD = 500,
    BAD_ARGUMENT = 501,
    USER_FIRST = 503,
    INCORRECT = 530,
    ERROR = 550,
    DISCONNECT_USER = 220
};

typedef struct clients_data_s {
    int fd;
    int data_fd;
    CODE return_code;
    char *msg;
    char *user;
    char *password;
    bool is_connected;
    struct clients_data_s *next;
    char *client_dir;
} clients_data_t;

void pwd(char *value, clients_data_t *client, server_t *server);
void check_password(char *value, clients_data_t *client, server_t *server);
void check_user(char *value, clients_data_t *client, server_t *server);
void disconnect(char *value, clients_data_t *client, server_t *server);
void noop(char *value, clients_data_t *client, server_t *server);
void change_dir(char *value, clients_data_t *client, server_t *server);
void parent_directory(char *value, clients_data_t *client, server_t *server);
void passive_mode(char *value, clients_data_t *client, server_t *server);
void read_file_from_client
    (char *value, clients_data_t *client, server_t *server);
void upload_file(char *value, clients_data_t *client, server_t *server);
void delete_file(char *value, clients_data_t *client, server_t *server);
void list_directory(char *value, clients_data_t *client, server_t *server);
void active_mode(char *value, clients_data_t *client, server_t *server);
void help_commands(char *value, clients_data_t *client, server_t *server);

#endif
