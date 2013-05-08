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


#ifndef CODE_H
#define CODE_H

typedef enum code {

  /*END = 0,

  LABEL = 5,

  SLOAD = 10,
  ILOAD = 11,

  SSTORE = 20,
  ISTORE = 21,

  LDCI = 30,
  LDCS = 31,

  JUMP = 40,
  JUMP_IF = 41,
  JUMP_IF_NOT = 42,

  IADD = 50,
  SADD = 51,

  ISUB = 60,

  IMUL = 70,

  IDIV = 80,

  IMOD = 90,

  EQUALS = 100,
  NOT_EQUALS = 101,
  GREATER_THAN = 102,
  LESS_THAN = 103,
  GREATER_THAN_EQUALS = 104,
  LESS_THAN_EQUALS = 105,

  PRINTI = 110,
  PRINTS = 111*/

  PUSH = 0,
  PRINT = 1,
  END = 2


} CODE;



#endif