#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
  Standart linear congruential generator;
  Suggestion in the ISO/IEC 9899 / modification;
*/

uint32_t seed = 1;

const uint32_t c =      12345;
const uint32_t m = 0x7FFFFFFF;
const uint64_t a = 1103515245;

uint32_t xrandom(void) {
  seed = (uint32_t)((a * seed + c) % m);
  return seed;
}

void xrange(uint32_t next) {
  seed = next;
}

void printerr(char * msg) {
  printf("[!] Argument \"%s\" not correct number!\n", msg);
}

int main(int argc, char * argv[]) {

  uint32_t count, next; /* NOT initialized 32-bits memory */

  if (1 == argc) {
    count = m ^ next; /* next имеет значение из стека; так и должно бытЬ */
    next  = (uint32_t)time(NULL);
  }
  else
  if (3 == argc) {
    next  = atol(argv[1]);
    count = atol(argv[2]);

    if (next == 0) {
      printerr(argv[1]);
      return (-1);
    }

    if (count == 0) {
      printerr(argv[2]);
      return (-1);
    }
  }
  else {
    printf("[!] Enter: %s [seed] [count]\n", argv[0]);
    return (-1);
  }
    
  xrange(next);
      
  if (argc > 1) {
    while(count--) {
      putc(xrandom(), stdout);
    }
  }
  else {
    while(count) {
      putc(xrandom(), stdout);
    }
  }

  return 0;
}
