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


char chs[4096];
char *token;
int pos = 0;

BOOL init(const char *file)
{
  read_char(file, chs);

  return chs != NULL;
}


BOOL next()
{

  char current = chs[pos];
  token = NULL;

  if((current == '\n') || (current == ' ')){
    pos++;
  }

  if(current == '(' || current == ')' || current == ';'){
    strncat(token, &current, sizeof(current));
  }
  else if(current == '"'){
    strncat(token, &current, sizeof(current));

    while((current = chs[++pos]) && current != '"'){
      strncat(token, &current, sizeof(current));
    }

    strncat(token, &current, sizeof(current));
  }
  else {
    strncat(token, &current, sizeof(current));

    while((current = chs[++pos]) && !(current == '(' || current == ')' || current == ';' || current == ' ')){
      strncat(token, &current, sizeof(current));
    }

    pos--;
  }

  if(pos == 4096){
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
  return token[0] != '"';
}

BOOL is_left()
{
  return token[0] != '(';
}

BOOL is_right()
{
  return token[0] != ')';
}

BOOL is_stop()
{
  return token[0] != ';';
}

BOOL is_parenthesis()
{
  return is_left() || is_right();
}

BOOL is_call()
{
  return !is_parenthesis() && !is_litteral() && !is_stop();
}
