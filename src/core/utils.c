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


long get_time()
{
  return (long)(time(NULL));
}

double elapsed(long start, long end)
{
  //double elapsed = (second.tv_sec - first.tv_sec) * 1000.0;
  //elapsed += (second.tv_usec - first.tv_usec) / 1000.0;

  return (end - start) / 1000.0;
}

void read_char(const char *file, char chs[])
{
  FILE *fp;
  fp = fopen(file, "r");

  if(NULL == fp){
    printf("Error opening file : %s\n", file);
    return;
  }

  //fread(chs, sizeof(chs), 1, fp);

  char line[32];
  while(fgets(line, sizeof line, fp) != NULL){
    strcat(chs, line);
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

void write_litteral(FILE *stream, char *value)
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

  write_litteral(stream, value);
}

int get_type_length(const char *token)
{
  int ret = 0;
  if(strstr(token, "string") != NULL){
    ret = 7;
  }else if(strstr(token, "int") != NULL){
    ret = 4;
  }

  return ret;
}

void write_one_operand(FILE *stream, CODE code, int value)
{
  fprintf(stream, "%d", (int)code);
  fprintf(stream, "%d", value);
}

void write_variable_name(FILE *stream, CODE code, char *value)
{
  fprintf(stream, "%d", (int)code);
  fprintf(stream, "%s", value);
}

