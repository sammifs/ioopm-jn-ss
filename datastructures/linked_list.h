#pragma once
#include <assert.h>
#include <stdbool.h>
#include "string.h"
#include <stdlib.h>
#include "common.h"

/**
 * @file hash_table.h
 * @author Jonathan Näslund och Emil Edin
 * @date 22 Sep 2023
 * @brief Simple linked list structure that holds integers as values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */


typedef struct list list_t; /// Meta: struct definition goes in C file
typedef struct link link_t;
typedef bool(*int_predicate)(elem_t value, void *extra);
typedef void(*apply_int_function)(elem_t *value, void *extra);


/// @brief Creates a new empty list
/// @return an empty linked list
list_t *linked_list_create(eq_function equal_fun);

/// @brief Tear down the linked list and return all its memory (but not the memory of the elements)
/// @param list the list to be destroyed
void linked_list_destroy(list_t *list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void linked_list_append(list_t *list, elem_t value);

/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended to
/// @param value the value to be prepended
void linked_list_prepend(list_t *list, elem_t value);

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the first element and n means after
/// the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be inserted 
void linked_list_insert(list_t *list, int index, elem_t value);

/// @brief Lookup the number of elements in the linked list in O(1) time
/// @param list the linked list
/// @return the number of elements in the list
size_t linked_list_size(list_t *list);

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements in the list is 0, else false
bool linked_list_is_empty(list_t *list);

/// @brief Remove an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list
/// @param index the position in the list
/// @return the value removed in an element struct
elem_t linked_list_remove(list_t *list, int index);

/// @brief Test if an element is in the list
/// @param list the linked list
/// @param element the element sought
/// @return true if element is in the list, else false
bool linked_list_contains(list_t *list, elem_t element);

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the value at the given position in an element struct
elem_t linked_list_get(list_t *list, int index);

/// @brief Remove all elements from a linked list
/// @param list the linked list
void linked_list_clear(list_t *list);

/// @brief Test if a supplied property holds for all elements in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested (function pointer)
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for all elements in the list, else false
bool linked_list_all(list_t *list, int_predicate prop, void *extra);

/// @brief Test if a supplied property holds for any element in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for any elements in the list, else false
bool linked_list_any(list_t *list, int_predicate prop, void *extra);

/// @brief Apply a supplied function to all elements in a list.
/// @param list the linked list
/// @param fun the function to be applied
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of fun
void linked_list_apply_to_all(list_t *list, apply_int_function fun, void *extra);

/// @brief Destroys a given link and all links after
/// @param link the link to be destroyed
void links_destroy(link_t *link);

/// @brief Gets the first link in a linked list
/// @param list The list that the link will be taken from
/// @return Returns the first link in a linked list
link_t *linked_list_first(list_t *list);