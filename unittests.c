#include "CUnit/Basic.h"
#include "testheader.h"

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

void TEST_query_database(void){

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

  CU_ASSERT(query_database(testNode, testKey) == 1);
  CU_ASSERT(query_database(testNode, testKeyLeft) == 1);
  CU_ASSERT(query_database(testNode, testKeyRight) == 1);
  CU_ASSERT(query_database(testNode, "asdasd") == 0);

}

void TEST_update_entry(void){

  char *testKey = "Anna";
  char *testValue2 = "02";
  char * testValue = "01";

  Node testNode = btree(testKey, testValue NULL);
  update_entry(testNode, testValue2);

  CU_ASSERT(strcmp(testValue2, testNode->testValue2));
};

void TEST_insert_entry(void){

  char *testKey = "Anna";
  char *testValue = "01";

  char *testKeyLeft = "Aaron";
  char *testValueLeft = "02";

  char *testKeyRight = "Bodil";
  char *testValueRight = "03";

  testNode = NULL;

  insert_entry(testNode, testKey, testValue);
  insert_entry(testNode, testKeyLeft, testValueLeft);
  insert_entry(testNode, testKeyRight, testValueLeft);

  CU_ASSERT(strcmp(testKey, testNode->key));
  CU_ASSERT(strcmp(testValue, testNode->value));
  CU_ASSERT(strcmp(testKeyLeft, testNode->left->key));
  CU_ASSERT(strcmp(testValueLeft, testNode->left->value));
  CU_ASSERT(strcmp(testKeyight, testNode->right->key));
  CU_ASSERT(strcmp(testValueLeft, testNode->right->value));

};

void TEST_delete_entry(void){

  char *testKey = "Anna";
  char *testValue = "01";

  char *testKeyLeft = "Aaron";
  char *testValueLeft = "02";

  char *testKeyRight = "Bodil";
  char *testValueRight = "03";

  testNode = NULL;

  insert_entry(testNode, testKey, testValue);
  insert_entry(testNode, testKeyLeft, testValueLeft);
  insert_entry(testNode, testKeyRight, testValueLeft);

  delete_entry(testNode, testKeyLeft);
  CU_ASSERT(NULL == testNode->left->key);
  CU_ASSERT(NULL == testNode->left->value);
  delete_entry(testNode, testKeyRight);
  CU_ASSERT(NULL == testNode->right->key);
  CU_ASSERT(NULL == testNode->right->value);

}

int main(){
  CU_pSuite pSuite1 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("funcions.c tests", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

   if (
    (NULL == CU_add_test(pSuite1, "test btree", TEST_Btree)) ||
    (NULL == CU_add_test(pSuite1, "test query_database", TEST_query_database)) ||
    (NULL == CU_add_test(pSuite1, "test update_entry", TEST_update_entry)) ||
    (NULL == CU_add_test(pSuite1, "test insert_entry", TEST_insert_entry)) ||
    (NULL == CU_add_test(pSuite1, "test delete_entry", TEST_delete_entry))
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
