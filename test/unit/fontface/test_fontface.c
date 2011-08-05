#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "scss.h"


#define CU_ASSERT_OR_GOTO_END(X) { CU_ASSERT((X)); if (CU_get_number_of_failures() != 0) goto end; }
#define CU_ASSERT_STRING_EQUAL_GOTO_END(X, Y) do { CU_ASSERT_STRING_EQUAL((X),(Y)); if (CU_get_number_of_failures() != 0) goto end; } while (0)


void test_fontface_001();
void test_fontface_002();
void test_fontface_003();
void test_fontface_004();
void test_fontface_005();
void test_fontface_006();
void test_fontface_007();
/* pend */

int
main()
{
  CU_pSuite atkeyword_suite;
  CU_initialize_registry();
  atkeyword_suite = CU_add_suite("test Simple CSS(is based CSS2 but not CSS2)  Parser", NULL, NULL);
  CU_add_test(atkeyword_suite, "@fontface 001",  test_fontface_001);
  CU_add_test(atkeyword_suite, "@fontface 002",  test_fontface_002);
  CU_add_test(atkeyword_suite, "@fontface 003",  test_fontface_003);
  CU_add_test(atkeyword_suite, "@fontface 004",  test_fontface_004);
  CU_add_test(atkeyword_suite, "@fontface 005",  test_fontface_005);
  CU_add_test(atkeyword_suite, "@fontface 006",  test_fontface_006);
  CU_add_test(atkeyword_suite, "@fontface 007",  test_fontface_007);
  /* aend */

  CU_basic_run_tests();
  CU_cleanup_registry();

  return(0);
}


void test_fontface_001()
{
#define TEST_STRING "@font-face"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@font-face") == 0);
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
void test_fontface_002()
{
#define TEST_STRING "@font-face {}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@font-face") == 0);
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
void test_fontface_003()
{
#define TEST_STRING "@font-face { size: 10px }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@font-face") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "size: 10px") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->name, "size") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->value1, "10px") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_fontface_004()
{
#define TEST_STRING "@font-face { size: 10px; display: none }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@font-face") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "size: 10px; display: none") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->name, "size") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->value1, "10px") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->name, "display") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->value1, "none") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_fontface_005()
{
#define TEST_STRING "@font-face abc { size: 10px; display: none }"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@font-face") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "size: 10px; display: none") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->name, "size") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->value1, "10px") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->name, "display") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->value1, "none") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_fontface_006()
{
#define TEST_STRING "@font-face { size: 10px; display: none"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@font-face") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "size: 10px; display: none") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->name, "size") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->value1, "10px") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->name, "display") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->value1, "none") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_fontface_007()
{
#define TEST_STRING "@font-face { size: 10px;\n\ndisplay: none}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@font-face") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "size: 10px;\n\ndisplay: none") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->name, "size") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->value1, "10px") == 0);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->name != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->name, "display") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->child->next->next->value1, "none") == 0);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
/*
 * vim:ts=2 et
 */
