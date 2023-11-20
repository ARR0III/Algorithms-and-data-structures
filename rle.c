#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void){
  int      byte, tmp;
  uint32_t stat = 0;

  tmp = 0;

  while ((byte = getchar()) != EOF) {
    if (tmp == byte) {
      stat++;
      continue;
    }
    else {
      if (stat >= 6) {
        fprintf(stdout, "%u", stat);
        putchar(tmp);
      }
      else {
        while(stat--) {
          putchar(tmp);
        }
      }

      tmp = byte;
      stat = 1;
    }
  }

  return 0;
}

