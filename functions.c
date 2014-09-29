/*
AUTHORS:
Pouya Ashraf
Jeff Jonasson
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct node{
  char *key;
  char *value;
  struct node *left;
  struct node *right;
};


Node btree(char *key, char *value, Node newNode){
  if(newNode == NULL){
    Node newNode = malloc(sizeof(struct node)); //allocates memory for the new node
    newNode->key = malloc(strlen(key) + 1); //allocates memory for the key...
    strcpy(newNode->key, key); //copies contents of key to newNode->key
    newNode->value = malloc(strlen(value) + 1); //..and the value
    strcpy(newNode->value, value);
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
  } else if (strcmp(key, newNode->key) > 0){
    newNode->right = btree(key, value, newNode->right);
  } else {
    newNode->left = btree(key, value, newNode->left);
  }
  return newNode;
}

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

//Loads the contents of the database file inte memory.
Node read_database(char* filename){
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  char keybuffer[128];
  char valuebuffer[128];
  Node list = NULL;
  while(!(feof(database))){ //while NOT at the end of database file...
    readline(keybuffer, 128, database); //get the desired key from sdtin and store in "keybuffer"
    readline(valuebuffer, 128, database); //get the desired value from stdin and store in "valuebuffer"
    list = btree(keybuffer, valuebuffer, list); //call function btree to contruct a binary tree.
  }
  return list;
}

//queries the database for an entry. Takes a node as input.
void query_database(Node list){
 printf("Enter key: ");
 char buffer[128];
 int found = 0;
 Node cursor = list;
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          puts("Found entry:");
          printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
          found = 1;
        } else{
	  if(strcmp(buffer, cursor->key) > 0){
	    cursor = cursor->right;
	  } else {
	    cursor = cursor->left;
	  }
        }
      }
      if(!found){
        printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }
}

//updates the value of a user specified key in the database. Takes a Node as input.
void update_entry(Node list){
  printf("Enter key: ");
  char buffer[128];
  int found;
  Node cursor;
  readline(buffer, 128, stdin);
  puts("Searching database...\n");
  found = 0;
  cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Matching entry found:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    } else{
      if(strcmp(buffer, cursor->key) > 0){
      cursor = cursor->right;
      } else {
      cursor = cursor->left;
      }
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


Node insert_entry(Node list){
  char keybuffer[128];
  char valuebuffer[128];
  int found = 0;
  Node cursor = list;
  printf("Enter key: ");
  readline(keybuffer, 128, stdin);
  puts("Searching database for duplicate keys...");
  while(!found && cursor != NULL){
    if(strcmp(keybuffer, cursor->key) == 0){
      printf("key \"%s\" already exists!\n", cursor->key);
      found = 1;
    } else {
      if(strcmp(keybuffer, cursor->key) < 0){
	cursor = cursor->left;
      } else {
	cursor = cursor->right;
      }
    }
  }
  if(!found){ // Insert new node to the front of the list
    puts("Key is unique!\n");
    printf("Enter value: ");
    readline(valuebuffer, 128, stdin);
    btree(keybuffer, valuebuffer, list);
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", keybuffer, valuebuffer);
  }
  return list;
}


Node minimum(Node list){
  if(list == NULL){
    return NULL;
  } if(list->left){
    return minimum(list->left);
  } else {
    return list;}
}


Node deleteExternal(Node list, char *key){
  Node helper = NULL;
  if(list == NULL){
    printf("Could not find an entry matching key \"%s\"!\n", key);
  } else {
    if(strcmp(key, list->key) < 0){
      list->left = deleteExternal(list->left, key);
    } else if(strcmp(key, list->key) > 0){
      list->right = deleteExternal(list->right, key);
    } else {
      printf("Deleted entry:\n key: %s\n value:\n %s", list->key, list->value);
      if(list->left == NULL){
	list = list->right;
      } else {
	if(list->right == NULL){
	  list = list->left;
	} else {
	  helper = minimum(list->right);
	  list->key = helper->key;
	  list->right = deleteExternal(list->right, helper->key);
	  free(helper);
	}
      }
    }
  }
  return list;
}


Node delete_entry(Node list){
  char keybuffer[128];
  puts("Enter key: "); //a magical function of unknown capacity
  readline(keybuffer, 128, stdin);
  puts("Searching database...\n");
  list = deleteExternal(list, keybuffer);
  return list;
}

void print_database(Node list){
  Node cursor = list;
  if(cursor){
    print_database(cursor->right);
    puts(cursor->key);
    puts(cursor->value);
    print_database(cursor->left);
  }     
}

