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


#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>
#include "code.h"


long get_time();

double elapsed(long start, long end);

void read_char(const char *file, char chs[]);

void write_header(FILE *stream);

void write_end(FILE *stream);

void write_simple_call(FILE *stream, CODE code);

void write_one_operand_call(FILE *stream, CODE code, char *value);

void write_one_operand(FILE *stream, CODE code, char *value);

void write_string_operand(FILE *stream, char *value);

void write_variable_name(FILE *stream, CODE code, char *value);

void copy(char *dest, char *src);


#endif
