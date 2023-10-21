#pragma once

#include <stdlib.h>

union elem
{
  int int_value;
  void *ptr_value;
  char *str_value;
};

typedef union elem elem_t;

#define int_elem(x) (elem_t) { .int_value=(x) }
#define ptr_elem(x) (elem_t) { .ptr_value=(x) }
#define str_elem(x) (elem_t) { .str_value=(x) }

typedef bool(*eq_function)(elem_t a, elem_t b);
typedef bool(*predicate)(elem_t key, elem_t value, void *extra);
typedef void(*apply_function)(elem_t key, elem_t *value, void *extra);
