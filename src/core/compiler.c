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


int parse_call(FILE *target, char *token, map_t *vars)
{
  int len = strlen(token) - 1;
  char temp[len];
  strncpy(temp, token, len);
  temp[len] = 0;

  if(strcmp(temp, "print") != 0){
    printf("The function call %s is not supported\n", temp);
    return 1;
  }

  if(next() == false){
    printf("Not enough arguments to the function call %s\n", temp);
    return 1;
  }

  if(is_litteral()){
    char *call = get_token();
    write_one_operand_call(target, PUSHS, call);

  } else if(is_alpha()){
    char *var = get_token();
    char *value;
    int v = hashmap_get(*vars, var, (void*)value);

    if(v == MAP_MISSING){
      printf("The variable %s does not exist\n", var);
      return 1;
    }

    write_one_operand_call(target, PUSHV, value);

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

int parse_assignment(FILE *target, char *token, map_t *vars)
{
  char temp[6];
  strncpy(temp, token, 6);
  temp[6] = 0;

  int length = strlen(token) - 7;
  char var[length];
  strncpy(var, token+6, length);
  var[length] = 0;

  if(strcmp(temp, "string") != 0){
    printf("The assignment only supports string\n");
    return 1;
  }

  if(next() == false){
     printf("Syntax error : invalid assignment\n");
     return 1;
  }

  char *t = get_token(); /* It changes */
  int len = strlen(t);
  char value[len];
  strcpy(value, t);
  value[len] = 0;

  int v = hashmap_get(*vars, var, (void*)value);

  if(is_litteral()){

    write_one_operand_call(target, PUSHS, var);

  } else if(is_alpha()){

    if(v == MAP_MISSING){
      printf("The variable %s does not exist\n", var);
      return 1;
    }

    write_one_operand_call(target, PUSHV, var);
  }

  if(next() == false || is_stop() == false){
    printf("Every instruction must be closed by a semicolon\n");
    return 1;
  }

  hashmap_put(*vars, var, value);
  write_one_operand_call(target, ASSIGN, var);

  return 0;
}

int scan(FILE *target)
{
  map_t vars = hashmap_new();

  write_header(target);

  int ret = 0;

  while(next() == true){

    if(is_alpha() == false){

      printf("An instruction can only start with a function call or assignment\n");
      return 1;
    }

    char *t = get_token();

    if(next() == false){

      printf("Incomplete instruction\n");
      return 1;

    }

    if(is_left()){

      ret = parse_call(target, t, &vars);  /* It is a call */

    } else if(next() == true && is_assignment()){

      ret = parse_assignment(target, t, &vars);  /* It is an assignment */

    } else {
      printf("Not a valid instruction\n");
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
  int length;

  /* make xxx.ccs to xxx.ccc */
  if(name != NULL){
    length = strlen(name) - 2;
  }else {
    length = strlen(file) - 1;
  }

  char output[length];
  strncpy(output, name == NULL ? file : ++name, length);
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

