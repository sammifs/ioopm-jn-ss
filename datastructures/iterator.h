#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "common.h"

typedef struct iter list_iterator_t;

/// @brief Create an iterator for a given list
/// @param list the list to be iterated over
/// @return an iteration positioned at the start of list
list_iterator_t *list_iterator(list_t *list);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if there is at least one more element 
bool iterator_has_next(list_iterator_t *iter);

/// @brief Step the iterator forward one step
/// @param iter the iterator
/// @return the next element
elem_t iterator_next(list_iterator_t *iter);

// /// NOTE: REMOVE IS OPTIONAL TO IMPLEMENT 
// /// @brief Remove the current element from the underlying list
// /// @param iter the iterator
// /// @return the removed element
// int iterator_remove(list_iterator_t *iter);

// /// NOTE: INSERT IS OPTIONAL TO IMPLEMENT 
// /// @brief Insert a new element into the underlying list making the current element it's next
// /// @param iter the iterator
// /// @param element the element to be inserted
// void iterator_insert(list_iterator_t *iter, int element);

/// @brief Reposition the iterator at the start of the underlying list
/// @param iter the iterator
void iterator_reset(list_iterator_t *iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element struct
elem_t iterator_current(list_iterator_t *iter);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void iterator_destroy(list_iterator_t *iter);