#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int grand(const int min, const int max) {
  return min + (int)((double)max * rand() / (RAND_MAX + (double)min));
}

int main(int argc, char * argv[]) {
  int byte, min, max;
  char * hex_data = "0123456789abcdef";

  if (argc != 3) {
    fprintf(stderr, "[!] Necessary 2 numbers!\n");
    exit(-1);
  }

  min = atoi(argv[1]);

  if (!min) {
    fprintf(stderr, "[!] Number \"%s\" not number!\n", argv[1]);
    exit(-2);
  }

  max = atoi(argv[2]);

  if (!max) {
    fprintf(stderr, "[!] Number \"%s\" not number!\n", argv[2]);
    exit(-2);
  }

  srand(time(NULL));

  while (1) {
    byte = grand(min, max);
    putc(hex_data[(unsigned char)byte >>    4], stdout);
    putc(hex_data[(unsigned char)byte  & 0x0F], stdout);
  }

  return 0;
}