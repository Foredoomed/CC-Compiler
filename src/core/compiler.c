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
#include "hashmap.h"


int parse_call(FILE *target, char *token, map_t vars)
{
  if(strcmp(token, "print") != 0){
    printf("The function call %s is not supported\n", token);
    return 1;
  }

  if(next() == false){
    printf("Not enough arguments to the function call %s\n", token);
    return 1;
  }

  if(is_litteral()){

    write_one_operand_call(target, PUSHS, token);

  } else if(is_alpha()){

    char *value;
    int v = hashmap_get(vars, token, (void*)value);

    if(v == MAP_MISSING){
      printf("The variable %s does not exist\n", token);
      return 1;
    }

    write_one_operand_call(target, PUSHV, token);

  } else {

    printf("Can only pass litteral or a variable to a function call\n");
    return 1;
  }

  if(next() == false || is_right() == false){
    printf("The function call must be closed with a right parenthesis\n");
    return 1;
  }

  if(next() == false || is_stop() == false){
    printf("Every instruction must be closed by a semicolon\n");
    return 1;
  }

  write_simple_call(target, PRINT);

  return 0;
}

int parse_assignment(FILE *target, char *token, map_t vars)
{
  if(next() == false){
     printf("Syntax error : invalid assignment\n");
  }

  char *temp = get_token(); /* It changes */
  int len = strlen(temp);
  char litteral[len];
  strcpy(litteral, temp);
  litteral[len] = 0;

  int v = hashmap_get(vars, token, (void*)litteral);

  if(is_litteral()){

    write_one_operand_call(target, PUSHS, token);

  } else if(is_alpha()){

    if(v == MAP_MISSING){
      printf("The variable %s does not exist\n", token);
      return 1;
    }

    write_one_operand_call(target, PUSHV, token);
  }

  if(next() == false || is_stop() == false){
    printf("Every instruction must be closed by a semicolon\n");
    return 1;
  }

  hashmap_put(vars, token, litteral);
  write_one_operand_call(target, ASSIGN, token);

  return 0;
}

int scan(FILE *target)
{
  map_t vars = hashmap_new();

  write_header(target);

  int ret = 0;

  while(next() == true){

    if(is_alpha() == false){

      printf("An instruction can only start with a function call\n");
      return 1;
    }

    char *token = get_token();

    if(next() == false){

      printf("Incomplete instruction : %s\n", token);
      return 1;

    }

    if(is_left()){

      ret = parse_call(target, token, vars);  /* It is a call */

    } else if(is_assignment()){

      ret = parse_assignment(target, token, vars);  /* It is an assignment */

    } else {
      printf("%s is not a valid instruction\n", token);
      return 1;
    }

  }

  write_end(target);

  return ret;

}

int compile(const char *file)
{
  printf("Compiling : %s\n", file);

  long start = get_time();

  BOOL success = init(file);

  if(!success){
    printf("Error opening file : %s\n", file);
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
    printf("Error opening file : %s\n", output);
    return 1;
  }

  int result = scan(target);

  fclose(target);

  if(result != 0){
    remove(output);
  }

  long end = get_time();

  double t = elapsed(start, end);

  printf("Finished in %lf\n", t);

  return result;

}

