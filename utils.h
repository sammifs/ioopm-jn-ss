#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "common.h"
#include "logic.h"

extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);

int cmpstringp(const void *p1, const void *p2);

int string_to_int(elem_t str);
int char_to_int(elem_t A);

bool compare_int(elem_t a, elem_t b);
bool compare_ptr(elem_t a, elem_t b);
bool compare_str(elem_t a, elem_t b);

char *read_string(char *buf, int buf_siz);
answer_t make_float(char *str);
bool not_empty(char *str);

bool is_shelf(char *str);
bool is_number(char *str);
bool is_float(char *str);

answer_t ask_question(char *question, check_func check, convert_func convert);
int ask_question_int(char *question);
double ask_question_float(char *question);
char *ask_question_string(char *question);
char *ask_question_shelf(char *question);
char *ask_question_char(char *question);


int string_length(char *inputstring);
void print(char *inputstring);
void println(char *inputstring);

bool yes_or_no(char *qstn);

#endif