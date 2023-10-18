#pragma once

#include <stdlib.h>


typedef struct shelf shelf_t;
typedef union elem elem_t;
typedef struct merch merch_t;
typedef struct list ioopm_list_t;

struct merch
{
  int price;   // holds the price
  char *desc;
  ioopm_list_t *locs; 
};


union elem
{
  int int_value;
  char *str_value;
  void *ptr_value;
  shelf_t *shelf_ptr;
  merch_t *merch_ptr;
};

struct shelf
{
  char *shelf;       // holds shelf as for exampel A23
  char *merch_name; // name of merchandise on shelf
  int amount;   // holds the amount in "ören"
};

typedef struct shelf shelf_t;
typedef union elem elem_t;

#define int_elem(x) (elem_t) { .int_value=(x) }
#define ptr_elem(x) (elem_t) { .ptr_value=(x) }
#define str_elem(x) (elem_t) { .str_value=(x) }
#define merch_elem(x) (elem_t) { .merch_ptr=(x) }
#define shelf_elem(x) (elem_t) { .shelf_ptr=(x) }

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void(*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
