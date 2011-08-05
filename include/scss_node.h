/*
 * Copyright (C) 2008 Atsushi Konno All rights reserved.
 * Copyright (C) 2008 QSDN,Inc. All rights reserved.
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
#if !defined(__SCSS_NODE_H__)
#define __SCSS_NODE_H__

#include "apr_pools.h"

typedef enum _SCSSType_t SCSSType_t;
enum _SCSSType_t {
  SCSSTYPE_SENTINEL = 0,
  SCSSTYPE_STYLESHEET = 1,
  SCSSTYPE_ATKEYWORD = 2,
  SCSSTYPE_SELECTOR,
  SCSSTYPE_PROPERTY,
};


typedef struct _SCSSNode_t SCSSNode_t;
typedef SCSSNode_t *SCSSNodePtr_t;

struct _SCSSNode_t {
  SCSSType_t type;
  SCSSNodePtr_t next;
  SCSSNodePtr_t *ref;
  SCSSNodePtr_t child;
  char *name;
  char *value1;
  char *value2;
  int line;
};

/**
 * create new node.
 *
 * @param pool - use pool object.
 * @return SCSSNode Object.
 */
extern SCSSNodePtr_t scss_create_node(apr_pool_t *pool);
#endif
