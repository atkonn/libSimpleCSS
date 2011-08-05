#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "scss.h"


#define CU_ASSERT_OR_GOTO_END(X) { CU_ASSERT((X)); if (CU_get_number_of_failures() != 0) goto end; }
#define CU_ASSERT_STRING_EQUAL_OR_GOTO_END(X, Y) do { CU_ASSERT_STRING_EQUAL((X),(Y)); if (CU_get_number_of_failures() != 0) goto end; } while (0)


void test_selector_001();
void test_selector_002();
void test_selector_003();
void test_selector_004();
void test_selector_005();
void test_selector_006();
void test_selector_007();
void test_selector_008();
/* pend */

int
main()
{
  CU_pSuite atkeyword_suite;
  CU_initialize_registry();
  atkeyword_suite = CU_add_suite("test Simple CSS(is based CSS2 but not CSS2)  Parser", NULL, NULL);
  CU_add_test(atkeyword_suite, "selector 001",  test_selector_001);
  CU_add_test(atkeyword_suite, "selector 002",  test_selector_002);
  CU_add_test(atkeyword_suite, "selector 003",  test_selector_003);
  CU_add_test(atkeyword_suite, "selector 004",  test_selector_004);
  CU_add_test(atkeyword_suite, "selector 005",  test_selector_005);
  CU_add_test(atkeyword_suite, "selector 006",  test_selector_006);
  CU_add_test(atkeyword_suite, "selector 007",  test_selector_007);
  CU_add_test(atkeyword_suite, "selector 008",  test_selector_008);
  /* aend */

  CU_basic_run_tests();
  CU_cleanup_registry();

  return(0);
}


void test_selector_001()
{
#define TEST_STRING "a1 { aaa:bbb; }"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "a1") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa:bbb;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->name != NULL);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->name, "<sentinel>");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->name, "aaa");
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->value1, "bbb");


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_selector_002()
{
#define TEST_STRING "a1\n{ aaa:bbb; }"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "a1") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa:bbb;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->name != NULL);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->name, "<sentinel>");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->name, "aaa");
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->value1, "bbb");


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_selector_003()
{
#define TEST_STRING "\na1\n{ aaa:bbb; }"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "a1") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa:bbb;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->name != NULL);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->name, "<sentinel>");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->name, "aaa");
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->value1, "bbb");


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_selector_004()
{
#define TEST_STRING "\na1\n{\naaa:bbb;\n}"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "a1") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa:bbb;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->name != NULL);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->name, "<sentinel>");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->name, "aaa");
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->value1, "bbb");


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_selector_005()
{
#define TEST_STRING "a1"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "a1") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_selector_006()
{
#define TEST_STRING "a1;a2 { aa:bb }"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "a1") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->name, "a2") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->next->value1, "aa:bb") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->ref == &doc->rootNode->child->next->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->name != NULL);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->next->child->name, "<sentinel>");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->type == SCSSTYPE_SENTINEL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->next->child->next->name, "aa");
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->next->child->next->value1, "bb");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->next->child == NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->next->next == doc->rootNode->child->next->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next->child->next->ref == &doc->rootNode->child->next->next->child->next);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_selector_007()
{
#define TEST_STRING "aaa { aaa: \"b:b:b\";\n}"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "aaa") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa: \"b:b:b\";") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->name != NULL);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->name, "<sentinel>");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->name, "aaa");
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->value1, "b:b:b");


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_selector_008()
{
#define TEST_STRING "aaa { aaa: &quot;b:b:b&quot;;\n}"
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
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "aaa") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "aaa: &quot;b:b:b&quot;;") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->name != NULL);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->name, "<sentinel>");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->name, "aaa");
  CU_ASSERT_STRING_EQUAL_OR_GOTO_END(doc->rootNode->child->next->child->next->value1, "b:b:b");


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
/*
 * vim:ts=2 et
 */
