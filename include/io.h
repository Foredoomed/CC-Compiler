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


#ifndef IO_H
#define IO_H


#include <stdio.h>
#include <string.h>
#include "code.h"
#include "utils.h"

void read_char(const char *file, char chars[])
{
  FILE *fp;
  fp = fopen(file, "r");

  if(NULL == fp){
    return;
  }

  fread(chars, sizeof(chars), 1, fp);
  fclose(fp);

}


void write_header(FILE *stream)
{
  fprintf(stream, "%s", "Clean C");
}

void write_end(FILE *stream)
{
  fprintf(stream, "%d", END);
}

void write_simple_call(FILE *stream, CODE code)
{
  fprintf(stream, "%d", code);
}

void write_one_operand_call(FILE *stream, CODE code, char *litteral)
{
  fprintf(stream, "%d", code);

}

void write_litteral(FILE *stream, char *litteral)
{
  fprintf(stream, "%s", 'S');
  fprintf(stream, "%d", strlen(litteral) - 2);

  char *temp = substring(litteral, 1, strlen(litteral) - 2);
  fprintf(stream, "%s", temp);
}





#endif