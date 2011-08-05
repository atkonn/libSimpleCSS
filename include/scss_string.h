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
#if !defined(__SCSS_STRING_H__)
#define __SCSS_STRING_H__

#include "apr_pools.h"

/**
 * Count white-space.
 * @param str       strings.
 * @param len       max length
 * @return count of white-space.
 */
extern int scss_count_space(const char *str, int len);

/**
 * check start with.
 * @param s check string.
 * @param w starts word.
 */
extern int scss_starts_with(const char *s, const char *w);

/**
 * ignore spaces.
 */
extern int scss_ignore_space(const char *s, int len, apr_size_t *nl_counter);

/**
 * trim string.
 *
 * @param pool - use pool object.
 * @param s    - target string.
 * @return trimed string.
 */
extern char *scss_trim(apr_pool_t *pool, const char *s);

/**
 * strip quote.
 *
 * @param pool - use pool object.
 * @param s    - target string.
 * @return stripped string.
 */
extern char *scss_strip_quote(apr_pool_t *pool, const char *s);




#if !defined is_white_space
#define is_white_space(c)   (' '  == (unsigned char)(c&0xff)  \
                          || '\t' == (unsigned char)(c&0xff)  \
                          || '\n' == (unsigned char)(c&0xff)  \
                          || '\f' == (unsigned char)(c&0xff)  \
                          || '\r' == (unsigned char)(c&0xff))
#endif
#endif
