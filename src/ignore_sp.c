/*
 * Copyright (C) 2005-2008 Atsushi Konno All rights reserved.
 * Copyright (C) 2005 QSDN,Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "scss_string.h"

/**
 * ignore space
 */
int
scss_ignore_space(const char *s, int len, apr_size_t *nl_counter)
{
  register int ii;
  register char *sp;
  apr_size_t counter = 0;

  if (! s) 
    return 0;
  if (len <= 0) 
    return 0;
  sp = (char *)s;

  counter = *nl_counter;

  for(ii=0;
      *sp && is_white_space(*sp) && ii<len;
      ii++, sp++)
    if (*sp == '\n') counter++;

  *nl_counter = counter;
  return (sp - s);
}
/*
 * vim:ts=2 et
 */
