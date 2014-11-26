#include "header.h"

struct node{
  char *key;
  char *value;
  struct node *left;
  struct node *right;
};


Node btree(void *key, void *value, Node newNode){
  if(newNode == NULL){
    Node newNode = malloc(sizeof(struct node));
    newNode->key = malloc(strlen(key) + 1);
    strcpy(newNode->key, key); 
    newNode->value = malloc(strlen(value) + 1); 
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


Node read_database(char* filename){
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  char keybuffer[128];
  char valuebuffer[128];
  Node newNode = NULL;
  while(!(feof(database))){ 
    readline(keybuffer, 128, database); 
    readline(valuebuffer, 128, database); 
    newNode = btree(keybuffer, valuebuffer, newNode);
  }
  return newNode;
}


int query_database(Node list, char *query){
 int found = 0;
 Node cursor = list;
      puts("Searching database...\n");
      while(!found && cursor != NULL){
        if(strcmp(query, cursor->key) == 0){
          puts("Found entry:");
          printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
          found = 1;
        } 
        else{
	       if(strcmp(query, cursor->key) > 0){
	        cursor = cursor->right;
	       }
        else {
	       cursor = cursor->left;
          }
        }
      }
      if(!found){
        printf("Could not find an entry matching key \"%s\"!\n", query);
      }
  return found;
}


void update_entry(Node list, char *key, char *value){
  int found;
  Node cursor;
  puts("Searching database...\n");
  found = 0;
  cursor = list;
  while(!found && cursor != NULL){
    if(strcmp(key, cursor->key) == 0){
      puts("Matching entry found:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    } else{
      if(strcmp(key, cursor->key) > 0){
      cursor = cursor->right;
      } else {
      cursor = cursor->left;
      }
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", key);
  }else{
    free(cursor->value);
    cursor->value = malloc(strlen(value) + 1);
    strcpy(cursor->value, value);
    puts("Value inserted successfully!");
  }
}


Node insert_entry(Node list, char *key, char *value){
  int found = 0;
  Node cursor = list;
  puts("Searching database for duplicate keys...");
  while(!found && cursor != NULL){
    if(strcmp(key, cursor->key) == 0){
      printf("key \"%s\" already exists!\n", cursor->key);
      found = 1;
    } else {
      if(strcmp(key, cursor->key) > 0){
	cursor = cursor->right;
      } else {
	cursor = cursor->left;
      }
    }
  }
  if(!found){  
    btree(key, value, list);
    puts("");
    puts("Entry inserted successfully:");
    printf("key: %s\nvalue: %s\n", key, value);
  }
  return list;
}


Node minimum(Node list){
  if(list == NULL){
    return NULL;
  } if(list->left){
    return minimum(list->left);
  } else {
    return list;
  }
}


Node deleteExternal(Node list, char *key){
  Node helper = NULL;
  if(list == NULL){
    printf("Could not find an entry matching key \"%s\"!\n", key);
  } else {
    if(strcmp(key, list->key) < 0){
      list->left = deleteExternal(list->left, key);
    } else {
      if(strcmp(key, list->key) > 0){
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
  }
  return list;
}

Node delete_entry(Node list, char *key){
  puts("Searching database...\n");
  list = deleteExternal(list, key);
  return list;
}

void print_database(Node cursor){
  if(cursor){
    print_database(cursor->right);
    puts(cursor->key);
    puts(cursor->value);
    print_database(cursor->left);
  }     
}

