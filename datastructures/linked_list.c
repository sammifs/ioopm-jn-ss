#include "linked_list.h"
#include "iterator.h"
#include <assert.h>
#include <stdbool.h>
#include "string.h"


struct link
{
    elem_t element;
    link_t *next;
};

struct list
{
    link_t *first;
    link_t *last;
    size_t size; // Added field to store the number of elements in the linked list.
    eq_function equal_fun;
};

list_t *linked_list_create(eq_function equal_fun)
{
    list_t *new_list = calloc(1, sizeof(list_t));
    new_list->first = NULL;
    new_list->last = NULL;
    new_list->size = 0;
    new_list->equal_fun = equal_fun;
    return new_list;
}

void links_destroy(link_t *link) {
  // Cache the next pointer
  link_t *next = link->next;
  free(link);
  if (next != NULL) {
    links_destroy(next);
  }
}

void linked_list_destroy(list_t *list) {
    if (list->first == NULL && list->last == NULL) {
        free(list);
    } else {
        links_destroy(list->first);
        free(list);
    }
}

void linked_list_append(list_t *list, elem_t value)
{
    link_t *new_link = calloc(1, sizeof(link_t));
    
    new_link->element = value;
    new_link->next = NULL;
    // Increment size by one
    list->size = list->size + 1;
    if (list->last == NULL && list->first == NULL) {
        // TODO: ska man uppdatera first också till new_link? Svar: Det hjälper att göra så när man använder list_destroy.
        list->first = new_link;
        list->last = new_link;
    } else {
        list->last->next = new_link;
        list->last = new_link;
    }
}

void linked_list_prepend(list_t *list, elem_t value)
{
    link_t *new_link = calloc(1, sizeof(link_t));
    new_link->element = value;
    new_link->next = list->first;
    list->size = list->size + 1;
    if (list->last == NULL && list->first == NULL) {
        list->first = new_link;
        list->last = new_link;
    }
    else {
        list->first = new_link;
    }
}

size_t linked_list_size(list_t *list) {
    return list->size;
}

void linked_list_insert(list_t *list, int index, elem_t value) {
    size_t length = linked_list_size(list);
    int counter = 1;
    // If we insert at the head of the list
    if (index == 0) {
        linked_list_prepend(list, value);
    // If we insert at the last element
    } else if (length == index) {
        linked_list_append(list, value);
    } else {
        link_t *linked_link = list->first;
        while (counter != index - 1 && index != 1) {
            linked_link = linked_link->next;
            counter = counter + 1;
        }
        link_t *new_link = calloc(1, sizeof(link_t));
        new_link->element = value;
        new_link->next = linked_link->next;
        linked_link->next = new_link;
       // Increment size by one
       list->size = list->size + 1;
    }
}

elem_t linked_list_get(list_t *list, int index)
{
    assert(list->size > index);
    int counter = index;
    link_t *list_itr = list->first;
    while (counter != 0) {
        list_itr = list_itr->next;
        counter--;
    }
    return list_itr->element;
} 
bool linked_list_is_empty(list_t *list) {
    return list->size == 0;
}

bool linked_list_contains(list_t *list, elem_t element) {
    link_t *linked_list = list->first;
    for (int i = 0; i < list->size; i++) {
        if (list->equal_fun(linked_list->element, element)) {
            return true;
        } else {
            linked_list = linked_list->next;
        }
    }
    return false;
}

elem_t linked_list_remove(list_t *list, int index) {
    assert(list->size > index);
    int counter = 1;
    if (index == 0 && list->first->next != NULL) { // (When we want to remove the first element in the list)
        // We move the pointer of the first element to the next element in the list 
        // And free the removed elements memory and return it's value
        link_t *free_the_struct1 = list->first;
        list->first = list->first->next;
        elem_t removed_first_element = free_the_struct1->element;
        free(free_the_struct1);
        list->size = list->size - 1;
        return removed_first_element;

    } else if (list->size - 1 == index) { // (When we want to remove the last element in the list)
        // We move the pointer of the last element to the previous element in the list by iterating to the penultimate element
        // And free the removed elements memory and return it's value
       if (list->first->next == NULL) {
        elem_t removed_final_element = list->first->element;
        link_t *free_the_struct1 = list->first;
        list->first = NULL;
        list->last = NULL;
        free(free_the_struct1);
        
        return removed_final_element;    
       }

        link_t *free_the_struct = list->last;
        link_t *next_link = list->first;
        list->size = list->size - 1;

        while (counter != list->size) {
            next_link = next_link->next;
            counter = counter + 1;
        }
        list->last = next_link;
        next_link->next = NULL;
        elem_t removed_last_element = free_the_struct->element;
        free(free_the_struct);
        return removed_last_element;

    } else { 
        // We find the previous element and point it's next pointer to the element after the intented removed element
        // And free the removed elements memory and return it's value
        link_t *linked_list = list->first;
        counter = counter - 1;
        while (counter != index - 1) {
            linked_list = linked_list->next;
            counter = counter + 1;
        }
        link_t *free_the_struct2 = linked_list->next;
        linked_list->next = linked_list->next->next;
        
        list->size = list->size - 1;
        elem_t removed_element = free_the_struct2->element;
        free(free_the_struct2);
        return removed_element;
    }
}

void linked_list_clear(list_t *list) {
    size_t size = list->size;
    for (int i = 0; i < size; i++) {
        linked_list_remove(list, 0);
    }
}


bool linked_list_all(list_t *list, int_predicate prop, void *extra)
{
    size_t size = linked_list_size(list);
    link_t *list_itr = list->first;

    for (int i = 0; i < size; i++) {
        if (!prop(list_itr->element, extra)) {
            return false;   
        } else {
            list_itr = list_itr->next;
        }
    } 
    return true;
}

bool linked_list_any(list_t *list, int_predicate prop, void *extra)
{
    size_t size = linked_list_size(list);
    link_t *list_itr = list->first;

    for (int i = 0; i < size; i++) {
        if (prop(list_itr->element, extra)) {
            return true;   
        } else {
            list_itr = list_itr->next;
        }
    } 
    return false;
}

void linked_list_apply_to_all(list_t *list, apply_int_function fun, void *extra) 
{
    size_t size = linked_list_size(list); 
    link_t *list_itr = list->first;
    int counter = 0;

    
    while (counter != size) {
        elem_t *a = &(list_itr->element);
        fun(a, extra);
        counter++;
        list_itr = list_itr->next;
    }
}



struct iter 
{
  link_t *current;
  list_t *list; /// New field
};

list_iterator_t *list_iterator(list_t *list)
{
  list_iterator_t *result = calloc(1, sizeof(struct iter));

  linked_list_prepend(list, ptr_elem(NULL));

  result->current = list->first;
  result->list = list; /// Iterator remembers where it came from

  return result; 
}

bool iterator_has_next(list_iterator_t *iter) {
    assert(iter->current);
    return iter->current->next != NULL;
}

elem_t iterator_next(list_iterator_t *iter)
{
  assert(iter->current);
  iter->current = iter->current->next;
  if (iter->current == NULL) { return ptr_elem(NULL); }
  return iter->current->element;
}

elem_t iterator_current(list_iterator_t *iter)
{
  return iter->current->element; 
}

void iterator_destroy(list_iterator_t *iter)
{
  free(iter);
}

void iterator_reset(list_iterator_t *iter)
{
  iter->current = iter->list->first;
}

link_t *linked_list_first(list_t *list) {
    return list->first;
}