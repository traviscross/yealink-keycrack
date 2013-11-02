#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static char key[] = "ljB7jiDIQQ7XD888";
static char ar1[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static char ar2[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char ar3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static char ar4[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

#define MS_RAND_MAX ((1U << 31) - 1)
static int ms_rseed = 0;
inline void ms_srand(int x) {
  ms_rseed = x;
}

inline int ms_rand() {
  return (ms_rseed = (ms_rseed * 214013 + 2531011) & MS_RAND_MAX) >> 16;
}

char rchar(char *map) {
  int i = ms_rand() % 62;
  return map[i];
}

char* rstr(char *guess, char *map) {
  int i;
  for (i=0; i<16; i++)
    guess[i] = rchar(map);
  //fprintf(stderr, "%s\n", guess);
  return guess;
}

int main(int argc, char **argv) {
  time_t t = time(NULL);
  char guess[17] = "";
  long int c = 0;
  while (t>(t-315360000)) {
    ms_srand((unsigned int)t);
    //rstr(guess,ar1); if (!(strcasecmp(guess,key))) break;
    rstr(guess,ar2); if (!(strcasecmp(guess,key))) break;
    //rstr(guess,ar3); if (!(strcasecmp(guess,key))) break;
    //rstr(guess,ar4); if (!(strcasecmp(guess,key))) break;
    t--; c++;
    if (!(c%2592000))
      fprintf(stderr,"Checked back %d months\n", c/2592000);
  }
  if (!(strcasecmp(guess,key))) {
    printf("Found key: %s generated at %d\n", guess, t);
    return 0;
  } else {
    printf("Couldn't find key, giving up\n");
    return 1;
  }
}
