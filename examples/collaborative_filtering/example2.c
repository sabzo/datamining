/* Example for determining Manhattan and Euclidean Distances between a CSV list of users and associated ratings. 
The idea is the shorter distance between two users means the users have similar
preferences */

#include <stdio.h>
#include "../../lib/lib.h"
 
// Create Hash, from macro expansion, for storing users and their ratings
HASH(user, char *, struct user, rating, HASHSIZE)

int main(int argc, char *argv[]) {

  FILE *fp;
  char line[MAXLINE]; // each line
  char *filename; 
  char *uid = NULL; // user id 
  user *u;

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
   return 0;
}
