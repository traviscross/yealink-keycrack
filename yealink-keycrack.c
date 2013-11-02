#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <strings.h>

//static char ar1[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static char ar2[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
//static char ar3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
//static char ar4[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// See: http://rosettacode.org/wiki/Linear_congruential_generator
#define MS_RAND_MAX ((1U << 31) - 1)
static int ms_rseed = 0;
static inline void ms_srand(int x) {
  ms_rseed = x;
}
static inline int ms_rand() {
  return (ms_rseed = (ms_rseed * 214013 + 2531011) & MS_RAND_MAX) >> 16;
}

static char rchar(char *map) {
  int i = ms_rand() % 62;
  return map[i];
}

static char* rstr(char *guess, char *map) {
  int i;
  for (i=0; i<16; i++)
    guess[i] = rchar(map);
  //fprintf(stderr, "%s\n", guess);
  return guess;
}

int main(int argc, char **argv) {
  time_t t = time(NULL);
  unsigned int tu = (unsigned int)t, stop=++tu;
  char guess[17] = "";
  uint32_t c = 0;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <key>\n", argv[0]);
    return 255;
  }
  char *key = argv[1];
  while (1) {
    ms_srand(tu);
    //rstr(guess,ar1); if (!(strcasecmp(guess,key))) break;
    rstr(guess,ar2); if (!(strcasecmp(guess,key))) break;
    //rstr(guess,ar3); if (!(strcasecmp(guess,key))) break;
    //rstr(guess,ar4); if (!(strcasecmp(guess,key))) break;
    tu--; c++;
    if (!(c & 0x00ffffff))
      fprintf(stderr,"%d/256 done\n", (c>>24));
    if (tu==stop) break;
  }
  if (!(strcasecmp(guess,key))) {
    printf("Found key: %s generated at %u\n", guess, tu);
    return 0;
  } else {
    printf("Couldn't find key, giving up\n");
    return 1;
  }
}
