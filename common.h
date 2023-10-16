#pragma once

#include <stdlib.h>

union elem
{
  int int_value;
  void *ptr_value;
};

struct shelf
{
  char *shelf;       // holds shelf as for exampel A23
  int amount;   // holds the amount in "ören"
};

typedef struct shelf shelf_t;
typedef union elem elem_t;

#define int_elem(x) (elem_t) { .int_value=(x) }
#define ptr_elem(x) (elem_t) { .ptr_value=(x) }

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void(*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
