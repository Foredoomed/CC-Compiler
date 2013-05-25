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
#include <stdio.h>
#include "utils.h"
#include "lexer.h"
#include "code.h"


int scan(FILE *target)
{

  write_header(target);

  while(next() == true){

    if(is_call() == false){
      printf("An instruction can only start with a call\n");
      return 1;
    }

    char *call = get_token();

    if(strcmp(call, "print") != 0){
      printf("The call %s is not supported\n", call);
      return 1;
    }

    if(next() == false || is_left() == false){
      printf("A call must be followed by a left parenthesis\n");
      return 1;
    }

    if(next() == false){
      printf("Not enough arguments to the call\n");
      return 1;
    }

    if(is_litteral() == false){
      printf("Can only pass litteral to a call\n");
      return 1;
    }

    char *litteral = get_token();

    if(next() == false || is_right() == false){
      printf("The call must be closed with a right parenthesis\n");
      return 1;
    }

    if(next() == false || is_stop() == false){
      printf("Every instruction must be closed by ;\n");
      return 1;
    }

    write_one_operand_call(target, PUSH, litteral);
    write_simple_call(target, PRINT);

  }

  write_end(target);

  return 0;

}

int compile(const char *file)
{
  printf("Compiling : %s\n", file);

  long start = get_time();

  BOOL success = init(file);

  if(!success){
    printf("Unable to open file : %s\n", file);
    return 1;
  }

  char *found = strstr(file, ".ccs");

  if(NULL == found){
    printf("Invalid file : %s\n", file);
    return 1;
  }

  char *name = strrchr(file, '/');
  int length = strlen(name); /* make xxx.ccs to xxx.ccc */
  char output[length];
  strncpy(output, ++name, length - 2);
  strcat(output, "c");

  FILE *target = fopen(output, "wb+");

  if(NULL == target){
    printf("Unable to open file : %s\n", output);
    return 1;
  }

  int result = scan(target);

  fclose(target);

  if(result != 0){
    remove(output);
  }

  long end = get_time();

  long t = elapsed(start, end);

  printf("Compliation completed : %ld\n", t);

  return result;

}

