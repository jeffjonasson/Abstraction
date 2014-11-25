#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//typedef struct node *Node;

typedef struct node{
  char *key;
  char *value;
  struct node *left;
  struct node *right;
} *Node;

/**
 * @brief A struct for a node in the database
 * @details A node in the database containing the key and a value.
 * 
 * @param filename path to the database file
 * @return A node in the database.
 */
Node read_database(char *filename);

/**
 * @brief inserts a node
 * @details inserts a node in the tree with specified key and value
 * 
 * @param key key
 * @param value value
 * @param newNode the tree
 * @return the tree with a new node inserted in the correct place.
 */
Node btree(void *key, void *value, Node newNode);

/**
 * @brief Function to query the database for a stored value.
 * @details Queries the database for the key specified by the user.
 * 
 * @param list the database stored in memory.
 */
void query_database(Node list);

/**
 * @brief Function to update an entry in the databse.
 * @details 
 * 
 * @param list The database stored in memory.
 */
void update_entry(Node list);

/**
 * @brief Function to insert a new entry in the database.
 * @details Inserts a new entry in the database. Key and value a prompted from the user when the function is called.
 * 
 * @param list The database stored in memory.
 * @return The databse with the new node inserted.
 */
Node insert_entry(Node list);

/**
 * @brief Function to delete an entry from the database.
 * @details Deletes an entry from the database. Prompts the user for which entry to delete when function is called.
 * 
 * @param list The database stored in memory.
 * @return The database with specified entry removed.
 */
Node delete_entry(Node list);

/**
 * @brief prints the database.
 * @details Prints the contents of the database to standard output.
 * 
 * @param list the database stored in memory.
 */
void print_database(Node list);
