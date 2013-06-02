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


#include <string.h>
#include <ctype.h>
#include "core.h"
#include "utils.h"


#define MAX 1024
char chs[MAX];
char token[MAX];
int pos = 0; /* index of chs */
int tpos = 0; /* index of token */


char *get_token()
{
  return token;
}

BOOL is_litteral()
{
  return token[tpos - 1] == '"';
}

BOOL is_left()
{
  return token[tpos - 1] == '(';
}

BOOL is_right()
{
  return token[tpos - 1] == ')';
}

BOOL is_stop()
{
  return token[tpos - 1] == ';';
}

BOOL is_parenthesis()
{
  return is_left() || is_right();
}

BOOL is_call()
{
  return !is_parenthesis() && !is_litteral() && !is_stop();
}

int is_alpha()
{
  return isalpha(token[0]);
}

BOOL is_assignment()
{
  return token[tpos - 1] == '=';
}


BOOL init(const char *file)
{
  read_char(file, chs);

  return chs != NULL;
}

BOOL next()
{
  char current[] = "\0\0";

  current[0] = chs[pos];

  while(isspace(current[0]) && current[0] != '\0'){
    current[0] = chs[++pos];
  }

  if(current[0] == '\0'){
    return false;
  }

  if(current[0] == '"'){

    memset(token, 0, sizeof(token)); /* Clear the array */
    strcpy(token, current);

    tpos = 1;
    while((current[0] = chs[++pos]) != '"'){
      strcat(token, current);
      tpos++;
    }

    current[0] = '"';
    strcat(token, current);
    tpos++;
    pos++;

  } else if(isalpha(current[0])){

    if(tpos == 0){
      memset(token, 0, sizeof(token)); /* Clear the array */
      strcpy(token, current);
      tpos = 1;

    } else {
      strcat(token, current);
      tpos++;
    }

    while((current[0] = chs[++pos]) && isalpha(current[0])){
      strcat(token, current);
      tpos++;
    }

  } else {

    strcat(token, current);
    pos++;
    tpos++;

  }

  if(pos == MAX - 1){
    return false;
  }

  if(token[0] == 0){
    return false;
  }

  return true;

}
