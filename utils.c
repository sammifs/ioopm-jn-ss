#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "logic.h"


int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}


// Uses the DJB2 algorithm to hash the string
int string_to_int(elem_t str) {
    int hash = 5381;
    unsigned char *ptr = (unsigned char *)str.ptr_value;

    while (*ptr) {
        hash = ((hash << 5) + hash) + *ptr; // hash * 33 + c
        ptr++;
    }

    return hash;
}

int char_to_int(elem_t A) {
  return A.int_value;
}

bool compare_int(elem_t a, elem_t b) {
  return a.int_value == b.int_value;
}

bool compare_ptr(elem_t a, elem_t b) {
  return a.ptr_value == b.ptr_value;
}

bool compare_str(elem_t a, elem_t b) {
  char *a_str = a.str_value;
  char *b_str = b.str_value;
  return strcmp(a_str, b_str) == 0;
}

/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
  return strlen(str) > 0;
}

bool is_char(char *str) {
  return strlen(str) <= 1;
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


answer_t make_float(char *str)
{
  return (answer_t) { .float_value = atof(str) };
}


bool is_number(char *str)
{
  int length = strlen(str);
  //printf("Length is: %d\n", length);

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
bool is_float(char *str)
{
    int length = strlen(str);
    int dotcount = 0;

  for (int i = 0; i < length; ++i) 
  {
    if (!isdigit(str[i]))  //om stri inte är en siffra och inte godkänd '-' och inte godkänd punkt
    {
      if (!(i == 0 && str[i] == '-' && length > 1)) //first char can be '-' , only if string is longer than one char
      {    
        if (i < length - 1 && str[i] == '.' && dotcount == 0) //any char can be '.' except first and last
        {
          ++dotcount;
        }
        else 
        {
          return false;
        }
      }
    }
  }
  return dotcount == 1;
}

bool is_shelf(char *str)
{
  int length = strlen(str);

  if (length != 3 || !(isupper(str[0]))) //shelf has to have length 3 and 1st has to be upper 
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

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}

double ask_question_float(char *question)
{
  return ask_question(question, is_float, make_float).float_value;
}

char *ask_question_string(char *question)
{
 return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

char *ask_question_shelf(char *question)
{
    return ask_question(question, is_shelf, (convert_func) strdup).string_value;
};

char *ask_question_char(char *question)
{
 return (ask_question(question, is_char, (convert_func) strdup).string_value);
}

int string_length(char *inputstring) 
{
    int i = 0;
    while (inputstring[i] != '\0')
    {
        ++i;
    }
    return i;
}

void print(char *inputstring) 
{
    
    int length = string_length(inputstring);
    
    if (inputstring[length - 1] == '\n') 
    {
        --length;
    }
    for (int i = 0; i <= length; ++i) 
    {
        putchar(inputstring[i]);
    }
}

void println(char *inputstring)
{
    printf("\n");
    print(inputstring);
    printf("\n");
}

bool yes_or_no(char *qstn) {
    printf("%s", qstn);
    // TODO : Maybe toupper?
    char *answer = ask_question_char((""));
    if (*answer == 'Y') {
        free(answer);
        return true;
    } else if (*answer == 'y') {
        free(answer);
        return true;
    } else if (*answer == 'N') {
        free(answer);
        return false;
    } else if (*answer == 'n') {
        free(answer);
        return false;
    } else {
        free(answer);
        printf("You did not give a valid answer! We take that as a no then.\n");
        return false;
    }
}