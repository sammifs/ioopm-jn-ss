#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int string_to_int(elem_t str) {
    int hash = 5381;
    unsigned char *ptr = (unsigned char *)str.ptr_value;

    while (*ptr) {
        hash = ((hash << 5) + hash) + *ptr; // hash * 33 + c
        ptr++;
    }

    return hash;
}

int elem_t_to_int(elem_t elem) {
  return elem.int_value;
}



int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

bool is_char(char *str) {
  return strlen(str) <= 1;
}

bool compare_str(elem_t a, elem_t b) {
  char *a_str = a.str_value;
  char *b_str = b.str_value;
  return (strcmp(a_str, b_str) == 0);
}

int char_to_int(elem_t A) {
  return A.int_value;
}

bool compare_int(elem_t a, elem_t b) {
  return a.int_value == b.int_value;
}

/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
  return strlen(str) > 0;
}

char *read_string(char *buf, int buf_siz) 
{
  int i = -1;
  
  do 
  {
    ++i;
    buf[i] = getchar();
  }
  while (buf[i] != '\n' && buf[i] != EOF && i < buf_siz);
  
  buf[i] = '\0';

  return buf;
}

answer_t ask_question(char *question, check_func check, convert_func convert) 
{
    char buf[255];
    char *inputstring;
    do
    {
        printf("%s\n", question);
        inputstring = read_string(buf, 255);
    } 
    while (!check(inputstring));
    
    return convert(inputstring);
}

bool is_number(char *str)
{
  int length = strlen(str);

  for (int i = 0; i < length; ++i) 
  {
    if (!isdigit(str[i])) 
    {
      if (!(i == 0 && str[i] == '-' && length > 1)) //first char can be '-', only if string is longer than one char
      {    
        return false;
      }
    }
  }  
  return true;
}

bool is_shelf(char *str)
{
  int length = strlen(str);

  if (length != 3 || !(isupper(str[0]))) //shelf has to have length 2+ and 1st has to be upper 
  {
    return false;
  }

  for (int i = 1; i < length; ++i) 
  {
    if (!isdigit(str[i]))
    {
      return false;
    }
  }  
  return true;
}

bool is_positive_number(char *str)
{
  int length = strlen(str);

  if (str[0] == '0' && length == 1) { return false; }

  for (int i = 0; i < length; ++i) 
  {
    if (!isdigit(str[i])) 
    {
      return false;
    }
  }  
  return true;
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}

int ask_question_positive_int(char *question) {
  answer_t answer = ask_question(question, is_positive_number, (convert_func) atoi);
  return answer.int_value;
}

char *ask_question_string(char *question)
{
 return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

char *ask_question_shelf(char *question)
{
    return ask_question(question, is_shelf, (convert_func) strdup).string_value;
}

char str_to_char(char *str) {
  return *str;
}

char ask_question_char(char *question)
{
 return (ask_question(question, is_char, (convert_func) str_to_char).char_value);
}
