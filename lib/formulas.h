#include <stdlib.h>

char manhattan_distance(char *user1, char *user2, char total) {
  int i = 0;
  char score = 0.0;
  while(i++ < total) {
    score += abs(*user1++ - *user2++);
  }
  return score;
}
