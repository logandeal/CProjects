#include "facebook.h"

// All entries should be saved in memory

// Creates a new hash table
HashTable* initHashTable(){
  HashTable* emptyTable = malloc(sizeof(HashTable));
  if (emptyTable == NULL){
    fprintf(stderr, "Error: malloc failure.\n");
    exit(0);
  }
  for (int i = 0; i < TABLE_SIZE; i++){
    emptyTable->entries[i] = NULL;
  }
  return emptyTable;
}

// Initializes a new node
Node* initNode(){
  Node* newNode = malloc(sizeof(Node));
  if (newNode == NULL){
    fprintf(stderr, "Error: malloc failure.\n");
    exit(0);
  }
  newNode->next = NULL;
  return newNode;
}

// // Hashes the name to an int
// int hash(char* name){
//   int sum = 0;
//   int character = 0;
//   while(name[character] != '\0'){
//     sum = sum + name[character];
//     character++;
//   }
//   return sum % TABLE_SIZE;
// }

// djb2 Hash
int hash(char *name)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *name++)){
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }

  return hash % TABLE_SIZE;
}

// Checks if two strings are the exact same
// This function can be removed (replaced with strcmp) to make the program more efficient
int strsame(char* name1, char* name2){
  if(strlen(name1) != strlen(name2)){
    return -2; // Not even the same length
  }
  for(int i = 0; i < strlen(name1); i++){
    if(name1[i] != name2[i]){
      return -1; // Not the exact same
    }
  }
  return 0; // The strings are the exact same
}

// Checks if two friends collide or not
int friend_collision(User* user1, User* user2){
  int index1 = hash(user1->name);
  int index2 = hash(user2->name);
  if(user1->friends->entries[index2] == NULL){
    return 0;
  }
  else{
    Node* nodePtr = user1->friends->entries[index2];
    while(nodePtr != NULL){
      if(strsame(((User*)(nodePtr->user))->name, user2->name) == 0){
        return 1;
      }
      nodePtr = nodePtr->next;
    }
  }
  return 0;
}

// Removes a friend from a user
void remove_friend(Node* nodePtr, char* friendName, int userIndex, int friendIndex, User* user, HashTable* table){
  Node* temp = NULL;
  while(nodePtr != NULL){
    if(strsame(((User*)(nodePtr->user))->name, friendName) == 0){
      //strcpy(((User*)(nodePtr->user))->name, -1);
      if(temp != NULL){ // Node to delete is not first and there are multiple nodes
        temp->next = nodePtr->next;
        free(nodePtr);
        nodePtr = NULL;
      }
      else{
        if(nodePtr->next == NULL){ // Node to delete is first node and is the only node
          free(nodePtr);
          nodePtr = NULL;
          ((User*)(table->entries[userIndex]->user))->friends->entries[friendIndex] = nodePtr;
        }
        else{ // Node to delete is the first node and there are more nodes
          ((User*)(table->entries[userIndex]->user))->friends->entries[friendIndex] = nodePtr->next;
          free(nodePtr);
          nodePtr = NULL;
        }
      }
      ((User*)(table->entries[userIndex]->user))->num_of_friends--;
      return;
    }
    temp = nodePtr;
    nodePtr = nodePtr->next;
  }
}

void P(char* name, HashTable* table){
  int index = hash(name);

  Node* newNode = initNode();
  newNode->next = table->entries[index];
  table->entries[index] = newNode;

  table->entries[index]->user = malloc(sizeof(User));
  if (table->entries[index]->user == NULL){
    fprintf(stderr, "Error: malloc failure.\n");
    exit(0);
  }
  strcpy(((User*)(table->entries[index]->user))->name, name);
  ((User*)(table->entries[index]->user))->friends = initHashTable();
  ((User*)(table->entries[index]->user))->num_of_friends = 0;
}

void F(char* name1, char* name2, HashTable* table){
  int index1 = hash(name1);
  int index2 = hash(name2);

  if(table->entries[index1] == NULL || table->entries[index2] == NULL){
    fprintf(stderr, "Error: one or two of the names provided do not exist.\n");
    return;
  }
  else if(index1 == index2){
    int counter = 0;
    Node *nodePtr = table->entries[index1];
    while(nodePtr != NULL){
      if(strsame(((User*)(nodePtr->user))->name, name1) == 0 || strsame(((User*)(nodePtr->user))->name, name2) == 0){
        counter++;
      }
      nodePtr = nodePtr->next;
    }
    if(counter < 2){
      fprintf(stderr, "Error: one or two of the names provided do not exist.\n");
      return;
    }
  }

  

  User* user1 = (User*) table->entries[index1]->user;
  User* user2 = (User*) table->entries[index2]->user;

  if(friend_collision(user1, user2)){
    fprintf(stderr, "Error: users provided are already friends.\n");
    return;
  }

  Node* newNode = initNode();
  newNode->user = malloc(sizeof(User));
  if (newNode->user == NULL){
    fprintf(stderr, "Error: malloc failure.\n");
    exit(0);
  }
  strcpy(((User*)(newNode->user))->name, name2);
  newNode->next = ((User*)(table->entries[index1]->user))->friends->entries[index2];
  ((User*)(table->entries[index1]->user))->friends->entries[index2] = newNode;

  Node* newNode2 = initNode();
  newNode2->user = malloc(sizeof(User));
  if (newNode2->user == NULL){
    fprintf(stderr, "Error: malloc failure.\n");
    exit(0);
  }
  strcpy(((User*)(newNode2->user))->name, name1);
  newNode2->next = ((User*)(table->entries[index2]->user))->friends->entries[index1];
  ((User*)(table->entries[index2]->user))->friends->entries[index1] = newNode2;

  ((User*)(table->entries[index1]->user))->num_of_friends++;
  ((User*)(table->entries[index2]->user))->num_of_friends++;
}

void U(char* name1, char* name2, HashTable* table){
  int index1 = hash(name1);
  int index2 = hash(name2);

  if(table->entries[index1] == NULL || table->entries[index2] == NULL){
    fprintf(stderr, "Error: one or two of the names provided do not exist.\n");
    return;
  }
  else if(index1 == index2){
    int counter = 0;
    Node *nodePtr = table->entries[index1];
    while(nodePtr != NULL){
      if(strsame(((User*)(nodePtr->user))->name, name1) == 0 || strsame(((User*)(nodePtr->user))->name, name2) == 0){
        counter++;
      }
      nodePtr = nodePtr->next;
    }
    if(counter < 2){
      fprintf(stderr, "Error: one or two of the names provided do not exist.\n");
      return;
    }
  }

  User* user1 = (User*) table->entries[index1]->user;
  User* user2 = (User*) table->entries[index2]->user;

  if(friend_collision(user1, user2)){
    Node* nodePtr1 = ((User*)(table->entries[index1]->user))->friends->entries[index2];
    remove_friend(nodePtr1, name2, index1, index2, user1, table);

    Node* nodePtr2 = ((User*)(table->entries[index2]->user))->friends->entries[index1];
    remove_friend(nodePtr2, name1, index2, index1, user2, table);

    return;
  }

  fprintf(stderr, "Error: names provided were already not friends.\n");
  return;

  // for (int i = 0; i <= table->entries[index1]->user->num_of_friends; i++){
  //   if (strcmp(table->entries[index1]->user->friends[i]->name, name2) == 0){
  //     table->entries[index1]->user->friends[i] == NULL;
  //     table->entries[index1]->user->num_of_friends--;
  //     break;
  //   }
  // }
  // for (int i = 0; i <= table->entries[index1]->user->num_of_friends; i++){
  //   if (strcmp(table->entries[index2]->user->friends[i]->name, name1) == 0){
  //     table->entries[index2]->user->friends[i] == NULL;
  //     table->entries[index2]->user->num_of_friends--;
  //     break;
  //   }
  // }
}

void L(char *name, HashTable* table){
  int index = hash(name);
  if(table->entries[index] == NULL){
    fprintf(stderr, "%s does not exist.\n", name);
    return;
  }
  else{
    int counter = 0;
    Node *nodePtr = table->entries[index];
    while(nodePtr != NULL){
      if(strsame(((User*)(nodePtr->user))->name, name) == 0){
        counter++;
      }
      nodePtr = nodePtr->next;
    }
    if(counter < 1){
      fprintf(stderr, "%s does not exist.\n", name);
      return;
    }
  }
  if(((User*)(table->entries[index]->user))->num_of_friends < 1){
    fprintf(stderr, "%s has no friends.\n", name);
    return;
  }
  printf("%s's Friends:\n", name);
  for(int i = 0; i < TABLE_SIZE; i++) {
      if(((User*)(table->entries[index]->user))->friends->entries[i] != NULL){
        Node* nodePtr = ((User*)(table->entries[index]->user))->friends->entries[i];
        while(nodePtr != NULL){
          printf("%s\n", ((User*)(nodePtr->user))->name);
          nodePtr = nodePtr->next;
        }
      }
  }

  // for(int i = 0; i <= table->entries[index]->user->friends->entries; i++){
  //   printf("%d: %s\n", i, table->entries[index]->user->friends[i]->name);
  // }
}

void Q(char* name1, char* name2, HashTable* table){
  int index1 = hash(name1);
  int index2 = hash(name2);

  if(table->entries[index1] == NULL || table->entries[index2] == NULL){
    fprintf(stderr, "Error: one or two of the names provided do not exist.\n");
    return;
  }
  else if(index1 == index2){
    int counter = 0;
    Node *nodePtr = table->entries[index1];
    while(nodePtr != NULL){
      if(strsame(((User*)(nodePtr->user))->name, name1) == 0 || strsame(((User*)(nodePtr->user))->name, name2) == 0){
        counter++;
      }
      nodePtr = nodePtr->next;
    }
    if(counter < 2){
      fprintf(stderr, "Error: one or two of the names provided do not exist.\n");
      return;
    }
  }

  User* user1 = (User*) table->entries[index1]->user;
  User* user2 = (User*) table->entries[index2]->user;
  
  if(friend_collision(user1, user2)){
    printf("Yes.\n");
  }
  else{
    printf("No.\n");
  }
}

void empty_line(){
  int c = getchar();
  while(c != '\n' && c != EOF){
    c = getchar();
  }
}

// Runs the commmands
void userCommand(HashTable* table){
  int args_permitted = 3;
  char input[50];
  strcpy(input, "");
  char arguments[args_permitted][TABLE_SIZE];

  int arg_i = 0;
  printf("----Facebook----\n");
  printf("Enter a command:\n");
  while(strcmp(input, "X") != 0){
    scanf("%[^\n]", input);
    char* token = strtok(input, " ");
    while(token != NULL && arg_i <= 2){
      if(arg_i == 0 && strlen(token) != 1){
        fprintf(stderr, "Error: invalid input.\n");
        break;
      }
      //arguments[arg_i] = malloc(strlen(token)*sizeof(char));
      if(arguments[arg_i] == NULL){
        fprintf(stderr, "Error: malloc failure.\n");
        break;
      }
      strcpy(arguments[arg_i], token);
      token = strtok(NULL, " ");
      arg_i++;
    }
    arg_i = 0;
    if(arguments[1] == NULL){
      printf("*******\n");
    }
    if(strcmp(arguments[0], "P") == 0 && strlen(arguments[1]) > 0){
      P(arguments[1], table);
    }
    else if(strcmp(arguments[0], "F") == 0 && strlen(arguments[1]) > 0 && strlen(arguments[2]) > 0){
      F(arguments[1], arguments[2], table);
    }
    else if(strcmp(arguments[0], "U") == 0 && strlen(arguments[1]) > 0 && strlen(arguments[2]) > 0){
      U(arguments[1], arguments[2], table);
    } 
    else if(strcmp(arguments[0], "L") == 0 && strlen(arguments[1]) > 0){
      L(arguments[1], table);
    }
    else if(strcmp(arguments[0], "Q") == 0 && strlen(arguments[1]) > 0 && strlen(arguments[2]) > 0){
      Q(arguments[1], arguments[2], table);
    } 
    else if(strcmp(arguments[0], "X") != 0){
      fprintf(stderr, "Error: unknown command.\n");
    }
    empty_line();
  }
}