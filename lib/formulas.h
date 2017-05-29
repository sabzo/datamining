#include <stdlib.h>
#include <math.h>

/* Manhattan Distance |x1-x2| + |y1-y2|*/
short manhattan_distance(char *user1, char *user2, short size) {
  int i = 0;
  short score = 0;
  while (i++ < size)
    score += abs(*user1++ - *user2++);
  return score;
}

/* Euclidean Distance */
float euclidean_distance(char *user1, char *user2, short size) {
  int i = 0;
  float score = 0.0;
  while (i++ < size) {
    score += pow(*user1++ - *user2++, 2);      
  }
  return sqrt(score);
}
