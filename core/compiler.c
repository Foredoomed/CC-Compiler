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


#ifndef COMPILER_H
#define COMPILER_H

#include <string.h>
#include <stdio.h>
#include "core.h"
#include "utils.h"
#include "time.h"
#include "lexer.h"
#include "code.h"

int compile(const char *file)
{
  printf("Compiling : %s", file);

  long start = get_ctime();

  BOOL success = init(file);

  if(!success){
    printf("Unable to open file : %s", file);
    return 1;
  }

  char *output_ext = ".ccc";
  char *ext = strstr(file, '.');
  int found = 0;
  if(NULL != ext){
    found = ext - file;
  }

  if(!found){
    printf("Invalid file : %s", file);
    return 1;
  }

  char *output;
  strncat(output, file, found);
  strcat(output, output_ext);

  FILE *out = fopen(output, "wb+");

  if(NULL == out){
    return 1;
  }

  int result = scan();

  fclose(out);

  if(result != 0){
    remove(out);
  }

  long end = get_ctime();

  printf("Compliation completed : %l", elapsed(start, end));

  return result;

}

int scan()
{
  while(next()){

    if(!is_call()){
      printf("%s\n","An instruction can only start with a call");
      return 1;
    }

    char *call = get_token();

    if(!strcmp(call, "print")){
      printf("The call %s is not supported\n", call);
      return 1;
    }

    if(!next() || !is_left()){
      printf("%s\n","A call must be followed by a left parenthesis");
      return 1;
    }

    if(!next()){
      printf("%s\n","Not enough arguments to the call");
      return 1;
    }

    if(!is_litteral()){
      printf("%s\n","Can only pass litteral to a call");
      return 1;
    }

    char *litteral = get_token();

    if(!next() || !is_right()){
      printf("%s\n","The call must be closed with a right parenthesis");
      return 1;
    }

    if(!next() || !is_stop()){
      printf("%s\n","Every instruction must be closed by ;");
      return 1;
    }

    write_one_operand_call(PUSH, litteral);
    write_simple_call(PRINT);

  }

  write_end();

  return 0;

}




#endif