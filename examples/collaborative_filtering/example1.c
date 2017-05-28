#include <stdio.h>
#include "../../lib/formulas.h"
#include "../../lib/hash.h"

void error_creating(char *name);

int main() {

  mhash *f1, *f2, *f3, *you; // three friends and you
  mhash *users[] = {f1, f2, f3, you};
  char c[] = {'1', '2', '3'};
  const num = 3; // number of restaurants
  char scores[][4] = {{2,4,4,4}, {1,4,3,3}, {4,5,5,5}, {4,5,4,4}};

  int i;

  // Add scores for 3 friends
  for (i = 0; i < 3; i++)
    if ((users[i] = hashadd("friend" + c[i], (char *) scores[i])) == NULL) 
    error_creating("user");

  // Add scores for user "you"
  if ((you = hashadd("you", scores[3])) == NULL) 
    error_creating("user: you"); 

  // Get Manhattan Distance  
  for (i = 0; i < 3; i++) 
    printf("manhattan_distance from you to friend %c: %d\n", c[i], manhattan_distance(you->value, users[i]->value, 4));
  // Get Euclidean Distance 

  return 0;
}

void error_creating (char*name) {
  printf("Error creating %s\n", name);
  exit(1);
}
