#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "scss.h"


#define CU_ASSERT_OR_GOTO_END(X) { CU_ASSERT((X)); if (CU_get_number_of_failures() != 0) goto end; }
#define CU_ASSERT_STRING_EQUAL_GOTO_END(X, Y) do { CU_ASSERT_STRING_EQUAL((X),(Y)); if (CU_get_number_of_failures() != 0) goto end; } while (0)


void test_media_001();
void test_media_002();
void test_media_003();
void test_media_004();
void test_media_005();
void test_media_006();
void test_media_007();
void test_media_008();
void test_media_009();
void test_media_010();
void test_media_011();
/* pend */

int
main()
{
  CU_pSuite atkeyword_suite;
  CU_initialize_registry();
  atkeyword_suite = CU_add_suite("test Simple CSS(is based CSS2 but not CSS2)  Parser", NULL, NULL);
  CU_add_test(atkeyword_suite, "@media 001",  test_media_001);
  CU_add_test(atkeyword_suite, "@media 002",  test_media_002);
  CU_add_test(atkeyword_suite, "@media 003",  test_media_003);
  CU_add_test(atkeyword_suite, "@media 004",  test_media_004);
  CU_add_test(atkeyword_suite, "@media 005",  test_media_005);
  CU_add_test(atkeyword_suite, "@media 006",  test_media_006);
  CU_add_test(atkeyword_suite, "@media 007",  test_media_007);
  CU_add_test(atkeyword_suite, "@media 008",  test_media_008);
  CU_add_test(atkeyword_suite, "@media 009",  test_media_009);
  CU_add_test(atkeyword_suite, "@media 010",  test_media_010);
  CU_add_test(atkeyword_suite, "@media 011",  test_media_011);
  /* aend */

  CU_basic_run_tests();
  CU_cleanup_registry();

  return(0);
}


void test_media_001()
{
#define TEST_STRING "@media"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_002()
{
#define TEST_STRING "@media all {}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "all") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child == NULL);


end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_003()
{
#define TEST_STRING "@media handheld { br {display:none}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref == &doc->rootNode->child->next->child->next->child->next);



end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_004()
{
#define TEST_STRING "\n\n@media handheld { br {display:none}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref == &doc->rootNode->child->next->child->next->child->next);



end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_005()
{
#define TEST_STRING "@/*abc*/media handheld { br {display:none}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref == &doc->rootNode->child->next->child->next->child->next);



end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_006()
{
#define TEST_STRING "@media/*abc*/ handheld { br {display:none}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref == &doc->rootNode->child->next->child->next->child->next);



end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_007()
{
#define TEST_STRING "@media\nhandheld { br {display:none}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref == &doc->rootNode->child->next->child->next->child->next);



end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_008()
{
#define TEST_STRING "@media handheld, print { br {display:none}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld, print") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref == &doc->rootNode->child->next->child->next->child->next);



end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_009()
{
#define TEST_STRING "@media handheld { br {display:none;display2:none2}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none;display2:none2}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none;display2:none2");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->next->name,   "display2");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->next->value1, "none2");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next->ref == &doc->rootNode->child->next->child->next->child->next->next);



end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_010()
{
#define TEST_STRING "@media handheld { br {display:none}\nhr {display:none}}"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display:none}\nhr {display:none}") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  /* br's property check */
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref  == &doc->rootNode->child->next->child->next->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->next->name,   "hr");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->next->value1, "display:none");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->next->value2, "");
  /* hr's property check */
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->next->child->next->value1, "none");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->child->next->next == doc->rootNode->child->next->child->next->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->child->next->ref  == &doc->rootNode->child->next->child->next->next->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next->ref == &doc->rootNode->child->next->child->next->next);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
void test_media_011()
{
#define TEST_STRING "@media handheld { br {display"
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
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->name, "@media") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value1, "br {display") == 0);
  CU_ASSERT_OR_GOTO_END(strcasecmp(doc->rootNode->child->next->value2, "handheld") == 0);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->next == doc->rootNode->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->ref == &doc->rootNode->child->next);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->type == SCSSTYPE_SELECTOR);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->name,   "br");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value1, "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->value2, "");
  /* br's property check */
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child != NULL);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->type == SCSSTYPE_PROPERTY);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->name != NULL);
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->name,   "display");
  CU_ASSERT_STRING_EQUAL_GOTO_END(doc->rootNode->child->next->child->next->child->next->value1, "");
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->next == doc->rootNode->child->next->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->child->next->ref  == &doc->rootNode->child->next->child->next->child->next);

  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->next == doc->rootNode->child->next->child);
  CU_ASSERT_OR_GOTO_END(doc->rootNode->child->next->child->next->ref == &doc->rootNode->child->next->child->next);

end:
  apr_terminate();
  fprintf(stderr, "end %s\n", __func__);
#undef TEST_STRING
}
/*
 * vim:ts=2 et
 */
