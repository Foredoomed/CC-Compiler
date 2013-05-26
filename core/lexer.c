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
#include "core.h"
#include "utils.h"


#define MAX 4096
char chs[MAX];
char token[MAX];
int pos = 0; /* pos of chs, index of token is pos - 1 */


BOOL init(const char *file)
{
  read_char(file, chs);

  return chs != NULL;
}

BOOL next()
{
  char current[] = "\0\0";

  current[0] = chs[pos];

  while((current[0] == '\n' || current[0] == ' ') && current[0] != '\0'){
    pos++;
  }

  if(current[0] == '\0'){
    return false;
  }

  if(current[0] == '(' || current[0] == ')' || current[0] == ';'){
    strcat(token, current);
    pos++;
  }
  else if(current[0] == '"'){
    strcat(token, "\"");

    while((current[0] = chs[++pos]) != '"'){
      strcat(token, current);
    }

    strcat(token, "\"");
    pos++;
  }
  else {
    strcat(token, current);

    while((current[0] = chs[++pos]) && !(current[0] == '(' || current[0] == ')' || current[0] == ';' || current[0] == ' ')){
      strcat(token, current);
    }
  }

  if(pos == MAX - 1){
    return false;
  }

  if(token[0] == 0){
    return false;
  }

  return true;

}

char *get_token()
{
  return token;
}

BOOL is_litteral()
{
  return token[pos - 1] == '"';
}

BOOL is_left()
{
  return token[pos - 1] == '(';
}

BOOL is_right()
{
  return token[pos - 1] == ')';
}

BOOL is_stop()
{
  return token[pos - 1] == ';';
}

BOOL is_parenthesis()
{
  return is_left() || is_right();
}

BOOL is_call()
{
  return !is_parenthesis() && !is_litteral() && !is_stop();
}
