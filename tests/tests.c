/*
** EPITECH PROJECT, 2021
** project_name
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <stdlib.h>
#include <string.h>
#include "my_utils.h"

int is_to_clean(char c);

Test(utils, basic_nb)
{
    cr_expect(is_number("12") == true);
    cr_expect(is_number("test") == false);
}

Test(utils, check_char_to_clean)
{
    cr_expect(is_to_clean('a') == 0);
    cr_expect(is_to_clean(' ') == 1);
    cr_expect(is_to_clean('\r') == 1);
    cr_expect(is_to_clean('\n') == 1);
    cr_expect(is_to_clean('\t') == 1);
}

Test(utils, clean_str)
{
    cr_assert(!strcmp("Hello World", clean_str(strdup("\tHello        World\r\n"))));
}

Test(utils, check_dir)
{
    cr_assert(is_valid_dir("./") == true);
    cr_assert(is_valid_dir("./no_dir") == false);
}
