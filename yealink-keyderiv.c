#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

static char ar[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

#define MS_RAND_MAX ((1U << 31) - 1)
static int ms_rseed = 0;
inline void ms_srand(int x) {
  ms_rseed = x;
}
inline int ms_rand() {
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
  return guess;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <time>\n", argv[0]);
    return 255;
  }
  unsigned long int t = strtoul(argv[1], NULL, 10);
  ms_srand((unsigned int)t);
  char guess[17] = "";
  rstr(guess,ar);
  printf("%s\n",guess);
}
