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


#ifndef LEXER_H
#define LEXER_H

#include "core.h"

BOOL init(const char *file);

BOOL next();

char *get_token();

BOOL is_litteral();

BOOL is_left();

BOOL is_right();

BOOL is_stop();

BOOL is_parenthesis();

BOOL is_call();

#endif