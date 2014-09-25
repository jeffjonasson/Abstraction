#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *Node;

//read_database
//reads the contents of given database file
Node read_database(char *filename);

//query_database
//takes a Node as input, No return value. Queries the database for an entry.
void query_database(Node list);

//update_database
//Takes a Node as input, has no return value. Updates an entry in the database.
void update_database(Node list);

//insert_database
//takes a Node as input, returns the database with a new node inserted.
Node insert_entry(Node list);

//delete_entry
//takes a Node as input, returns the database with a (user specified) node deleted.
Node delete_entry(Node list);

//print_database
//takes a Node as input, no return value, prints the contents of 
//database to standard output stream
void print_database(Node list);
