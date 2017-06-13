/* Example for determining Manhattan and Euclidean Distances between a CSV list of users and associated ratings. 
The idea is the shorter distance between two users means the users have similar
preferences */

#include <stdio.h>
#include "../../lib/lib.h"
 
// Create Hash, from macro expansion, for storing users and their ratings
HASH(user, char *, struct user, rating, HASHSIZE)
// Get nearby users
int distance_compare(distance *d1, distance *d2) {
  int eq;
  if (d1->distance == d2->distance)
    eq = 0;
  else if (d1->distance < d2->distance)
    eq = -1;
  else
    return 1;
}
// TODO struct rec_args {
  // args
  
// Returns number of nearby users calculated as near


typedef int (*fnptr_t) (int a, const char *b);

int nearby_users(distance *ud, const user *u, user **users, int len) {
  int num_users = 0;
  int i = 0;
  int total = 0;
  // parse through users calculating distance
  while (i < HASHSIZE) {   
    const user *tmp = (*users);
    while (tmp && tmp->key != NULL && total < len) { 
      distance d = {tmp->key, euclidean_distance(u->value, tmp->value)};
      if (d.distance) {
        ud[total++] = d;
        num_users++;
      }
      tmp = tmp->next;
    }
    users++;
    i++; 
  }
  qsort(ud, num_users, sizeof(distance), (int (*)(const void *, const void *)) distance_compare);
  return num_users;
}

void rank (void *heuristic, distance *d) {
}
int main(int argc, char *argv[]) {

  FILE *fp;
  char line[MAXLINE]; // each line
  char *filename; 
  char *uid = NULL; // user id 
  user *u;
  distance distances[MAXDISTANCES];
  int total_distances;
  char **results[MAXRECOMMENDATIONS];

  if (argc < 2)
    usage(argv[0]);
  // Get userID from commandline
  if (argc == 3)
    uid = argv[2];

   // Open ratings file
   filename = argv[1];
   if ((fp = fopen (filename, "r")) == NULL) 
     error("Unable to open file \n");

   // Add/update user ratings
   while (fgets(line, MAXLINE, fp) != NULL) {
       char **words = delim(line, ','); 
       char *uid = *words;
       char *title = *(words + 1);
       char *_rating = *(words + 2);
       rating r = {title, atof(_rating)};
       
       // printf("User %s, title: %s, rating: %s\n", uid, title, _rating);
       _user_add(uid, r);
   }

   // Allow user to choose a userID
   if (uid == NULL) {
     int i = 0;
     printf("Enter a user id to find ratings\n");
     uid = calloc(UIDSIZE + 1, sizeof(char)); // +1 for \0 
     while (i < UIDSIZE && (uid[i] = getc(stdin)) != '\n') 
       i++; 
     uid[i] = '\0';
     printf("uid: %s\n", uid);
    } 
 
   // Get ratings for a user
   if ((u = _user_find(uid)) != NULL) {
       int i;
       for (i = 0; i < u->v_it; i++) {
         rating r = u->value[i];
         printf("movie: %s, rating: %f\n", r.key, r.score);
       }
    }  
   
   recommend(distances, u, (const void **) _user_hash, MAXDISTANCES, (const void*) u, (void (*)(void *, void *, void *, int)) nearby_users, (void (*)(const void *, void *)) rank);
   return 0;
}
