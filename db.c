#include "header.h"
#include <stdio.h>

int main(int argc, char *argv[]){

  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }

  char querybuffer[128];
  char updatekey[128];
  char updatevalue[128];
  char insertkey[128];
  char insertvalue[128];
  char deletekey[128];

  
  char *filename = *(argv +1); 
  Node list = read_database(filename); 


  int choice = -1;
  while(choice != 0){
    puts("Please choose an operation");
    puts("1. Query a key");
    puts("2. Update an entry");
    puts("3. New entry");
    puts("4. Remove entry");
    puts("5. Print database");
    puts("0. Exit database");
    printf("? \n");
    scanf("%d", &choice);
    while(getchar() != '\n'); 
    switch(choice){

    case 1: 
      printf("Enter Key: ");
      readline(querybuffer, 128, stdin);
      query_database(list, querybuffer);
      break;      // Query
    case 2: 
      printf("Enter Key: ");
      readline(updatekey, 128, stdin);
      printf("Enter Value ");
      readline(updatevalue, 128, stdin);
      update_entry(list, updatekey, updatevalue); 
      break;     // Update
    case 3:
      printf("Enter Key: ");
      readline(insertkey, 128, stdin);
      printf("Enter Value ");
      readline(insertvalue, 128, stdin);
      list = insert_entry(list, insertkey, insertvalue);
      break; // Insert
    case 4:
      printf("Enter Key: ");
      readline(deletekey, 128, stdin);
      list = delete_entry(list, deletekey);
      break; // Delete
    case 5:
      print_database(list);
      break;  // Print database
    case 0:
      puts("Good bye!"); 
      break; //exits
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
  return 0;
}
