#pragma once

#include "../utils/utils.h"
#include "../datastructures/linked_list.h"
#include "../datastructures/hash_table.h"

typedef struct shelf_list shelf_list_t;

typedef struct shelf shelf_t;


/// @brief Duplicates a linked list with all its links and values with new pointers
/// @param old_list list to be duplicated
/// @return the duplicated list
shelf_list_t *dup_shelf_list(shelf_list_t *old_list);

shelf_list_t *dup_shelf_list_insert_shelf_ht(hash_table_t *ht, shelf_list_t *old_list, char *new_name);

/// @brief Increases the amount on a shelf
/// @param shelf shelf operated upon
/// @param amount amount to be increased with
void shelf_increase_amount(shelf_t *shelf, int amount);

/// @brief Decreases the amount of a merchandise. If one shelf goes to 0, go on to the next one
/// @param locs location list operated upon
/// @param amount amount to decrease with
/// @return a list of shelves that has the amount 0 from the locs list
list_t *shelf_decrease_amount(shelf_list_t *locs, int amount);

/// @brief Creates a new empty list
/// @return an empty linked list
shelf_list_t *shelf_list_create();

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements in the list is 0, else false
bool shelf_list_is_empty(shelf_list_t *list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param shelf_name the name of the shelf to be appended
/// @param amount the amount for the shelf
void shelf_list_append(shelf_list_t *list, char *shelf_name, int amount);

/// @brief gets the first shelf of a merchandise
/// @param list list operated upon
/// @param name merchandise of sought shelf
/// @return the wanted shelf
shelf_t *shelf_list_get_shelf(shelf_list_t *list, char *name);

/// @brief prints the name and amount of all shelves from the list
/// @param list list operated upon
void shelf_list_print_name_amount(shelf_list_t *list);

/// @brief Tear down the linked list and return all its memory
/// @param list the list to be destroyed
void shelf_list_destroy(shelf_list_t *list);

/// @brief destroyes the first shelf in the list and sets the first pointer to the next one
/// @param shelf_list list operated upon
void destroy_first_shelf(shelf_list_t *shelf_list);