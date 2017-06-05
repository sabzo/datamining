/* Example for determining Manhattan and Euclidean Distances between two users. 
The idea is the shorter distance between two users means the users have similar
preferences */

#include <stdio.h>
#include "../../lib/lib.h"

int main() {

  user *f1, *f2, *f3, *you; // three friends and you
  user *users[] = {f1, f2, f3, you};
  char c[] = {'1', '2', '3'};
  const num = 3; // number of restaurants
  rating f1r[] = {{"Blues Traveler", 3.5}, {"Broken Bells",1.0}, {"Norah Jones", 1.5},{"Phoenix", 5.0}, NULL};
  rating f2r[] = {{"Blues Traveler", 1.5}, {"Broken Bells",2.0}, {"Norah Jones", 2.0},{"Phoenix", 5.0}, NULL};
  rating f3r[] = {{"Blues Traveler", 0.5}, {"Broken Bells",3.0}, {"Norah Jones", 3.0},{"Phoenix", 3.0}, NULL};
  rating userr[] = {{"Blues Traveler", 3.5}, {"Broken Bells",2.0}, {"Norah Jones", 2.0},{"Phoenix",2.0}, NULL};
 
  rating *scores[4] = {f1r, f2r, f3r, userr};
 // char scores[][9] = {{2,4,4,0,1,5,0,0,3}, {0,0,3,3,2,0,2,0,4}, {3,0,5,5,0,3,4,5,3}, {4,5,0,4,0,0,2,5,4}};

  int i;

  // Add scores for 3 friends
  for (i = 0; i < 3; i++)
    if ((users[i] = _user_add("friend" + c[i], scores[i])) == NULL) 
    error_creating("user");

  // Add scores for userr 
  if ((you = _user_add("you", scores[3])) == NULL) 
    error_creating("user: you"); 

  // Get Manhattan Distance  
  for (i = 0; i < 3; i++) 
    printf("Manhattan Distance from you to friend %c: %d\n", c[i], manhattan_distance(you->value, users[i]->value));

  printf("\n\n");

  // Get Euclidean Distance 
  for (i =0; i < 3; i++)
    printf("Euclidean Distance from you to friend %c: %f\n", c[i], euclidean_distance(you->value, users[i]->value)); 

  return 0;
}
