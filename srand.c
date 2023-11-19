#include <stdio.h>

int main (int argc, char * argv[]) {
  int c = 0;
  int min, max;  


  if (argc != 3) {
    printf("[!] Incorrect count arguments!\n");
    return -1;
  }

  min = argv[1][0];
  max = argv[2][0];

  while (1) {
    c = getchar();
    if (EOF == c) break;

    if (c >= min && c <= max) putchar(c);
  }

  return 0;
}
