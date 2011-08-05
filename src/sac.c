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
#include "scss.h"
#include "scss_string.h"

static int s_parse_stylesheet(SCSSParserPtr_t parser, SCSSNodePtr_t node);
static char *s_get_import_url(SCSSParserPtr_t parser, SCSSNodePtr_t node);
static char **s_get_import_media(SCSSParserPtr_t parser, SCSSNodePtr_t node);
static char **s_get_media_list(SCSSParserPtr_t parser, SCSSNodePtr_t node);
static SCSSNodePtr_t s_get_selectors_list(apr_pool_t *pool, const char *src);

#define JUDGE_STRINGS(S)  \
    if (*(S) == '\\') {   \
      (S) +=2;            \
      continue;           \
    }                     \
    if (*(S) == '"') {    \
      if (! sq) {         \
        if (! dq) dq = 1; \
        else      dq = 0; \
      }                   \
    }                     \
    if (*(S) == '\'') {   \
      if (! dq) {         \
        if (! sq) sq = 1; \
        else      sq = 0; \
      }                   \
    }
#undef list_insert

#define list_insert(node, point) do {           \
    node->ref  = point->ref;                    \
    *node->ref = node;                          \
    node->next = point;                         \
    point->ref = &node->next;                   \
} while (0)


SCSSParserPtr_t 
scss_parser_new_from_buf(apr_pool_t *pool, const char *buf, char *defaultEncoding)
{
  SCSSParserPtr_t parser;
  SCSSDocPtr_t doc;

  doc    = scss_create_doc(pool);
  doc->source = apr_pstrdup(pool, buf);
  doc->defaultEncoding = apr_pstrdup(pool, defaultEncoding);

  parser = (SCSSParserPtr_t)apr_palloc(doc->pool, sizeof(*parser));
  parser->doc = doc;
  parser->handler = NULL;
  return parser;
}

SCSSSACHandlerPtr_t 
scss_doc_handler_new(SCSSParserPtr_t parser)
{
  SCSSSACHandlerPtr_t handler;

  handler = (SCSSSACHandlerPtr_t)apr_palloc(parser->doc->pool, sizeof(*handler));
  memset(handler, 0, sizeof(*handler));
  parser->handler = handler;
  return handler;
}

const char *
scss_get_perser_version(SCSSParserPtr_t parser)
{
  return "http://www.w3.org/TR/REC-CSS2";
}

int 
scss_parse_stylesheet(SCSSParserPtr_t parser)
{
  int ret;
  if (parser->handler->startDocument) {
    parser->handler->startDocument(parser);
  }
  scss_parser(parser->doc, parser->doc->pool, parser->doc->source);
  ret = s_parse_stylesheet(parser, parser->doc->rootNode->child);

  if (parser->handler->endDocument) {
    parser->handler->endDocument(parser);
  }
  return ret;
}


static int
s_parse_stylesheet(SCSSParserPtr_t parser, SCSSNodePtr_t node)
{
  SCSSNodePtr_t curNode;
  int ret;

  if (! node) return 0;

  for (curNode = node->next; curNode != node; curNode = curNode->next) {
    if (IS_ATKEYWORD(curNode)) {
      if (strcasecmp(curNode->name, "@import") == 0) {
        if (parser->handler->import) {
          char *url = s_get_import_url(parser, curNode);
          char **media = s_get_import_media(parser, curNode);
          parser->handler->import(parser, url, (const char **)media, "");
        }
      }
      else if (strcasecmp(curNode->name, "@media") == 0) {
        char **media = s_get_media_list(parser, curNode);
        if (parser->handler->startMedia) {
          parser->handler->startMedia(parser, (const char **)media);
        }
        ret = s_parse_stylesheet(parser, curNode->child);
        if (ret) {
          return ret;
        }
        if (parser->handler->endMedia) {
          parser->handler->endMedia(parser, (const char **)media);
        }
      }
      else if (strcasecmp(curNode->name, "@page") == 0) {
        if (parser->handler->startPage) {
          parser->handler->startPage(parser, curNode->value1, "");
        }
        ret = s_parse_stylesheet(parser, curNode->child);
        if (ret) {
          return ret;
        }
        if (parser->handler->endPage) {
          parser->handler->endPage(parser, curNode->value1, "");
        }
      }
      else if (strcasecmp(curNode->name, "@page:first") == 0) {
        if (parser->handler->startPage) {
          parser->handler->startPage(parser, curNode->value1, ":first");
        }
        ret = s_parse_stylesheet(parser, curNode->child);
        if (ret) {
          return ret;
        }
        if (parser->handler->endPage) {
          parser->handler->endPage(parser, curNode->value1, ":first");
        }
      }
      else if (strcasecmp(curNode->name, "@page:right") == 0) {
        if (parser->handler->startPage) {
          parser->handler->startPage(parser, curNode->value1, ":right");
        }
        ret = s_parse_stylesheet(parser, curNode->child);
        if (ret) {
          return ret;
        }
        if (parser->handler->endPage) {
          parser->handler->endPage(parser, curNode->value1, ":right");
        }
      }
      else if (strcasecmp(curNode->name, "@page:left") == 0) {
        if (parser->handler->startPage) {
          parser->handler->startPage(parser, curNode->value1, ":left");
        }
        ret = s_parse_stylesheet(parser, curNode->child);
        if (ret) {
          return ret;
        }
        if (parser->handler->endPage) {
          parser->handler->endPage(parser, curNode->value1, ":left");
        }
      }
      else if (strcasecmp(curNode->name, "@font-face") == 0) {
        if (parser->handler->startFontFace) {
          parser->handler->startFontFace(parser);
        }
        ret = s_parse_stylesheet(parser, curNode->child);
        if (ret) {
          return ret;
        }
        if (parser->handler->endFontFace) {
          parser->handler->endFontFace(parser);
        }
      }
    }
    else if (IS_SELECTOR(curNode)) {
      SCSSNodePtr_t selectors = s_get_selectors_list(parser->doc->pool, curNode->name);
      if (parser->handler->startSelector) {
        parser->handler->startSelector(parser, selectors);
      }
      ret = s_parse_stylesheet(parser, curNode->child);
      if (ret) {
        return ret;
      }
      if (parser->handler->endSelector) {
        parser->handler->endSelector(parser, selectors);
      }
    }
    else if (IS_PROPERTY(curNode)) {
      if (parser->handler->property) {
        parser->handler->property(parser, curNode->name, curNode->value1, (curNode->value2 != NULL));
      }
    }
  }
  return 0;
}


static char *
s_get_import_url(SCSSParserPtr_t parser, SCSSNodePtr_t node)
{
  char *ret;
  char *src = apr_pstrdup(parser->doc->pool, node->value1);
  char *spos;
  if (scss_starts_with(src, "url")) {
    src += 3;
  }
  while(*src) {
    if (! is_white_space(*src)) break;
    src++;
  }
  int pc = 0;
  int dq, sq;

  dq = sq = 0;
  spos = src;
  while(*src) {
    JUDGE_STRINGS(src); 
    if (!dq && !sq && !pc && *src == '(') {
      pc++;
      src++;
      spos = src;
      continue;
    }
    if (!dq && !sq && pc && *src == ')') {
      pc--;
      if (! pc) {
        break;
      }
    }
    src++;
  }

  ret = apr_palloc(parser->doc->pool, src - spos + 1);
  memcpy(ret, spos, src - spos);
  ret[src-spos] = 0;
  return ret;
}

static char **
s_get_import_media(SCSSParserPtr_t parser, SCSSNodePtr_t node)
{
  int ii;
  char **media = (char **)apr_palloc(parser->doc->pool, sizeof(char *) * SCSS_MEDIA_TYPE_NUM);
  for (ii=0; ii<SCSS_MEDIA_TYPE_NUM;ii++) {
    media[ii] = NULL;
  }

  char *pstat;
  char *src = apr_pstrdup(parser->doc->pool, node->value2);
  ii = 0;
  while(1) {
    char *tmp = apr_strtok(src, ",", &pstat);
    if (!tmp) {
      break;
    }
    src = NULL;
    media[ii] = scss_trim(parser->doc->pool, tmp);
    if (++ii>=SCSS_MEDIA_TYPE_NUM) break;
  }
  return media;
}


static char **
s_get_media_list(SCSSParserPtr_t parser, SCSSNodePtr_t node)
{
  return s_get_import_media(parser, node);
}

static SCSSNodePtr_t
s_get_selectors_list(apr_pool_t *pool, const char *src)
{
  char *s = apr_pstrdup(pool, src);
  char *pstat;
  SCSSNodePtr_t headNode;

  headNode = scss_create_node(pool);

  while(1) {
    char *one = apr_strtok(s, ",", &pstat);
    if (!one) {
      break;
    }
    s = NULL;
    one = scss_trim(pool, one);
    if (*one) {
      SCSSNodePtr_t node = scss_create_node(pool);
      node->name = one;
      list_insert(node, headNode);
    }
  }
  return headNode;
}


void *
scss_get_user_data(SCSSParserPtr_t parser)
{
  if (parser->doc) {
    return parser->doc->userData;
  }
  return NULL;
}


void
scss_set_user_data(SCSSParserPtr_t parser, void *userData)
{
  if (parser->doc) {
    parser->doc->userData = userData;
  }
}
/*
 * vim:ts=2 et
 */
