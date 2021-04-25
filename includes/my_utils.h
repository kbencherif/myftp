/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** my_utils
*/

#ifndef __MY_UTILS_H__
#define __MY_UTILS_H__

#include <stdbool.h>
#include "functions.h"

void error_command(clients_data_t *client);
void bad_argument_error(clients_data_t *client);
int get_size(char *value);
bool is_valid_dir(char *str);
bool is_number(char *str);
char *clean_str(char *str);

#endif
