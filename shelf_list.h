#pragma once

#include "utils.h"
#include "datastructures/linked_list.h"

typedef struct shelf_list shelf_list_t;

typedef struct shelf shelf_t;

char *shelf_get_shelf_name(shelf_t *shelf);

shelf_list_t *dup_shelf_list(shelf_list_t *old_list);

void shelf_increase_amount(shelf_t *shelf, int amount);

list_t *shelf_decrease_amount(shelf_list_t *locs, int amount);

shelf_list_t *shelf_list_create();

bool shelf_list_is_empty(shelf_list_t *list);

void shelf_list_append(shelf_list_t *list, char *shelf_name, int amount);

shelf_t *shelf_list_get_shelf(shelf_list_t *list, char *name);

void shelf_list_print_name_amount(shelf_list_t *list);

void shelf_list_destroy(shelf_list_t *list);

void destroy_first_shelf(shelf_list_t *shelf_list);