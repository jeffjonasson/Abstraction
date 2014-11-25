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

void testBtree(void){

  char *testKey = "Anna";
  char *testValue = "01";
  Node testNode = malloc(sizeof(Node));
  newNode->key = malloc(sizeof(testKey));
  newNode->Value = malloc(sizeof(testValue));
  testNode->key = testKey;
  testNode->value = testValue;

  Node testNode2 = btree(testKey, testValue, NULL);

  CU_ASSERT(testNode->key == testNode2->key);
  CU_ASSERT(testNode->value == testNode2->value);
};


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
    (NULL == CU_add_test(pSuite1, "test if test works", testBtree()))
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
