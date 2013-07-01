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
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"
#include "code.h"
#include "type.h"
#include "hash.h"


int parse_call(FILE *target, char *function, hash_t *var_map)
{

  if(strcmp(function, "print") != 0){
    printf("The function call %s is not supported\n", function);
    return 1;
  }

  if(next() == false){
    printf("Not enough arguments to the function call %s\n", function);
    return 1;
  }

  if(is_litteral()){
    char *call = get_token();
    write_one_operand_call(target, PUSHS, call);

  } else if(is_alpha()){
    char *var_name = get_token();

    char *var_value = hash_lookup(var_map, var_name);

    if(NULL == var_value){
      printf("The variable %s does not exist\n", var_name);
      return 1;
    }

    write_one_operand_call(target, PUSHV, var_name);

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

int parse_assignment(FILE *target, char *token, hash_t *var_map)
{
  //int type_length = strlen(token);
  //char type[type_length];
  //strncpy(type, token, type_length-1);
  //type[type_length] = '\0';


  // int length = 0;
  // if(strchr(token,'=') == NULL){
  //   length = strlen(token) - type_length + 1;
  // } else {
  //   length = strlen(token) - type_length;
  // }
  // char var_name[length];
  // strncpy(var_name, token+type_length-1, length);
  // var_name[length] = '\0';
  int var_type_length = strlen(token);
  char var_type[var_type_length + 1];
  memcpy(var_type, token, var_type_length);
  var_type[var_type_length] = '\0';

  char *current = get_token();
  int var_name_length = strlen(current);
  char var_name[var_name_length];
  memcpy(var_name, current, var_name_length - 1);
  var_name[var_name_length-1] = '\0';

  if(strcmp(var_type, "string") != 0){
    printf("Syntax error : only supports string assignment\n");
    return 1;
  }

  if(next() == false){
     printf("Syntax error : invalid assignment\n");
     return 1;
  }

  current = get_token();
  // int len = strlen(t);
  // char var_value[len];
  // strcpy(var_value, t);
  // var_value[len] = '\0';
  int var_value_length = strlen(current);
  char var_value[var_value_length + 1];
  memcpy(var_value, current, var_value_length);
  var_value[var_value_length] = '\0';

  if(is_litteral()){

    write_one_operand_call(target, PUSHS, var_value);

  } else if(is_alpha()){

    char *var_value = hash_lookup(var_map, var_name);

    if(NULL == var_value){
      printf("The variable %s does not exist\n", var_name);
      return 1;
    }

    write_one_operand_call(target, PUSHV, var_name);
  }

  if(next() == false || is_stop() == false){
    printf("Every instruction must be closed by a semicolon\n");
    return 1;
  }

  hash_insert(var_map, var_name, var_value);
  write_variable_name(target, ASSIGN, var_name);

  return 0;
}

int scan(FILE *target)
{
  hash_t *var_map = malloc(sizeof(hash_t));
  hash_init(var_map, 1024);

  write_header(target);

  int ret = 0;

  while(next() == true){

    if(is_alpha() == false){

      printf("An instruction can only start with a function call or assignment\n");
      return 1;
    }

    char *current_token = get_token();

    char *temp;
    strcpy(temp, current_token);

    if(next() == false){

      printf("Incomplete instruction\n");
      return 1;

    }

    if(is_left()){

      ret = parse_call(target, temp, var_map);  /* It is a call */

    } else if(is_assignment()){

      ret = parse_assignment(target, temp, var_map);  /* It is an assignment */

    } else {
      printf("Not a valid instruction\n");
      return 1;
    }

    if(ret == 1 ){
      printf("Syntax error\n");
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
  if(NULL != name){
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

  printf("Finished in %.000f seconds\n", t);

  return result;

}

