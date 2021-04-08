/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** print_usage
*/

#include <stdio.h>

int print_usage()
{
    printf("USAGE: ./myftp port path\n");
    printf("       port  is the port number on which the server socket listens"
            );
    putchar('\n');
    printf("       path  is the path to the home directory for the Anonymous");
    printf(" user\n");
    return 0;
}
