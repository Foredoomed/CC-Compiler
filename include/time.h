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


#ifndef TIME_H
#define TIME_H


#include <time.h>

long get_ctime()
{
  return (long)time(NULL);
}


long elapsed(long first, long second)
{
  //double elapsed = (second.tv_sec - first.tv_sec) * 1000.0;
  //elapsed += (second.tv_usec - first.tv_usec) / 1000.0;

  return (second - first) / 1000;
}






#endif