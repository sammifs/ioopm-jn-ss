#pragma once

#include "utils.h"

typedef struct shelf_list shelf_list_t;

typedef struct shelf shelf_t;

void shelf_increase_amount(shelf_t *shelf, int amount);

shelf_list_t *shelf_list_create();

void shelf_list_append(shelf_list_t *list, char *shelf_name, char *merch_name, int amount);

shelf_t *shelf_list_get_shelf(shelf_list_t *list, char *name);

void shelf_list_print_name_amount(shelf_list_t *list);

void shelf_list_destroy(shelf_list_t *list);