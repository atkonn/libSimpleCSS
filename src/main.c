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
#include "apr_pools.h"

#include <stdio.h>
/*
 * stylesheet
 *   +--------> @import
 *   +--------> @media 
 *   |            +--> {
 *   |                   selector 
 *   |                      +-----> property
 *   |                   selector
 *   |                      +-----> property
 *   |                 }
 *   +---------> selector
 *   |              +-----> property
 *   +---------> selector
 *                  +-----> property
 */
#undef list_insert
#undef list_remove

#define list_insert(node, point) do {           \
    node->ref  = point->ref;                    \
    *node->ref = node;                          \
    node->next = point;                         \
    point->ref = &node->next;                   \
} while (0)

#define list_remove(node) do {                  \
    *node->ref      = node->next;               \
    node->next->ref = node->ref;                \
} while (0)

#define PASS_COMMENT(S,NL)                  \
    if (*(S) == '/' && *((S) + 1) == '*') { \
      (S) = s_pass_comment((S),(NL));       \
      continue;                             \
    }

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

static char *s_cut_ident(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter);
static const char *s_pass_comment(const char *s, apr_size_t *nl_counter);
static char *s_cut_before_next_semicoron_or_block(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter);
static char *s_cut_before_white_space_or_semicoron(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter);
static char *s_cut_before_block_closer(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter);
static char *s_cut_before_semicoron(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter);
static void s_add_child_node(SCSSDocPtr_t doc, SCSSNodePtr_t nowNode, SCSSNodePtr_t node);
static char *s_get_one_selector(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter);
static char *s_replace_refstring(SCSSDocPtr_t doc, const char *s);
static void s_get_property_list(SCSSDocPtr_t doc, SCSSNodePtr_t nowNode, const char *s);
static char *s_cut_url_function(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter);
static void s_default_error_log(void *userData, const char *func, const char *fname, int line, const char *src, int srcline, char *fmt, ...);

SCSSParserError_fn scss_parser_error = s_default_error_log;

SCSSDocPtr_t
scss_parser(SCSSDocPtr_t doc, apr_pool_t *ppool,  const char *src)
{
  register const char *s;
  int len;
  apr_size_t pass_len;
  apr_size_t nl_counter = 1;

  len = strlen(src);
  if (len == 0) return doc;

  s = (char *)src;

  
  while (*s) {
    int pass = scss_ignore_space(s, len, &nl_counter);
    if (pass) {
      s += pass;
      continue;
    }
    if (*s == '@') {
      SCSSNodePtr_t atnode = scss_create_node(doc->pool);
      char *name;
      char *value1 = "";
      char *value2 = "";
      s++;
      atnode->type = SCSSTYPE_ATKEYWORD;
      atnode->line = nl_counter;
      name  = apr_psprintf(doc->pool, "@%s", s_cut_ident(doc, s, &pass_len, &nl_counter));
      s += pass_len;
      if (strcasecmp(name, "@import") == 0) {
        if (! *s || *s == ';') {
          /* XXX ERROR XXX */
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@import parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "all");
        }
        else {
          value1 = scss_trim(doc->pool, s_cut_before_white_space_or_semicoron(doc, s, &pass_len, &nl_counter));
          if (scss_starts_with(value1, "url")) {
            value1 = scss_trim(doc->pool, s_cut_url_function(doc, s, &pass_len, &nl_counter));
            s += pass_len;
          }
          else {
            s += pass_len + 1;
          }
          if (*s != ';' && *s) {
            value2 = scss_trim(doc->pool, s_cut_before_semicoron(doc, s, &pass_len, &nl_counter));
            s += pass_len + 1;
          }
          else {
            value2 = apr_pstrdup(doc->pool, "all");
          }
        }
      }
      else if (strcasecmp(name, "@media") == 0) {
        if (! *s || *s == ';') {
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@media parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "all");
        }
        else {
          value2 = scss_trim(doc->pool, s_cut_before_next_semicoron_or_block(doc, s, &pass_len, &nl_counter));
          s += pass_len + 1;
          if (*s == '{') {
            value1 = scss_trim(doc->pool, s_cut_before_block_closer(doc, ++s, &pass_len, &nl_counter));
            s += pass_len;
            if (*s == '}') s++;
            if (*value1) {
              char *one_selector = s_get_one_selector(doc, value1, &pass_len, &nl_counter);
              char *vv = value1;
              while (*one_selector) {
                SCSSNodePtr_t selector_node = scss_create_node(doc->pool);
                selector_node->type = SCSSTYPE_SELECTOR;
                selector_node->name = one_selector;
                selector_node->line = nl_counter;
                selector_node->value2 = apr_pstrdup(doc->pool, "");
                s_add_child_node(doc, atnode, selector_node);
                vv += pass_len;
                if (*vv != ';') {
                  if (*vv == '{') vv++;
                  selector_node->value1 = scss_trim(doc->pool, s_cut_before_block_closer(doc, vv, &pass_len, &nl_counter));
                  s_get_property_list(doc, selector_node, selector_node->value1);
                  vv += pass_len;
                  vv = scss_trim(doc->pool, vv);
                  if (*vv == '}') vv++;
                }
                else {
                  selector_node->value1 = apr_pstrdup(doc->pool, "");
                }
                one_selector = s_get_one_selector(doc, vv, &pass_len, &nl_counter);
              }
            }
          }
        }
      }
      else if (strcasecmp(name, "@charset") == 0) {
        if (! *s || *s == ';') {
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@charset parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "");
        }
        else {
          value1 = scss_trim(doc->pool, s_cut_before_semicoron(doc, s, &pass_len, &nl_counter));
          value1 = scss_strip_quote(doc->pool, value1);
          s += pass_len + 1;
          if (strcasecmp(value1, "UTF-8") != 0) {
            apr_size_t enc_len = strlen(s);
            apr_status_t rv = 0;
            char *err_msg;
            char *dst;
            dst = scss_iconv(doc->pool, s, &enc_len, value1, "UTF-8", &rv, &err_msg);
            if (rv != 0) {
              scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter, err_msg);
            }
            s = dst;
          }
        }
      }
      else if (strcasecmp(name, "@page") == 0) {
        if (! *s || *s == ';') {
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "");
        }
        else {
          value1 = scss_trim(doc->pool, s_cut_before_next_semicoron_or_block(doc, s, &pass_len, &nl_counter));
          s += pass_len + 1;
          if (*s == '{') {
            value2 = scss_trim(doc->pool, s_cut_before_block_closer(doc, ++s, &pass_len, &nl_counter));
            s += pass_len;
            if (*s) s++;
          }
          else {
            scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page parse error");
            value1 = apr_pstrdup(doc->pool, "");
            value2 = apr_pstrdup(doc->pool, "");
          }
        }
      }
      else if (strcasecmp(name, "@page:first") == 0) {
        if (! *s || *s == ';') {
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page:first parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "");
        }
        else {
          value1 = scss_trim(doc->pool, s_cut_before_next_semicoron_or_block(doc, s, &pass_len, &nl_counter));
          s += pass_len + 1;
          if (*s == '{') {
            value2 = scss_trim(doc->pool, s_cut_before_block_closer(doc, ++s, &pass_len, &nl_counter));
            s += pass_len;
            if (*s) s++;
          }
          else {
            scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page:first parse error");
            value1 = apr_pstrdup(doc->pool, "");
            value2 = apr_pstrdup(doc->pool, "");
          }
        }
      }
      else if (strcasecmp(name, "@page:right") == 0) {
        if (! *s || *s == ';') {
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page:right parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "");
        }
        else {
          value1 = scss_trim(doc->pool, s_cut_before_next_semicoron_or_block(doc, s, &pass_len, &nl_counter));
          s += pass_len + 1;
          if (*s == '{') {
            value2 = scss_trim(doc->pool, s_cut_before_block_closer(doc, ++s, &pass_len, &nl_counter));
            s += pass_len;
            if (*s) s++;
          }
          else {
            scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page:right parse error");
            value1 = apr_pstrdup(doc->pool, "");
            value2 = apr_pstrdup(doc->pool, "");
          }
        }
      }
      else if (strcasecmp(name, "@page:left") == 0) {
        if (! *s || *s == ';') {
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page:left parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "");
        }
        else {
          value1 = scss_trim(doc->pool, s_cut_before_next_semicoron_or_block(doc, s, &pass_len, &nl_counter));
          s += pass_len + 1;
          if (*s == '{') {
            value2 = scss_trim(doc->pool, s_cut_before_block_closer(doc, ++s, &pass_len, &nl_counter));
            s += pass_len;
            if (*s) s++;
          }
          else {
            scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@page:left parse error");
            value1 = apr_pstrdup(doc->pool, "");
            value2 = apr_pstrdup(doc->pool, "");
          }
        }
      }
      else if (strcasecmp(name, "@font-face") == 0) {
        if (! *s || *s == ';') {
          scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@font-face parse error");
          value1 = apr_pstrdup(doc->pool, "");
          value2 = apr_pstrdup(doc->pool, "");
        }
        else {
          s_cut_before_next_semicoron_or_block(doc, s, &pass_len, &nl_counter);
          s += pass_len + 1;
          if (*s == '{') {
            value1 = scss_trim(doc->pool, s_cut_before_block_closer(doc, ++s, &pass_len, &nl_counter));
            s += pass_len;
            if (*s == '}') s++;
            if (*value1) {
              s_get_property_list(doc, atnode, value1);
            }
          }
          else {
            scss_parser_error(doc->userData, __func__,__FILE__,__LINE__,(s - pass_len - 1), nl_counter ,"@font-face parse error");
            value1 = apr_pstrdup(doc->pool, "");
            value2 = apr_pstrdup(doc->pool, "");
          }
        }
      }
      else {
        value1 = scss_trim(doc->pool, s_cut_before_next_semicoron_or_block(doc, s, &pass_len, &nl_counter));
        s += pass_len + 1;
      }
      if (*name) {
        atnode->name = apr_pstrdup(doc->pool, name);
        atnode->value1 = apr_pstrdup(doc->pool, value1);
        atnode->value2 = apr_pstrdup(doc->pool, value2);
        s_add_child_node(doc, doc->rootNode, atnode);
      }
    }
    else if (! is_white_space(*s)) {
      PASS_COMMENT(s, &nl_counter); 
      char *one_selector = s_get_one_selector(doc, s, &pass_len, &nl_counter);
      if (*one_selector) {
        SCSSNodePtr_t selector_node = scss_create_node(doc->pool);
        selector_node->line = nl_counter;
        selector_node->type = SCSSTYPE_SELECTOR;
        selector_node->name = one_selector;
        s_add_child_node(doc, doc->rootNode, selector_node);
        s += pass_len;
        if (*s != ';') {
          if (*s == '{') s++;
          selector_node->value1 = scss_trim(doc->pool, s_cut_before_block_closer(doc, s, &pass_len, &nl_counter));
          s_get_property_list(doc, selector_node, selector_node->value1);
          s += pass_len + 1;
        }
        else {
          selector_node->value1 = apr_pstrdup(doc->pool, "");
        }
      }
    }
    if (! *s) break;
    s++;
  }
  return doc;
}


static char *
s_cut_ident(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter)
{
  const char *spos = s;
  char *ret;
  int npos;
  apr_size_t counter = 0;
  while (*s) {
    if (!is_white_space(*s)) break;
    if (*s == '\n') (*nl_counter)++;
    s++;
  }
  while (*s) {
    PASS_COMMENT(s, &counter);
    if (is_white_space(*s)) {
      break;
    }
    if (*s == ';' || *s == '{' || *s == '}') break;
    s++;
  }
  
  *pass_len = s - spos;
  *nl_counter += counter;

  ret = apr_palloc(doc->pool, *pass_len + 1);
  s = spos;
  npos = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    if (is_white_space(*s)) {
      break;
    }
    if (*s == ';' || *s == '{' || *s == '}') break;
    ret[npos++] = *s;
    s++;
  }
  ret[npos] = 0;
  return ret;
}


static const char *
s_pass_comment(const char *s, apr_size_t *nl_counter)
{
  apr_size_t counter = 0;
  while(*s) {
    if (*s == '*' && *(s+1) == '/') {
      ++s;
      return ++s;
    }
    if (*s == '\n') counter++;
    s++;
  }
  *nl_counter += counter;
  return s;
}

  

static char *
s_cut_before_next_semicoron_or_block(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter)
{
  const char *spos = s;
  char *ret;
  int npos;
  int sq, dq;
  apr_size_t counter = 0;

  sq = dq = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (!sq && !dq && (*s == '{' || *s == ';')) {
      break;
    }
    s++;
  }

  *nl_counter += counter;
  *pass_len = s - spos - 1;

  ret = apr_palloc(doc->pool, *pass_len + 1);
  s = spos; 

  npos = 0;
  sq = dq = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (!sq && !dq && (*s == '{' || *s == ';')) {
      break;
    }
    ret[npos++] = *s++;
  }
  ret[npos] = 0;
  return ret;
}

static char *
s_cut_before_block_closer(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter)
{
  const char *spos = s;
  char *ret;
  int npos;
  int nest = 0;
  int dq, sq;
  apr_size_t counter = 0;

  dq = sq = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (!sq && !dq && *s == '{') {
      nest++;
    }
    if (!sq && !dq && *s == '}') {
      if (! nest) {
        break;
      }
      nest--;
    }
    s++;
  }

  *nl_counter += counter;
  *pass_len = s - spos;

  ret = apr_palloc(doc->pool, *pass_len + 1);
  s = spos; 

  npos = 0;
  dq = sq = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (!sq && !dq && *s == '{') {
      nest++;
    }
    if (!sq && !dq && *s == '}') {
      if (! nest) {
        break;
      }
      nest--;
    }
    ret[npos++] = *s++;
  }
  ret[npos] = 0;
  return ret;
}


static char *
s_cut_before_white_space_or_semicoron(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter)
{
  const char *spos = s;
  char *ret;
  int npos;
  int sq, dq;
  apr_size_t counter = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    if (! is_white_space(*s)) {
      break;
    }
    s++;
  }
  dq = sq = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (!sq && !dq && is_white_space(*s)) {
      break;
    }
    if (!sq && !dq && *s == ';') {
      break;
    }
    s++;
  }

  *nl_counter += counter;
  *pass_len = s - spos - 1;

  ret = apr_palloc(doc->pool, *pass_len + 1);
  s = spos; 

  npos = 0;
  dq = sq = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    if (! is_white_space(*s)) {
      break;
    }
    s++;
  }
  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (!dq && !sq && is_white_space(*s)) {
      break;
    }
    if (!dq && !sq && *s == ';') {
      break;
    }
    ret[npos++] = *s++;
  }
  ret[npos] = 0;
  return ret;
}


static char *
s_cut_before_semicoron(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter)
{
  const char *spos = s;
  char *ret;
  int npos;
  int sq = 0;
  int dq = 0;
  apr_size_t counter = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    if (! is_white_space(*s)) {
      break;
    }
    s++;
  }

  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (*s == ';' && ! dq && ! sq) {
      break;
    }
    s++;
  }

  *nl_counter += counter;
  *pass_len = s - spos - 1;

  ret = apr_palloc(doc->pool, *pass_len + 1);
  s = spos; 

  npos = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    if (! is_white_space(*s)) {
      break;
    }
    s++;
  }
  sq = dq = 0;
  while (*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (! dq && ! sq && *s == ';') {
      break;
    }
    ret[npos++] = *s++;
  }
  ret[npos] = 0;
  return ret;
}

static void 
s_add_child_node(SCSSDocPtr_t doc, SCSSNodePtr_t nowNode, SCSSNodePtr_t node)
{
  if (nowNode->child != NULL) {
    list_insert(node, nowNode->child);
  }
  else {
    SCSSNodePtr_t sentinelNode = scss_create_node(doc->pool);
    sentinelNode->type = SCSSTYPE_SENTINEL;
    sentinelNode->name = apr_pstrdup(doc->pool, "<sentinel>");
    nowNode->child = sentinelNode;
    list_insert(node, sentinelNode);
  }
}


static char *
s_get_one_selector(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter)
{
  const char *spos = s;
  char *cand;
  char *ret;
  int npos;
  int dq = 0;
  int sq = 0;
  apr_size_t counter = 0;
  while(*s) {
    PASS_COMMENT(s, &counter);
    if (*s == '\\') {
      s += 2;
      continue;
    }
    if (! is_white_space(*s)) {
      break;
    }
    s++;
  }

  while(*s) {
    PASS_COMMENT(s, &counter);
    JUDGE_STRINGS(s);
    if (! sq && !dq && (*s == '{' || *s == ';')) {
      break;
    }
    s++;
  }
  *nl_counter = counter + *nl_counter;
  *pass_len = s - spos;

  cand = apr_palloc(doc->pool, *pass_len + 1);
  memcpy(cand, spos, *pass_len);
  cand[*pass_len] = 0;
  cand = scss_trim(doc->pool, cand);
  ret = apr_palloc(doc->pool, *pass_len + 1);
  spos = cand;
  npos = 0;
  while(*cand) {
    while(*cand) {
      if (*cand == ' ' || *cand == '+' || *cand == '>' || *cand == ',') {
        break;
      }
      ret[npos++] = *cand++;
    }
    int sib = 0; /* + */
    int cld = 0; /* > */
    int cnm = 0; /* , */
    while(*cand) {
      if (*cand != ' ' && *cand != '+' && *cand != '>' && *cand != ',') {
        break;
      }
      if (!cnm && !cld && *cand == '+') {
        sib++;
      }
      if (!cnm && !sib && *cand == '>') {
        cld++;
      }
      if (!cld && !sib && *cand == ',') {
        cnm++;
      }
      cand++;
    }
    if (*cand) {
      if (sib) {
        ret[npos++] = '+';
      }
      else if (cld) {
        ret[npos++] = '>';
      }
      else if (cnm) {
        ret[npos++] = ',';
      }
      else {
        ret[npos++] = ' ';
      }
    }
  }
  ret[npos] = 0;
  
  return ret;
}


static void
s_get_property_list(SCSSDocPtr_t doc, SCSSNodePtr_t nowNode, const char *s)
{
  char *block = (char *)s;
  char *pstat;
  block = s_replace_refstring(doc, block);
  while(1) {
    char *pstat2;
    char *key, *val;
    char *valtmp;
    char *imp;
    char *pair = apr_strtok(block, ";", &pstat);
    if (!pair) {
      break;
    }
    key = apr_pstrdup(doc->pool, pair);
    val = strchr(key, ':');
    if (val) {
      *val = 0;
      val++;
    }
    key = scss_trim(doc->pool, key);
    val = scss_trim(doc->pool, val);

    valtmp = val;
    val = apr_strtok(valtmp, "!", &pstat2);
    imp = apr_strtok(NULL, "!", &pstat2);
    
    SCSSNodePtr_t node = scss_create_node(doc->pool);
    node->name   = key;
    node->value1 = (val) ? scss_strip_quote(doc->pool, apr_pstrdup(doc->pool, val)) : apr_pstrdup(doc->pool, "");
    node->value2 = (imp) ? apr_pstrcat(doc->pool, "!", imp, NULL) : NULL;
    node->type   = SCSSTYPE_PROPERTY;
    s_add_child_node(doc, nowNode, node);
    block = NULL;
  }
}


static char *
s_replace_refstring(SCSSDocPtr_t doc, const char *s)
{
  char *ss;
  char *ret;
  int npos;
  apr_pool_t *pool = doc->pool;

  ss = (char *)scss_trim(doc->pool, s);
  if (! ss) return apr_pstrdup(pool, "");
  if (! *ss) return apr_pstrdup(pool, "");

  ret = apr_palloc(pool, strlen(ss) + 1);
  memset(ret, 0, strlen(ss) + 1);
  npos = 0;
  while(*ss) {
    if (*ss == '&') {
      if (strncasecmp(ss, "&quot;", sizeof("&quot;")-1) == 0) {
        ret[npos++] = '"';
        ss += sizeof("&quot;")-1;
        
      }
      else if (strncasecmp(ss, "&amp;", sizeof("&amp;")-1) == 0) {
        ret[npos++] = '&';
        ss += sizeof("&amp;")-1;
      }
      else if (strncasecmp(ss, "&lt;", sizeof("&lt;")-1) == 0) {
        ret[npos++] = '<';
        ss += sizeof("&lt;")-1;
      }
      else if (strncasecmp(ss, "&gt;", sizeof("&gt;")-1) == 0) {
        ret[npos++] = '>';
        ss += sizeof("&gt;")-1;
      }
      else {
        ret[npos++] = *ss;
        ss++;
      }
    }
    else {
      ret[npos++] = *ss;
      ss++;
    }
  }
  ret[npos] = 0;
  return ret;
}


static char *
s_cut_url_function(SCSSDocPtr_t doc, const char *s, apr_size_t *pass_len, apr_size_t *nl_counter)
{
  const char *spos = s;
  int pcnt = 0;
  apr_size_t counter = 0;

  counter = *nl_counter;
  while(*s) {
    PASS_COMMENT(s, &counter);
    if (*s == '\\') {
      s += 2;
      continue;
    }
    if (! is_white_space(*s)) {
      break;
    }
    if (*s == '\n') counter++;
    s++;
  }

  while(*s) {
    PASS_COMMENT(s, &counter);
    if (*s == '\\') {
      s += 2;
      continue;
    }
    if (pcnt && *s == ')') {
      pcnt--;
      if (! pcnt) {
        s++;
        break;
      }
    }
    if (*s == '(') {
      pcnt++;
    }
    if (*s == '\n') counter++;
    s++;
  }

  *pass_len = s - spos;
  *nl_counter = counter;

  char *ret = apr_palloc(doc->pool, *pass_len + 1);
  memcpy(ret, spos, *pass_len);
  ret[*pass_len] = 0;
  return ret;
}


static void
s_default_error_log(void *userData, const char *func, const char *fname, int line, const char *src, int srcline, char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "func:[%s] file:[%s] line:[%d] src:[%.*s] srcline:[%d]", func, fname, line, 10, src, srcline);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fprintf(stderr, "\n");
}

void 
scss_doc_set_user_data(SCSSDocPtr_t doc, void *userData)
{
  doc->userData = userData;
}

void *
scss_doc_get_user_data(SCSSDocPtr_t doc)
{
  return doc->userData;
}
