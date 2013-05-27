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
  fprintf(stream, "%s", "Clean C");
}

void write_end(FILE *stream)
{
  fprintf(stream, "%d", (int)END);
}

void write_simple_call(FILE *stream, CODE code)
{
  fprintf(stream, "%d", (int)code);
}

void write_litteral(FILE *stream, char *litteral)
{
  fprintf(stream, "%s", "S");

  /* Remove double quoters */
  int length =(int)(strlen(litteral) - 2);
  fprintf(stream, "%d", length);

  char temp[length];
  strncpy(temp, litteral + 1, length);
  temp[length] = 0;

  fprintf(stream, "%s", temp);
}

void write_one_operand_call(FILE *stream, CODE code, char *litteral)
{
  fprintf(stream, "%d", (int)code);

  write_litteral(stream, litteral);
}

