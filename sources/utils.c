/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** utils
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool is_valid_dir(char *str, char *env[])
{
    char *root = calloc(strlen(str) + 3, 1);

    strcpy(root, "./");
    strcat(root, str);
    if (!chdir(root)) {
        return true;
    } else {
        return false;
    }
}

bool is_number(char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

char *clean_str(char *str)
{
    int i = 0;
    int j = 0;
    int str_len = strlen(str);
    char *cleaned_str = malloc(sizeof(char) * (str_len + 1));

    for (; is_space(str[i]); i++);
    while (str[i]) {
        if (is_space(str[i]) && !is_space(str[i + 1]) && str[i + 1]) {
            cleaned_str[j] = ' ';
            j++;
        } else if (!is_space(str[i])) {
            cleaned_str[j] = str[i];
            j++;
        }
        i++;
    }
    cleaned_str[j] = '\0';
    if (str)
        free(str);
    return cleaned_str;
}
