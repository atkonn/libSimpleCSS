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
#if !defined(__SCSS_H__)
#define __SCSS_H__

#include "apr_pools.h"
#include "apr_strings.h"
#include "scss_node.h"
#include "scss_iconv.h"

#define ROOT_NODE_SIGNATURE "<rootNode>"

typedef struct _SCSSDoc_t SCSSDoc_t;
typedef SCSSDoc_t *SCSSDocPtr_t;

struct _SCSSDoc_t {
  apr_pool_t    *pool;
  SCSSNodePtr_t rootNode;
  SCSSNodePtr_t nowNode;
  void          *userData;
  char          *source;
  char          *defaultEncoding;
};

#define IS_STYLESHEET(X) ((X)->type == SCSSTYPE_STYLESHEET)
#define IS_ATKEYWORD(X)  ((X)->type == SCSSTYPE_ATKEYWORD )
#define IS_SELECTOR(X)   ((X)->type == SCSSTYPE_SELECTOR  )
#define IS_PROPERTY(X)   ((X)->type == SCSSTYPE_PROPERTY  )


#include "scss_sac.h"

typedef void (*SCSSParserError_fn)(void *userData, const char *func, const char *fname, int line, const char *src, int srcline, char *fmt, ...);



/**
 * for DEBUG. dump Node tree.
 *
 * @param doc     for dump doc object.
 * @param level   please set 0.
 */
extern void scss_dump_nodes(SCSSDocPtr_t doc);

/**
 * CSS Parser.
 *
 * @param doc   - SCSSDoc_t Object.
 * @param ppool - parent pool.
 * @param src   - CSS source.
 * @return SCSSDocPtr_t
 */
extern SCSSDocPtr_t scss_parser(SCSSDocPtr_t doc, apr_pool_t *ppool,  const char *src);

/**
 * CSS Parser Error log.
 */
extern SCSSParserError_fn scss_parser_error;

/**
 * create new doc.
 *
 * @param pool - use pool object.
 * @return SCSSDoc_t object.
 */
extern SCSSDocPtr_t scss_create_doc(apr_pool_t *pool);

/**
 * set user data.
 *
 * @param doc      - SCSSDoc Object.
 * @param userData - user's data.
 */
extern void scss_doc_set_user_data(SCSSDocPtr_t doc, void *userData);

/**
 * get user data.
 *
 * @param doc      - SCSSDoc Object.
 */
extern void *scss_doc_get_user_data(SCSSDocPtr_t doc);
#endif
