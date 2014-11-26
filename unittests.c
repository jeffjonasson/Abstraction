#include "CUnit/Basic.h"
#include "header.h"

int init_suite_1(void){
  return 0;
}

int clean_suite_1(void){
  return 0;
}

int init_suite_2(void){
  return 0;
}

int clean_suite_2(void){
  return 0;
}

void TEST_Btree(void){

  char *testKey = "Anna";
  char *testValue = "01";

  char *testKeyLeft = "Aaron";
  char *testValueLeft = "02";

  char *testKeyRight = "Bodil";
  char *testValueRight = "03";

  /*construcy a binary tree for testing*/
  Node testNode = btree(testKey, testValue, NULL);
  Node testNode = btree(testKeyLeft, testValueLeft, testNode);
  Node testNode = btree(testKeyRight, testValueRight, testNode);

  CU_ASSERT(strcmp(testKey, testNode->key));
  CU_ASSERT(strcmp(testValue, testNode->value));

  CU_ASSERT(strcmp(testKeyLeft, testNode->left->key));
  CU_ASSERT(strcmp(testValueLeft, testNode->left->value));

  CU_ASSERT(strcmp(testKeyRight, testNode->right->key));
  CU_ASSERT(strcmp(testValueLeft, testNode->right->value);
}


int main(){
  CU_pSuite pSuite1 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

   if (
    (NULL == CU_add_test(pSuite1, "test if test works", TEST_Btree))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();

}
