#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 40

typedef struct Node {
  struct Node *next;
  void* user;
} Node;

typedef struct HashTable {
  Node* entries[TABLE_SIZE];
} HashTable;

typedef struct User {
  char name[TABLE_SIZE]; //key
  struct HashTable* friends;
  int num_of_friends;
} User;

HashTable* initHashTable();
Node* initNode();
int hash(char* name);
int strsame(char* name1, char* name2);
int friend_collision(User* user1, User* user2);
void remove_friend(Node* nodePtr, char* friendName, int userIndex, int friendIndex, User* user, HashTable* table);
void P(char* name, HashTable* table);
void F(char* name1, char* name2, HashTable* table);
void U(char* name1, char* name2, HashTable* table);
void L(char *name, HashTable* table);
void Q(char* name1, char* name2, HashTable* table);
void empty_line();
void userCommand();