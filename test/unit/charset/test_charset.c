#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "scss.h"


#define CU_ASSERT_OR_GOTO_END(X) { CU_ASSERT((X)); if (CU_get_number_of_failures() != 0) goto end; }
#define CU_ASSERT_STRING_EQUAL_GOTO_END(X, Y) do { CU_ASSERT_STRING_EQUAL((X),(Y)); if (CU_get_number_of_failures() != 0) goto end; } while (0)


void test_charset_001();
void test_charset_002();
void test_charset_003();
void test_charset_004();
void test_charset_005();
void test_charset_006();
void test_charset_007();
void test_charset_008();
void test_charset_009();
void test_charset_010();
void test_charset_011();
/* pend */

int
main()
{
  CU_pSuite atkeyword_suite;
  CU_initialize_registry();
  atkeyword_suite = CU_add_suite("test Simple CSS(is based CSS2 but not CSS2)  Parser", NULL, NULL);
  CU_add_test(atkeyword_suite, "@charset 001",  test_charset_001);
  CU_add_test(atkeyword_suite, "@charset 002",  test_charset_002);
  CU_add_test(atkeyword_suite, "@charset 003",  test_charset_003);
  CU_add_test(atkeyword_suite, "@charset 004",  test_charset_004);
  CU_add_test(atkeyword_suite, "@charset 005",  test_charset_005);
  CU_add_test(atkeyword_suite, "@charset 006",  test_charset_006);
  CU_add_test(atkeyword_suite, "@charset 007",  test_charset_007);
  CU_add_test(atkeyword_suite, "@charset 008",  test_charset_008);
  CU_add_test(atkeyword_suite, "@charset 009",  test_charset_009);
  CU_add_test(atkeyword_suite, "@charset 010",  test_charset_010);
  CU_add_test(atkeyword_suite, "@charset 011",  test_charset_011);
  /* aend */

  CU_basic_run_tests();
  CU_cleanup_registry();

  return(0);
}


void test_charset_001()
{
#define TEST_STRING "@charset"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_002()
{
#define TEST_STRING "@charset \"UTF-8\""
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_003()
{
#define TEST_STRING "@charset \"UTF-8\";"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_004()
{
#define TEST_STRING "@charset\n \"UTF-8\";"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_005()
{
#define TEST_STRING "\n\n@charset\n \"UTF-8\";"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_006()
{
#define TEST_STRING "\n\n@c/*abc*/harset\n \"UTF-8\";"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_007()
{
#define TEST_STRING "\n\n@c/*abc*/harset\n \"UTF-8"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_008()
{
#define TEST_STRING "@charset \"CP932\";br { \x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8:none }"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "CP932") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->name, "br") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->value1, "あいうえお:none") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->ref == &doc->rootNode->child->next->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->child->next->name, "あいうえお") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->child->next->value1, "none") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_009()
{
#define TEST_STRING "@charset \"UTF-8\";br { \x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8:none }"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->name, "br") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->value1, "\x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8\x3a\x6e\x6f\x6e\x65") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->ref == &doc->rootNode->child->next->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->child->next->name, "\x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->child->next->value1, "none") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_010()
{
#define TEST_STRING "@charset \"UTF-8\";\nbr { \x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8:none }"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "UTF-8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->name, "br") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->value1, "\x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8\x3a\x6e\x6f\x6e\x65") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->ref == &doc->rootNode->child->next->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->child->next->name, "\x82\xa0\x82\xa2\x82\xa4\x82\xa6\x82\xa8") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->child->next->value1, "none") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_charset_011()
{
#define TEST_STRING "@charset;@charset \"UTF-8\";"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT_OR_GOTO_END(doc != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->name, "@charset") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->value1, "UTF-8") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->ref == &doc->rootNode->child->next->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
/*
 * vim:ts=2 et
 */
