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
#include "scss_iconv.h"
#include "apr_strings.h"
#include <errno.h>
#include <iconv.h>

char *
scss_iconv(apr_pool_t *pool, const char *src, apr_size_t *len, const char *from, const char *to, apr_status_t *rv, char **err_msg)
{
  char                *obuf;
  char                *ibuf;
  char                *spos;
  
  iconv_t             cd;
  size_t              result;
  apr_size_t          ilen;
  apr_size_t          olen;


  if ((int)*len < 0) {
    *err_msg = apr_psprintf(pool, "%s:%d runtime exception: scss_iconv(): invalid string size.[%d]", __FILE__,__LINE__, (int)*len);
    *rv = -1;
    return (char *)apr_pstrdup(pool, "");
  }

  ilen = *len;
  ibuf = apr_palloc(pool, ilen+1);
  if (ibuf == NULL) {
    *err_msg = apr_psprintf(pool, "%s:%d runtime exception: scss_iconv(): Out of memory.", __FILE__,__LINE__);
    *rv = -2;
    return (char *)src;
  }
  memset(ibuf, 0, ilen+1);
  memcpy(ibuf, src, ilen);

  olen = ilen * 4 + 1;
  spos = obuf = apr_palloc(pool, olen);
  if (obuf == NULL) {
    *err_msg = apr_psprintf(pool, "%s:%d runtime exception: scss_iconv(): Out of memory", __FILE__,__LINE__);
    *rv = -3;
    return ibuf;
  }
  memset(obuf, 0, olen);
  cd = iconv_open(to, from);
  if (cd == (iconv_t)-1) {
    if (EINVAL == errno) {
      *err_msg = apr_psprintf(pool, "%s:%d The conversion from %s to %s is not supported by the implementation.", __FILE__,__LINE__, from, to);
      *rv = -4;
    }
    else {
      *err_msg = apr_psprintf(pool, "%s:%d iconv open failed. from:[%s] to:[%s] errno:[%d]", __FILE__,__LINE__, from, to, errno);
      *rv = -5;
    }
    return ibuf;
  }

  while (ilen > 0) {
    result = iconv(cd, &ibuf, &ilen, &obuf, &olen);
    if (result == (size_t)(-1)) {
      if (E2BIG == errno) {
        *err_msg = apr_psprintf(pool, "%s:%d There is not sufficient room at *outbuf.", __FILE__,__LINE__);
        *rv = -6;
      }
      else if (EILSEQ == errno) {
        *err_msg = apr_psprintf(pool, "%s:%d An invalid multibyte sequence has been encountered in the input. input:[%s]", __FILE__,__LINE__,ibuf);
        *rv = -7;
      }
      else if (EINVAL == errno) {
        *err_msg = apr_psprintf(pool, "%s:%d An invalid multibyte sequence has been encountered in the input. input:[%s]", __FILE__,__LINE__,ibuf);
        *rv = -8;
      }
      break;
    }
  }
  *len = strlen(spos);
  iconv_close(cd);

  *rv = 0;
  return spos;
}
/*
 * vim:ts=2 et
 */
