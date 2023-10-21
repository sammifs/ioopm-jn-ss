#include "shelf_list.h"
#include <assert.h>

struct shelf
{
  char *shelf_name;       // holds shelf as for exampel A23
  char *merch_name; // name of merchandise on shelf
  int amount;   // holds the amount in "ören"

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

void shelf_destroy(shelf_t *shelf) {
  // shelf_t IS RESPONSBILE for shelf_name and WILL destroy it.
  free(shelf->shelf_name);
  free(shelf);
}

void shelf_increase_amount(shelf_t *shelf, int amount) {
    shelf->amount += amount;
}

void shelf_decrease_amount(shelf_t *shelf, int amount) {
    shelf->amount -= amount;
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