#include <string.h>
#include <stdlib.h>
#define HASHSIZE 101

typedef struct hash {
  char *key;
  char *value;
  struct hash *next;
} mhash;

struct hash *hash[HASHSIZE];

/* Hash Algorithm from K&R */
unsigned int hashpos(char *name) {
  unsigned hashval = 0;
  char c;
  while ((c = *name++) != '\0')
    hashval = c + 31 * hashval;
  return hashval % HASHSIZE;
}

/* Lookup Obj */
mhash *hashfind(char *key) {
  struct hash *hp;
  for (hp = hash[hashpos(key)]; hp != NULL; hp = hp->next)
    if (strcmp(key, hp->key) == 0)
      return hp;
    return NULL;
}

/* add to hashtable */
/* ideally type of value should be void/anything */
mhash *hashadd(char *key, char *value) {
  mhash *hp;
  unsigned int hpos;
  int hkey;

  if ((hp = hashfind(key)) == NULL) { /* not found */
    if ((hp = (mhash *) malloc(sizeof(*hp))) != NULL) {
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
mhash *hashremove(char *key) {
  mhash *prev, *curr;
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
