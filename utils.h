#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);

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

#endif