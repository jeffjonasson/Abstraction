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
  Node testNode3 = btree(testKey, testValue, NULL);
  Node testNode2 = btree(testKeyLeft, testValueLeft, testNode3);
  Node testNode1 = btree(testKeyRight, testValueRight, testNode2);

  CU_ASSERT(strcmp(testKey, testNode1->key) == 0);
  CU_ASSERT(strcmp(testValue, testNode1->value) == 0);

  CU_ASSERT(strcmp(testKeyLeft, testNode1->left->key) == 0);
  CU_ASSERT(strcmp(testValueLeft, testNode1->left->value) == 0);

  CU_ASSERT(strcmp(testKeyRight, testNode1->right->key) == 0);
  CU_ASSERT(strcmp(testValueLeft, testNode1->left->value) == 0);
}


// void TEST_query_database(void){

//   char *testKey = "Anna";
//   char *testValue = "01";

//   char *testKeyLeft = "Aaron";
//   char *testValueLeft = "02";

//   char *testKeyRight = "Bodil";
//   char *testValueRight = "03";

//   /*construcy a binary tree for testing*/
//   Node testNode3 = btree(testKey, testValue, NULL);
//   Node testNode2 = btree(testKeyLeft, testValueLeft, testNode3);
//   Node testNode1 = btree(testKeyRight, testValueRight, testNode2);

//   CU_ASSERT(query_database(testNode1, testKey) == 1);
//   CU_ASSERT(query_database(testNode1, testKeyLeft) == 1);
//   CU_ASSERT(query_database(testNode1, testKeyRight) == 1);
//   CU_ASSERT(query_database(testNode1, "asdasd") == 0);

// }

void TEST_update_entry(void){

  char *testKey = "Anna";
  char *testValue2 = "02";
  char *testValue = "01";

  Node testNode = btree(testKey, testValue, NULL);
  update_entry(testNode, testKey, testValue2);

  //CU_ASSERT(strcmp(testValue2, testNode->testValue2) == 0);
  CU_ASSERT(strcmp(testValue2, testNode->value) == 0);
}

void TEST_insert_entry(void){

  char *testKey = "Anna";
  char *testValue = "01";

  char *testKeyLeft = "Aaron";
  char *testValueLeft = "02";

  char *testKeyRight = "Bodil";
  char *testValueRight = "03";

  Node testNode = btree(testKey, testValue, NULL);

  insert_entry(testNode, testKey, testValue);
  insert_entry(testNode, testKeyLeft, testValueLeft);
  insert_entry(testNode, testKeyRight, testValueRight);

  CU_ASSERT(strcmp(testKey, testNode->key) == 0);
  CU_ASSERT(strcmp(testValue, testNode->value) == 0);
  CU_ASSERT(strcmp(testKeyLeft, testNode->left->key) == 0);
  CU_ASSERT(strcmp(testValueLeft, testNode->left->value) == 0);
  CU_ASSERT(strcmp(testKeyRight, testNode->right->key) == 0);
  CU_ASSERT(strcmp(testValueLeft, testNode->left->value) == 0);

}

void TEST_delete_entry(void){

  // char *testKey = "Anna";
  // char *testValue = "01";

  // char *testKeyLeft = "Aaron";
  // char *testValueLeft = "02";

  // char *testKeyRight = "Bodil";
  // char *testValueRight = "03";

  // Node testNode = btree(testKey, testValue, NULL);

  // insert_entry(testNode, testKey, testValue);
  // insert_entry(testNode, testKeyLeft, testValueLeft);
  // insert_entry(testNode, testKeyRight, testValueRight);

  char *testKey = "Anna";
  char *testValue = "01";

  char *testKeyLeft = "Aaron";
  char *testValueLeft = "02";

  char *testKeyRight = "Bodil";
  char *testValueRight = "03";

  /*construcy a binary tree for testing*/
  Node testNode3 = btree(testKey, testValue, NULL);
  Node testNode2 = btree(testKeyLeft, testValueLeft, testNode3);
  Node testNode1 = btree(testKeyRight, testValueRight, testNode2);

  delete_entry(testNode1, "Aaron");

  CU_ASSERT(NULL == testNode1->left->key);
  CU_ASSERT(NULL == testNode1->left->value);
  // delete_entry(testNode1, testKeyRight);
  // CU_ASSERT(NULL == testNode1->right->key);
  // CU_ASSERT(NULL == testNode1->right->value);

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
    // (NULL == CU_add_test(pSuite1, "test query_database", TEST_query_database)) ||
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
