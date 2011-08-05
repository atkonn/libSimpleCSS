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
#include "scss_node.h"

SCSSNodePtr_t
scss_create_node(apr_pool_t *pool)
{
  SCSSNodePtr_t node;
  node = apr_palloc(pool, sizeof(SCSSNode_t));

  node->type      = SCSSTYPE_STYLESHEET; 
  node->next      = node;
  node->ref       = &node->next;
  node->child     = NULL;
  node->name      = NULL;
  node->value1    = NULL;
  node->value2    = NULL;

  return node;
}
/*
 * vim:ts=2 et
 */
