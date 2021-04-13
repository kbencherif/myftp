/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "my_utils.h"
#include <criterion/internal/assert.h>
#include <stdlib.h>
#include <string.h>

Test(utils, basic_nb)
{
    cr_assert(is_number("12") == true);
}
