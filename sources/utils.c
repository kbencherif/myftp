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

bool is_valid_dir(char *str)
{
    if (!chdir(str)) {
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

int is_to_clean(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

char *clean_str(char *str)
{
    int i = 0;
    int j = 0;
    int str_len = strlen(str);
    char *cleaned_str = malloc(sizeof(char) * (str_len + 1));

    for (; is_to_clean(str[i]); i++);
    while (str[i]) {
        if (is_to_clean(str[i]) && !is_to_clean(str[i + 1]) && str[i + 1]) {
            cleaned_str[j] = ' ';
            j++;
        } else if (!is_to_clean(str[i])) {
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
