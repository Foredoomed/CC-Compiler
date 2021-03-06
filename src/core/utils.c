/***********************************************************************
**
**  Clean C
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**  http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
************************************************************************/


#include <stdio.h>
#include <string.h>
#include <time.h>
#include "code.h"
#include "util.h"


long get_time()
{
  return (long)(time(NULL));
}

double elapsed(long start, long end)
{
  return difftime(start, end);
}

void read_char(const char *file, char buffer[])
{
  FILE *fp;
  fp = fopen(file, "r");

  if(NULL == fp){
    printf("Cannot open file : %s\n", file);
    return;
  }

  char line[128];
  while(fgets(line, sizeof(line), fp) != NULL){
    strcat(buffer, line);
  }

  fclose(fp);
}

void write_header(FILE *stream)
{
  fprintf(stream, "%s", "CC");
}

void write_end(FILE *stream)
{
  fprintf(stream, "%d", (int)END);
}

void write_simple_call(FILE *stream, CODE code)
{
  fprintf(stream, "%d", (int)code);
}

void write_string_operand(FILE *stream, char *value)
{
  int length;
  char *index = strchr(value, '"');
  if(index != NULL){
    fprintf(stream, "%s", "S");
    length = (int)(strlen(value) - 2);  /* Remove double quoters */
    fprintf(stream, "%d", length);
  } else {
    length = (int)strlen(value);
  }

  char temp[length];
  strncpy(temp, index == NULL ? value : value + 1, length);
  temp[length] = 0;

  fprintf(stream, "%s", temp);
}

void write_one_operand_call(FILE *stream, CODE code, char *value)
{
  fprintf(stream, "%d", (int)code);

  write_string_operand(stream, value);
}

void write_one_operand(FILE *stream, CODE code, char *value)
{
  fprintf(stream, "%d", (int)code);
  fprintf(stream, "%s", value);
}

void write_variable_name(FILE *stream, CODE code, char *value)
{
  fprintf(stream, "%d", (int)code);
  fprintf(stream, "%d", (int)strlen(value));
  fprintf(stream, "%s", value);
}

void write_int(FILE *stream, int value)
{
  fprintf(stream, "%d", value);
}

