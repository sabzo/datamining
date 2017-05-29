#include <string.h>
#include <stdlib.h>
#include <math.h>
#define HASHSIZE 101

typedef struct user { 
  char *key;
  char *value;
  struct user *next;
} user;

typedef struct rating {
  char *key;
  short score;
} rating;
  
struct user *hash[HASHSIZE];

/* Hash Algorithm from K&R */
unsigned int hashpos(char *name) {
  unsigned hashval = 0;
  char c;
  while ((c = *name++) != '\0')
    hashval = c + 31 * hashval;
  return hashval % HASHSIZE;
}

/* Lookup Obj */
user *hashfind(char *key) {
  struct user *hp;
  for (hp = hash[hashpos(key)]; hp != NULL; hp = hp->next)
    if (strcmp(key, hp->key) == 0)
      return hp;
    return NULL;
}

/* add to hashtable */
/* ideally type of value should be void/anything */
user *hashadd(char *key, char *value) {
  user *hp;
  unsigned int hpos;
  int hkey;

  if ((hp = hashfind(key)) == NULL) { /* not found */
    if ((hp = (user *) malloc(sizeof(*hp))) != NULL) {
      hkey = hashpos(key);      
      hp->key = key;
      hp->value = value;
      hp->next = hash[hkey];
      hash[hkey] = hp;
    }
  } else /* Found item */ 
     if((hp->value = value) == NULL) 
       return NULL;

  return hp;
}

/* Remove value from Hash if there */
user *hashremove(char *key) {
  user *prev, *curr;
  int hkey = hashpos(key);
  int removed = 0;
  for (prev = curr = hash[hkey]; curr != NULL; curr = curr->next) {
    if (strcmp(key, curr->key) == 0) {
      prev->next = curr->next;
      free(curr);
      removed = 1;                     
    }
  }
  return 0;
}

/* Manhattan Distance |x1-x2| + |y1-y2|*/
short manhattan_distance(char *user1, char *user2, short size) {
  int i = 0;
  short score = 0;
  while (i++ < size) {
  // if there are no corresponding values -- indicated by 0 skip score addition
    if (*user1 != 0 && *user2 != 0)
      score += abs(*user1 - *user2);
    user1++; 
    user2++;
  }
  return score;
}

/* Euclidean Distance */
float euclidean_distance(char *user1, char *user2, short size) {
  int i = 0;
  float score = 0.0;
  while (i++ < size) {
    if (*user1 != 0 && *user2 != 0)
      score += pow(*user1 - *user2, 2);      
    user1++;
    user2++;
  }
  return sqrt(score);
}

void error_creating (char*name) {
  printf("Error creating %s\n", name);
  exit(1);
}
