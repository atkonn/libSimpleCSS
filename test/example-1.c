
#include "scss.h"
#include "apr.h"
#include "apr_pools.h"
#include "apr_mmap.h"

#include <stdio.h>

static void s_import(SCSSParserPtr_t parser, const char *uri, const char **media, const char *defaultNamespaceURI);

static void s_start_document(SCSSParserPtr_t parser);
static void s_end_document(SCSSParserPtr_t parser);
static void s_start_media(SCSSParserPtr_t parser, const char **media);
static void s_end_media(SCSSParserPtr_t parser, const char **media);
static void s_start_page(SCSSParserPtr_t parser, const char *name, const char *pseudoPage);
static void s_end_page(SCSSParserPtr_t parser, const char *name, const char *pseudoPage);
static void s_start_font_face(SCSSParserPtr_t parser);
static void s_end_font_face(SCSSParserPtr_t parser);
static void s_start_selector(SCSSParserPtr_t parser, SCSSNodePtr_t selectors);
static void s_end_selector(SCSSParserPtr_t parser, SCSSNodePtr_t selectors);
static void s_property(SCSSParserPtr_t parser, const char *propertyName, const char *value, int important);
static void print_usage(const char * const argv[]);
static void s_close_file(apr_mmap_t *mm);
static apr_mmap_t *s_open_file(apr_pool_t *pool, const char *filename);

static int level = 0;
int
main(int argc, const char * const argv[])
{
  apr_pool_t *pool;
  SCSSParserPtr_t parser;
  SCSSSACHandlerPtr_t handler;
  apr_mmap_t *mm;
  char *s;
  
  /*===================*/
  /* 1) APR initialize */
  /*===================*/
  apr_initialize();
  apr_pool_create(&pool, NULL);
  if (argc != 2) {
    print_usage(argv);
    return -1;
  }

  mm = s_open_file(pool, argv[1]);
  if (mm == NULL) {
    fprintf(stderr, "failed: open %s\n", argv[1]);
    return -2;
  }
  s = (char *)mm->mm;

  /*=========================*/
  /* 2) create parser object */
  /*=========================*/
  parser = scss_parser_new_from_buf(pool, s, "");

  /*==========================*/
  /* 3) create handler object */
  /*==========================*/
  handler = scss_doc_handler_new(parser);

  /*==========================*/
  /* 4) register handler      */
  /*==========================*/
  handler->startDocument = s_start_document;
  handler->endDocument   = s_end_document;
  handler->import        = s_import;
  handler->startMedia    = s_start_media;
  handler->endMedia      = s_end_media;
  handler->startPage     = s_start_page;
  handler->endPage       = s_end_page;
  handler->startFontFace = s_start_font_face;
  handler->endFontFace   = s_end_font_face;
  handler->startSelector = s_start_selector;
  handler->endSelector   = s_end_selector;
  handler->property      = s_property;

  /*==========================*/
  /* 5) do parse.             */
  /*==========================*/
  scss_parse_stylesheet(parser);

  /*==========================*/
  /* 6) APR terminate         */
  /*==========================*/
  s_close_file(mm);
  apr_pool_destroy(pool);
  apr_terminate();
  return 0;
}

static void print_level()
{
  int ii;
  for (ii=0; ii<level;ii++) fprintf(stderr, "+");
}

static void 
s_import(SCSSParserPtr_t parser, const char *uri, const char **media, const char *defaultNamespaceURI) 
{
  int ii;
  print_level(); fprintf(stderr, "IMPORT\n");
  print_level(); fprintf(stderr, "\turi:[%s]\n", uri);
  for (ii=0; ii < SCSS_MEDIA_TYPE_NUM; ii++) {
    if (media[ii]) {
      print_level(); fprintf(stderr, "\tmedia:[%s]\n", media[ii]);
    }
  }
}


static void
s_start_document(SCSSParserPtr_t parser)
{
  fprintf(stderr, "START DOCUMENT\n");
  level++;
}


static void
s_end_document(SCSSParserPtr_t parser)
{
  level--;
  fprintf(stderr, "END DOCUMENT\n");
}



static void
s_start_media(SCSSParserPtr_t parser, const char **media)
{
  int ii;
  print_level(); fprintf(stderr, "START MEDIA\n");
  for (ii=0; ii < SCSS_MEDIA_TYPE_NUM; ii++) {
    if (media[ii]) {
      print_level(); fprintf(stderr, "\tmedia:[%s]\n", media[ii]);
    }
  }
  level++;
}

static void
s_end_media(SCSSParserPtr_t parser, const char **media)
{
  int ii;
  level--;
  print_level(); fprintf(stderr, "END MEDIA\n");
  for (ii=0; ii < SCSS_MEDIA_TYPE_NUM; ii++) {
    if (media[ii]) {
      print_level(); fprintf(stderr, "\tmedia:[%s]\n", media[ii]);
    }
  }
}



static void
s_start_page(SCSSParserPtr_t parser, const char *name, const char *pseudoPage)
{
  print_level(); fprintf(stderr, "START PAGE\n");
  print_level(); fprintf(stderr, "\tname:[%s]\n", name);
  print_level(); fprintf(stderr, "\tpseudo:[%s]\n", pseudoPage);
  level++;
}

static void
s_end_page(SCSSParserPtr_t parser, const char *name, const char *pseudoPage)
{
  level--;
  print_level(); fprintf(stderr, "END PAGE\n");
  print_level(); fprintf(stderr, "\tname:[%s]\n", name);
  print_level(); fprintf(stderr, "\tpseudo:[%s]\n", pseudoPage);
}

static void
s_start_font_face(SCSSParserPtr_t parser)
{
  print_level(); fprintf(stderr, "START FONT-PAGE\n");
  ++level;
}
static void
s_end_font_face(SCSSParserPtr_t parser)
{
  --level;
  print_level(); fprintf(stderr, "START FONT-PAGE\n");
}

static void
s_start_selector(SCSSParserPtr_t parser, SCSSNodePtr_t selectors)
{
  SCSSNodePtr_t curNode;
  print_level(); fprintf(stderr, "START SELECTOR\n");
  for (curNode = selectors->next; curNode != selectors; curNode = curNode->next) {
    print_level(); fprintf(stderr, "\tname:[%s]\n", curNode->name);
  }
  level++; 
}
static void
s_end_selector(SCSSParserPtr_t parser, SCSSNodePtr_t selectors)
{
  SCSSNodePtr_t curNode;
  level--;
  print_level(); fprintf(stderr, "END SELECTOR\n");
  for (curNode = selectors->next; curNode != selectors; curNode = curNode->next) {
    print_level(); fprintf(stderr, "\tname:[%s]\n", curNode->name);
  }
}

static void
s_property(SCSSParserPtr_t parser, const char *propertyName, const char *value, int important)
{
  print_level(); fprintf(stderr, "PROPERTY\n");
  print_level(); fprintf(stderr, "\tname:[%s]\n", propertyName);
  print_level(); fprintf(stderr, "\tvalue:[%s]\n", value);
  print_level(); fprintf(stderr, "\timportant:[%d]\n", important);
}

static void
print_usage(const char * const argv[])
{
  fprintf(stderr, "Usage: %s filename\n", argv[0]);
}

static apr_mmap_t *
s_open_file(apr_pool_t *pool, const char *filename)
{
  apr_mmap_t *mm;
  apr_status_t rv;
  apr_file_t *fp;
  apr_finfo_t finfo;
  rv = apr_stat(&finfo, filename, APR_FINFO_SIZE, pool);
  if (rv != APR_SUCCESS) {
    return NULL;
  }
  if (finfo.size == 0) {
    return NULL;
  }
  rv = apr_file_open(&fp, filename, APR_READ | APR_BINARY, 0, pool);
  if (rv != APR_SUCCESS) {
    return NULL;
  }
  rv = apr_mmap_create(&mm, fp, 0, finfo.size, APR_MMAP_READ, pool);
  apr_file_close(fp);
  if (rv != APR_SUCCESS) {
    apr_file_close(fp);
    return NULL;
  }

  return mm;
}

static void
s_close_file(apr_mmap_t *mm)
{
  apr_mmap_delete(mm);
}
