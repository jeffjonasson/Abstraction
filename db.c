#include "header.h"

int main(int argc, char *argv[]){
  //checks if a database file is given as argument.
  // If not terminates the program.
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

  char *filename = *(argv +1); //filename = pointer to argument vector
  Node list = read_database(filename); //list = an array of characters

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
    case 1: query_database(list); break;      // Query
    case 2: update_entry(list); break;     // Update
    case 3: insert_entry(list); break; // Insert
    case 4: delete_entry(list); break; // Delete
    case 5: print_database(list); break;  // Print database
    case 0: puts("Good bye!"); break; //exits
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
  return 0;
}
