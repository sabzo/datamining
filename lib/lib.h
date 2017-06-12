#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#define HASHSIZE 101
#define MAXVALUES 100
#define MAXLINE 1000
#define MAXDISTANCES 1000
#define MAXLINEWORDS 20
#define MAXRECOMMENDATIONS 10
#define UIDSIZE 4
// Create a Custom Hahs Type
#define HASH(name, type_key, type_next, type_obj, size)  \
  typedef struct name { \
    type_key key; \
    type_obj *value; \
    char v_it; /*value array position iterator */ \
    type_next *next; \
  } name; \
  type_next *_##name##_hash[HASHSIZE];\
 \
/* Get position in Hash array based on key */ \
unsigned int _##name##_hashpos(type_key _name) { \
  unsigned hashval = 0; \
  char c; \
  while ((c = *_name++) != '\0') \
    hashval = c + 31 * hashval; \
  return hashval % HASHSIZE; \
} \
  /* Find the object if it exists in the hash */ \
type_next *_##name##_find(type_key key) { \
  type_next *hp; \
  for (hp = _##name##_hash[_##name##_hashpos(key)]; hp != NULL; hp = hp->next) \
    if (strcmp(key, hp->key) == 0) \
      return hp; \
    return NULL; \
} \
  /* Add a new object to Hash. If it exists append its value array */ \
type_next *_##name##_add(type_key key, type_obj value) { \
  name *hp; \
  unsigned int hpos; \
  int hkey; \
  if ((hp = _##name##_find(key)) == NULL) { /* not found */ \
    if ((hp = (name *) malloc(sizeof(*hp))) != NULL) { \
      hkey = _##name##_hashpos(key); \
      hp->key = key; \
      hp->v_it = 0; /* the value array is now initialized with 1 object */ \
      hp->value = calloc(MAXVALUES + 1, sizeof(type_obj)); /* zero fill + 1 off to use as sentinel */\
      hp->value[hp->v_it++] = value; \
      hp->next = _##name##_hash[hkey]; \
      _##name##_hash[hkey] = hp; \
    }\
  } else {/* Found item */ \
    if (hp->v_it < MAXVALUES) \
      hp->value[hp->v_it++] = value; \
  } \
  return hp; \
} \
  /* Remove an Object from the hash */ \
type_next *_##name##_remove(type_key key) { \
  name *prev, *curr; \
  int hkey = _##name##_hashpos(key); \
  int removed = 0; \
  for (prev = curr = _##name##_hash[hkey]; curr != NULL; curr = curr->next) { \
    if (strcmp(key, curr->key) == 0) { \
      prev->next = curr->next; \
      free(curr); \
      removed = 1; \
    } \
  } \
  return 0; \
}

typedef struct distance {
  char *key;
  float distance;
} distance;

typedef struct rating {
  char *key;
  float score;
} rating;

// Searches for a value in specified array
// TODO Better implementation would be to use a HASH but at moment not interested
int in_rating_array(rating target, rating *ratings) {
  int i = 0;
  while (ratings != NULL && ratings->key != NULL) {
    if ((strcmp(target.key, ratings++->key) == 0))
      return i;
    i++;    
  }
  return -1;
}

/* Manhattan Distance |x1-x2| + |y1-y2|*/
short manhattan_distance(rating *r1, rating *r2) {
  int i = 0;
  short score = 0;
  int pos = 0;
  while (r1 != NULL && r1->key != NULL && r2 != NULL && r2->key != NULL) { 
    if ((pos = in_rating_array(*r1, r2)) != -1) 
      score += fabs(r1->score - (r2 + pos)->score);
    r1++;
  }
  return score;
}

/* Euclidean Distance */
float euclidean_distance(rating *r1, rating *r2) {
  float score = 0.0;
  int i = 0;
  int pos = 0;
  while ( r1 != NULL && r1->key != NULL && r2 != NULL && r2->key != NULL) { 
    if ((pos = in_rating_array(*r1, r2)) != -1) 
      score += pow(r1->score - (r2 + pos)->score, 2);     
    r1++;
  }
  return sqrt(score);
}

void error_creating (char*name) {
  printf("Error creating %s\n", name);
  exit(1);
}

void error (char *msg) {
  printf("%s\n", msg);
  exit(1);
}

void usage(char *progname) {
  printf("Usage: %s <ratings csv file> \n", progname);
  exit(0);
}

int get_num_lines(char *filename) {
  FILE *fp;
  char line[MAXLINE];
  int count = 0;
  if ((fp = fopen(filename, "r")) != NULL) 
    while (fgets(line, MAXLINE, fp) != NULL)
      count++;  
  return count;
}

/* Returns an Array of words. Remember to Free Array after use */
char ** delim(char *str, char delim) {
  int num_words = 0;
  char char_counter = 0; // num of chars in word
  char wordsize[MAXLINEWORDS];
  char c;
  int pos = 0;
  int str_ptr_offset = 0;
  // Determine how many delimetered words there are
  while (++str_ptr_offset && (c = *str++) != '\0' && c != '\n' && ++char_counter <= MAXLINEWORDS) {
        if (c == delim || *str == '\0' || *str == '\n') {
          if (c == delim)             
            char_counter = char_counter - 1;   // don't count delimeter as a letter
	  num_words++;
	  wordsize[pos++] = char_counter;
	  char_counter = 0; 
	}
  }
  str -= str_ptr_offset;
  // allocate words of words
  char **words = malloc(num_words * sizeof(char *));
  // allocate for each word in list
  for (pos = 0; pos < num_words; pos++)
	*words++ = malloc(wordsize[pos] * sizeof(char *));
  words -= pos; // *words temporarily goes to dangerous territory array overbound. On a separate note resetting so word can start from first letter	
  char_counter = 0;
  while ((c = *str++) != '\0' && c != '\n') {
    if (c == delim) {
      **words = '\0'; // complete word creation
      *words = *words - char_counter;
      char_counter = 0;
      words++; // next word 
    }
	else {
	  (*(*words)++) = c; // **words = 'c' THEN *words++. 
          char_counter++;
        }
  }
  **words = '\0'; // End last word which has no delimeter after it
  *words = *words - char_counter;
  words -= pos-1; // Note: this time *word didn't go off by 1 but pos is still off by 1, so subtract 1 to error correct
  return words;
}

/* Recommend 
 ** Similarity()
  - Finds similarity of this to that

 ** Rank(heuristic, elements)
  - heurist can be a function or an object
  - elements are elements needing to be ranked.
*/

void recommend(void *result, const void *this, const void **that, const int len_that, void *heuristic, void (*similarity)(void *result, const void *this, const void *that, const int len_that), void (*rank)(const void *heuristic, void *result)) {
  // Get similar items
  similarity(result, this, that, len_that); 
  // rank results
  rank(heuristic, result);
}

