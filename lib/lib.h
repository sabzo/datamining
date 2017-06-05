#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define HASHSIZE 101
#define MAXMOVIES 100

// Create a Custom Hahs Type
#define HASH(name, type_key, type_next, type_obj, size) \
  typedef struct name { \
    type_key key; \
    type_obj value; \
    type_next *next; \
  } name; \
  type_next *_##name##_hash[HASHSIZE];\
  type_next hash_##name##_add (type_key hash, type_key key, type_obj obj) { \
    type_next test; \
    return test; \
  }

typedef struct distance {
  char *key;
  float distance;
} distance;

typedef struct rating {
  char *key;
  float score;
} rating;

HASH(user, char *, struct user, rating *, HASHSIZE)
  
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
user *hashadd(char *key, rating *value) {
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
short manhattan_distance(rating *r1, rating *r2) {
  int i = 0;
  short score = 0;
  while ( r1 != NULL && r1->key != NULL && r2 != NULL && r2->key != NULL) 
    if (strcmp(r1->key, r2->key) == 0) 
      score += abs((r1++)->score - (r2++)->score);

  return score;
}

/* Euclidean Distance */
float euclidean_distance(rating *r1, rating *r2) {
  float score = 0.0;
  while ( r1 != NULL && r1->key != NULL && r2 != NULL && r2->key != NULL) 
    if (strcmp(r1->key, r2->key) == 0) 
      score += pow((r1++)->score - (r2++)->score, 2);     
  
  return sqrt(score);
}

/*
int in_array(rating target, rating *ratings) {
  int i = 0;
  while(*(ratings + i) != NULL) 
    if ((strcmp(target->key, (ratings + i)->key) == 0))
     return 1;
   return 0;
}
*/

void error_creating (char*name) {
  printf("Error creating %s\n", name);
  exit(1);
}
