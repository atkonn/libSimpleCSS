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
#if !defined(__SCSS_SAC_H__)
#define __SCSS_SAC_H__

typedef struct _SCSSParser_t SCSSParser_t;
typedef struct _SCSSParser_t *SCSSParserPtr_t;
typedef struct _SCSSSACHandler_t SCSSSACHandler_t;
typedef struct _SCSSSACHandler_t *SCSSSACHandlerPtr_t;

struct _SCSSParser_t {
  SCSSDocPtr_t        doc;
  SCSSSACHandlerPtr_t handler;
};


#define SCSS_MEDIA_TYPE_NUM   (10)

typedef void (*SCSSSAC_import_fn)(SCSSParserPtr_t parser, 
                 const char *uri,
                 const char **media,
                 const char *defaultNamespaceURI);

typedef void (*SCSSSAC_startDocument_fn)(SCSSParserPtr_t parser);
typedef void (*SCSSSAC_endDocument_fn)(SCSSParserPtr_t parser);
typedef void (*SCSSSAC_startMedia_fn)(SCSSParserPtr_t parser, const char **media);
typedef void (*SCSSSAC_endMedia_fn)(SCSSParserPtr_t parser, const char **media);
typedef void (*SCSSSAC_startPage_fn)(SCSSParserPtr_t parser, const char *name, const char *pseudoPage);
typedef void (*SCSSSAC_endPage_fn)(SCSSParserPtr_t parser, const char *name, const char *pseudoPage);
typedef void (*SCSSSAC_startFontFace_fn)(SCSSParserPtr_t parser);
typedef void (*SCSSSAC_endFontFace_fn)(SCSSParserPtr_t parser);
typedef void (*SCSSSAC_startSelector_fn)(SCSSParserPtr_t parser, SCSSNodePtr_t selectors);
typedef void (*SCSSSAC_endSelector_fn)(SCSSParserPtr_t parser, SCSSNodePtr_t selectors);
typedef void (*SCSSSAC_property_fn)(SCSSParserPtr_t parser, const char *propertyName, const char *value, int impotant);

/**
 * SAC Handlers.
 */
struct _SCSSSACHandler_t {
  SCSSSAC_startDocument_fn startDocument;
  SCSSSAC_endDocument_fn   endDocument;
  SCSSSAC_import_fn        import;
  SCSSSAC_startMedia_fn    startMedia;
  SCSSSAC_endMedia_fn      endMedia;
  SCSSSAC_startPage_fn     startPage;
  SCSSSAC_endPage_fn       endPage;
  SCSSSAC_startFontFace_fn startFontFace;
  SCSSSAC_endFontFace_fn   endFontFace;
  SCSSSAC_startSelector_fn startSelector;
  SCSSSAC_endSelector_fn   endSelector;
  SCSSSAC_property_fn      property;
};


/**
 * create SAC Parser from buffer.
 *
 * @param pool - parent pool.
 * @param buf - buffer (CSS data).
 * @param defaultEncoding - encoding(see iconv)
 */
extern SCSSParserPtr_t scss_parser_new_from_buf(apr_pool_t *pool, const char *buf, char *defaultEncoding);

/**
 * create new SAC Handler.
 */
extern SCSSSACHandlerPtr_t scss_doc_handler_new(SCSSParserPtr_t parser);

extern const char *scss_get_perser_version(SCSSParserPtr_t parser);

/**
 * do parse.
 */
extern int scss_parse_stylesheet(SCSSParserPtr_t parser);


/**
 * get user's data.
 *
 * @param parser - SCSSParser_t Object.
 * @return user's data if any.
 */
extern void *scss_get_user_data(SCSSParserPtr_t parser);


/**
 * set user's data.
 *
 * @param parser - SCSSParser_t Object.
 * @param userData - user's data.
 */
extern void scss_set_user_data(SCSSParserPtr_t parser, void *userData);
#endif
