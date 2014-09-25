#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct node{
  char *key;
  char *value;
  struct node *next;
  };

/*GLOBAL VARIABLES:*/
char buffer[128];
int found;
Node cursor;
Node list = NULL;

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void read_database(char* databaso){
  printf("Loading database \"%s\"...\n\n", databaso);
  FILE *database = fopen(databaso, "r");
  while(!(feof(database))){
    Node newNode = malloc(sizeof(struct node));
    readline(buffer, 128, database);
    newNode->key = malloc(strlen(buffer) + 1);
    strcpy(newNode->key, buffer);
    readline(buffer, 128, database);
    newNode->value = malloc(strlen(buffer) + 1);
    strcpy(newNode->value, buffer);
    newNode->next = list;
    list = newNode;
  }
}

void query_database(){
 printf("Enter key: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      found = 0;
      cursor = list;
      while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          puts("Found entry:");
          printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
          found = 1;
        }else{
          cursor = cursor->next;
        }
      }
      if(!found){
        printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }
}

void update_database(){
 printf("Enter key: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      found = 0;
      cursor = list;
      while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          puts("Matching entry found:");
          printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
          found = 1;
        }else{
          cursor = cursor->next;
        }
      }
      if(!found){
        printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }else{
        printf("Enter new value: ");
        readline(buffer, 128, stdin);
        free(cursor->value);
        cursor->value = malloc(strlen(buffer) + 1);
        strcpy(cursor->value, buffer);
        puts("Value inserted successfully!");
      }
}

void update_entry(){
printf("Enter key: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      found = 0;
      cursor = list;
      while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          puts("Matching entry found:");
          printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
          found = 1;
        }else{
          cursor = cursor->next;
        }
      }
      if(!found){
        printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }else{
        printf("Enter new value: ");
        readline(buffer, 128, stdin);
        free(cursor->value);
        cursor->value = malloc(strlen(buffer) + 1);
        strcpy(cursor->value, buffer);
        puts("Value inserted successfully!");
      }
}

void insert_entry(){
printf("Enter key: ");
      readline(buffer, 128, stdin);
      puts("Searching database for duplicate keys...");
      found = 0;
      cursor = list;
      while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          printf("key \"%s\" already exists!\n", cursor->key);
          found = 1;
        }else{
          cursor = cursor->next;
        }
      }
      if(!found){ // Insert new node to the front of the list
        puts("Key is unique!\n");
        Node newNode = malloc(sizeof(struct node));
        newNode->key = malloc(strlen(buffer) + 1);
        strcpy(newNode->key, buffer);
        printf("Enter value: ");
        readline(buffer, 128, stdin);
        newNode->value = malloc(strlen(buffer) + 1);
        strcpy(newNode->value, buffer);
        newNode->next = list;
        list = newNode;
        puts("");
        puts("Entry inserted successfully:");
        printf("key: %s\nvalue: %s\n", list->key, list->value);
      }
}

void delete_entry(){
 printf("Enter key: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      found = 0;
      cursor = list;
      Node prev = NULL;
      while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          if(prev == NULL){ // Delete first node
            list = cursor->next;
          }else{
            prev->next = cursor->next;
          }
          found = 1;
          printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);
        }else{
          prev = cursor;
          cursor = cursor->next;
        }
      }
      if(!found){
        printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }
}

void print_database(){
 cursor = list;
      while(cursor != NULL){
        puts(cursor->key);
        puts(cursor->value);
        cursor = cursor->next;
      }
      
}
int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
  // Read the input file
  char *filename = *(argv +1);
  read_database(filename);
  // Main loop
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
    while(getchar() != '\n'); // Clear stdin
    switch(choice){
    case 1: query_database(); break;      // Query
    case 2: update_entry(); break;     // Update
    case 3: insert_entry(); break; // Insert
    case 4: delete_entry(); break; // Delete
    case 5: print_database(); break;  // Print database
    case 0: puts("Good bye!"); break; //exits
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
  return 0;
}

