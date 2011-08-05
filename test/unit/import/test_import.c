#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "scss.h"


#define CU_ASSERT_OR_GOTO_END(X) { CU_ASSERT((X)); if (CU_get_number_of_failures() != 0) goto end; }


void test_import_001();
void test_import_002();
void test_import_003();
void test_import_004();
void test_import_005();
void test_import_006();
void test_import_007();
void test_import_008();
void test_import_009();
void test_import_010();
/* pend */

int
main()
{
  CU_pSuite atkeyword_suite;
  CU_initialize_registry();
  atkeyword_suite = CU_add_suite("test Simple CSS(is based CSS2 but not CSS2)  Parser", NULL, NULL);
  CU_add_test(atkeyword_suite, "@import 001",  test_import_001);
  CU_add_test(atkeyword_suite, "@import 002",  test_import_002);
  CU_add_test(atkeyword_suite, "@import 003",  test_import_003);
  CU_add_test(atkeyword_suite, "@import 004",  test_import_004);
  CU_add_test(atkeyword_suite, "@import 005",  test_import_005);
  CU_add_test(atkeyword_suite, "@import 006",  test_import_006);
  CU_add_test(atkeyword_suite, "@import 007",  test_import_007);
  CU_add_test(atkeyword_suite, "@import 008",  test_import_008);
  CU_add_test(atkeyword_suite, "@import 009",  test_import_009);
  CU_add_test(atkeyword_suite, "@import 010",  test_import_010);
  /* aend */

  CU_basic_run_tests();
  CU_cleanup_registry();

  return(0);
}


void test_import_001()
{
#define TEST_STRING "@import"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT(doc != NULL);
  CU_ASSERT(doc->rootNode != NULL);
  CU_ASSERT(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT(doc->rootNode->child != NULL);
  CU_ASSERT(doc->rootNode->child->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT(doc->rootNode->child->next != NULL);
  CU_ASSERT(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT(doc->rootNode->child->next->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);
  CU_ASSERT(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT(doc->rootNode->child->next->child == NULL);


  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_002()
{
#define TEST_STRING "@import@import"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT(doc != NULL);
  CU_ASSERT(doc->rootNode != NULL);
  CU_ASSERT(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT(doc->rootNode->child != NULL);
  CU_ASSERT(doc->rootNode->child->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT(doc->rootNode->child->next != NULL);
  CU_ASSERT(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT(doc->rootNode->child->next->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->name, "@import@import") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT(doc->rootNode->child->next->child == NULL);


  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_003()
{
#define TEST_STRING "@import;@import"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT(doc != NULL);
  CU_ASSERT(doc->rootNode != NULL);
  CU_ASSERT(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT(doc->rootNode->child != NULL);
  CU_ASSERT(doc->rootNode->child->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT(doc->rootNode->child->next != NULL);
  CU_ASSERT(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT(doc->rootNode->child->next->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);
  CU_ASSERT(doc->rootNode->child->next->next != NULL);
  CU_ASSERT(doc->rootNode->child->next->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->next->name, "@import") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->next->value1, "") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->next->value2, "all") == 0);


  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_004()
{
#define TEST_STRING "@import\n;@import"
  SCSSDocPtr_t doc;
  apr_pool_t *pool;

  fprintf(stderr, "start %s\n", __func__);
  apr_initialize();
  apr_pool_create(&pool, NULL);

  doc = scss_create_doc(pool);
  scss_parser(doc, pool,  TEST_STRING);

  CU_ASSERT(doc != NULL);
  CU_ASSERT(doc->rootNode != NULL);
  CU_ASSERT(doc->rootNode->type == SCSSTYPE_STYLESHEET);
  CU_ASSERT(doc->rootNode->child != NULL);
  CU_ASSERT(doc->rootNode->child->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->name, "<sentinel>") == 0);
  CU_ASSERT(doc->rootNode->child->next != NULL);
  CU_ASSERT(doc->rootNode->child->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT(doc->rootNode->child->next->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);
  CU_ASSERT(doc->rootNode->child->next->next != NULL);
  CU_ASSERT(doc->rootNode->child->next->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->next->name, "@import") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->next->value1, "") == 0);
  CU_ASSERT(strcasecmp(doc->rootNode->child->next->next->value2, "all") == 0);


  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_005()
{
#define TEST_STRING "\n\n@import\n/*abc*/abc /*abc*/all;\n@import"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->type == SCSSTYPE_ATKEYWORD);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->name, "@import") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->value2, "all") == 0);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_006()
{
#define TEST_STRING "@import url(\"http://www.google.co.jp/{}\");"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "url(\"http://www.google.co.jp/{}\")") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_007()
{
#define TEST_STRING "@import url(\"http://www.google.co.jp/{}\") handheld, print;"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "url(\"http://www.google.co.jp/{}\")") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld, print") == 0);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_008()
{
#define TEST_STRING "@import url( \"http://www.google.co.jp/{}\") handheld, print;"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "url( \"http://www.google.co.jp/{}\")") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld, print") == 0);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_009()
{
#define TEST_STRING "@import url( \"http://www.google.co.jp/{}\" ) handheld, print;"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "url( \"http://www.google.co.jp/{}\" )") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld, print") == 0);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_import_010()
{
#define TEST_STRING "@import url( \"http://www"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@import") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "url( \"http://www") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
/*
 * vim:ts=2 et
 */
