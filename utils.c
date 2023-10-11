#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

answer_t ask_question(char *question, check_func check, convert_func convert);
int ask_question_int(char *question);
answer_t make_float(char *str);
double ask_question_float(char *question);
char *ask_question_string(char *question, char *buf, int buf_siz);
bool not_empty(char *str);
char *read_string(char *buf, int buf_siz);
int string_length(char *inputstring);
void print(char *inputstring);
void println(char *inputstring);


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

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}

answer_t make_float(char *str)
{
  return (answer_t) { .float_value = atof(str) };
}


double ask_question_float(char *question)
{
  return ask_question(question, is_float, make_float).float_value;
}

char *ask_question_string(char *question, char *buf, int buf_siz)
{
 return ask_question(question, not_empty, (convert_func) strdup).string_value;
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