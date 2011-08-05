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
#include "scss.h"
#include <stdio.h>

static void s_dump_nodes(SCSSNodePtr_t nowNode, int level);

void
scss_dump_nodes(SCSSDocPtr_t doc)
{
  s_dump_nodes(doc->rootNode->child, 0);
}


static void
s_dump_nodes(SCSSNodePtr_t nowNode, int level)
{
  SCSSNodePtr_t curNode;
  int ii;

  for (curNode = nowNode->next; curNode != nowNode; curNode = curNode->next) {
    for (ii=0; ii<level; ii++) {
      printf("  ");
    }
    if (IS_STYLESHEET(curNode)) {
      printf("stylesheet:");
    }
    else if (IS_ATKEYWORD(curNode)) {
      printf("atkeyword:");
    }
    else if (IS_SELECTOR(curNode)) {
      printf("selector:");
    }
    else if (IS_PROPERTY(curNode)) {
      printf("property:");
    }
    printf("name:[%s] value1:[%s] value2:[%s]\n", curNode->name, curNode->value1, curNode->value2);
    if (curNode->child != NULL) {
      s_dump_nodes(curNode->child, level + 1);
    }
  }
}
