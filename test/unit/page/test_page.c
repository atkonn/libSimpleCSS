#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "scss.h"


#define CU_ASSERT_OR_GOTO_END(X) { CU_ASSERT((X)); if (CU_get_number_of_failures() != 0) goto end; }
#define CU_ASSERT_STRING_EQUAL_GOTO_END(X, Y) do { CU_ASSERT_STRING_EQUAL((X),(Y)); if (CU_get_number_of_failures() != 0) goto end; } while (0)


void test_page_001();
void test_page_002();
void test_page_003();
void test_page_004();
void test_page_005();
void test_page_006();

void test_page_101();
void test_page_102();
void test_page_103();
void test_page_104();
void test_page_105();
void test_page_106();

void test_page_201();
void test_page_202();
void test_page_203();
void test_page_204();
void test_page_205();
void test_page_206();

void test_page_301();
void test_page_302();
void test_page_303();
void test_page_304();
void test_page_305();
void test_page_306();
/* pend */

int
main()
{
  CU_pSuite atkeyword_suite;
  CU_initialize_registry();
  atkeyword_suite = CU_add_suite("test Simple CSS(is based CSS2 but not CSS2)  Parser", NULL, NULL);
  CU_add_test(atkeyword_suite, "@page 001",  test_page_001);
  CU_add_test(atkeyword_suite, "@page 002",  test_page_002);
  CU_add_test(atkeyword_suite, "@page 003",  test_page_003);
  CU_add_test(atkeyword_suite, "@page 004",  test_page_004);
  CU_add_test(atkeyword_suite, "@page 005",  test_page_005);
  CU_add_test(atkeyword_suite, "@page 006",  test_page_006);

  CU_add_test(atkeyword_suite, "@page 101",  test_page_101);
  CU_add_test(atkeyword_suite, "@page 102",  test_page_102);
  CU_add_test(atkeyword_suite, "@page 103",  test_page_103);
  CU_add_test(atkeyword_suite, "@page 104",  test_page_104);
  CU_add_test(atkeyword_suite, "@page 105",  test_page_105);
  CU_add_test(atkeyword_suite, "@page 106",  test_page_106);

  CU_add_test(atkeyword_suite, "@page 201",  test_page_201);
  CU_add_test(atkeyword_suite, "@page 202",  test_page_202);
  CU_add_test(atkeyword_suite, "@page 203",  test_page_203);
  CU_add_test(atkeyword_suite, "@page 204",  test_page_204);
  CU_add_test(atkeyword_suite, "@page 205",  test_page_205);
  CU_add_test(atkeyword_suite, "@page 206",  test_page_206);

  CU_add_test(atkeyword_suite, "@page 301",  test_page_301);
  CU_add_test(atkeyword_suite, "@page 302",  test_page_302);
  CU_add_test(atkeyword_suite, "@page 303",  test_page_303);
  CU_add_test(atkeyword_suite, "@page 304",  test_page_304);
  CU_add_test(atkeyword_suite, "@page 305",  test_page_305);
  CU_add_test(atkeyword_suite, "@page 306",  test_page_306);
  /* aend */

  CU_basic_run_tests();
  CU_cleanup_registry();

  return(0);
}


void test_page_001()
{
#define TEST_STRING "@page"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page") == 0);
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
void test_page_002()
{
#define TEST_STRING "@page { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_003()
{
#define TEST_STRING "@page aaa { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_004()
{
#define TEST_STRING "@page aaa abc { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_005()
{
#define TEST_STRING "@page aaa abc { size: 10px; "
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_006()
{
#define TEST_STRING "@page aaa"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page") == 0);
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


/* page:first */
void test_page_101()
{
#define TEST_STRING "@page:first"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:first") == 0);
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
void test_page_102()
{
#define TEST_STRING "@page:first { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:first") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_103()
{
#define TEST_STRING "@page:first aaa { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:first") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_104()
{
#define TEST_STRING "@page:first aaa abc { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:first") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_105()
{
#define TEST_STRING "@page:first aaa abc { size: 10px; "
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:first") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_106()
{
#define TEST_STRING "@page:first aaa"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:first") == 0);
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



/* page:right */
void test_page_201()
{
#define TEST_STRING "@page:right"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:right") == 0);
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
void test_page_202()
{
#define TEST_STRING "@page:right { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:right") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_203()
{
#define TEST_STRING "@page:right aaa { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:right") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_204()
{
#define TEST_STRING "@page:right aaa abc { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:right") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_205()
{
#define TEST_STRING "@page:right aaa abc { size: 10px; "
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:right") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_206()
{
#define TEST_STRING "@page:right aaa"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:right") == 0);
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



/* page:left */
void test_page_301()
{
#define TEST_STRING "@page:left"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:left") == 0);
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
void test_page_302()
{
#define TEST_STRING "@page:left { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:left") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_303()
{
#define TEST_STRING "@page:left aaa { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:left") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_304()
{
#define TEST_STRING "@page:left aaa abc { size: 10px; }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:left") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_305()
{
#define TEST_STRING "@page:left aaa abc { size: 10px; "
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:left") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa abc") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "size: 10px;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_page_306()
{
#define TEST_STRING "@page:left aaa"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@page:left") == 0);
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
/*
 * vim:ts=2 et
 */
