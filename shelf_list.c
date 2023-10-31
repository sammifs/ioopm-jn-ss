#include "shelf_list.h"
#include <assert.h>

struct shelf
{
  char *shelf_name;       // holds shelf as for exampel A23
  char *merch_name; // name of merchandise on shelf
  int amount;   // holds the amount

  shelf_t *next;
};

typedef bool(*shelf_eq_function)(char * a, char * b);

bool compare_char_ptr(char *a, char *b) {
  return strcmp(a, b) == 0;
}

struct shelf_list 
{
  shelf_t *first;
  int size;
  shelf_eq_function eq_fun;
};

shelf_t *shelf_create(char *shelf_name, int amount, shelf_t *next) {
    shelf_t *result = calloc(1, sizeof(shelf_t));

    result->shelf_name = shelf_name;
    result->amount = amount;
    result->next = next;

    return result;
}

shelf_list_t *dup_shelf_list(shelf_list_t *old_list) {
  shelf_t *shelf = old_list->first;
  shelf_list_t *new_list = shelf_list_create();

  while(shelf != NULL) {
    char *tmp = shelf->shelf_name;
    char *name = strdup(tmp);
    shelf_list_append(new_list, name, shelf->amount);
    shelf = shelf->next;
  }
  return new_list;
}

void shelf_destroy(shelf_t *shelf) {
  // shelf_t IS RESPONSBILE for shelf_name and WILL destroy it.
  free(shelf->shelf_name);
  free(shelf);
}

void  destroy_first_shelf(shelf_list_t *shelf_list) {
  shelf_t *next = shelf_list->first->next;
  shelf_destroy(shelf_list->first);
  shelf_list->first = next;
}

void shelf_increase_amount(shelf_t *shelf, int amount) {
    shelf->amount += amount;
}

list_t *shelf_decrease_amount(shelf_list_t *locs, int amount) {
  list_t *linked_list = linked_list_create(NULL);
  shelf_t *shelf = locs->first;
  while (amount != 0 && shelf != NULL) {
    if (shelf->amount > amount){
      shelf->amount -= amount;
      amount = 0;
    } else {
      amount -= shelf->amount;
      linked_list_append(linked_list, ptr_elem(shelf->shelf_name));
      //destroy_first_shelf(locs);
      shelf = shelf->next;
    }
  }
  if (linked_list_is_empty(linked_list)) {
    linked_list_destroy(linked_list);
    return NULL;
  }
  return linked_list;
}

shelf_list_t *shelf_list_create() {
  shelf_list_t *new_list = calloc(1,sizeof(shelf_list_t));

  new_list->first = NULL;
  new_list->size = 0;
  new_list->eq_fun = compare_char_ptr;

  return new_list;
}

int shelf_list_size(shelf_list_t *list) {
  return list->size;
}

bool shelf_list_is_empty(shelf_list_t *list) {
  return shelf_list_size(list) == 0;
}

void shelf_list_append(shelf_list_t *list, char *shelf_name, int amount) {
  if (shelf_list_is_empty(list)) {
    list->first = shelf_create(shelf_name, amount, NULL);
    list->size++;
  }
  else {
    shelf_t *current = list->first;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = shelf_create(shelf_name, amount, NULL);
    list->size++;
  }
}

shelf_t *shelf_list_get_shelf(shelf_list_t *list, char *name) {
    shelf_t *current = list->first;
    for (int i = 0; i < shelf_list_size(list); i++) {
        if (list->eq_fun(current->shelf_name, name)) {
            return current;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

void shelf_list_print_name_amount(shelf_list_t *list) {
  assert(list);
  shelf_t *current = list->first;
  while (current != NULL) {
    printf("%s: %d\n", current->shelf_name, current->amount);
    current = current->next;
  }
}

void shelf_list_destroy(shelf_list_t *list) {
  assert(list);
  shelf_t *current = list->first;
  while (current != NULL) {
    shelf_t *tmp = current->next;
    shelf_destroy(current);
    current = tmp;
  }
  free(list);
}