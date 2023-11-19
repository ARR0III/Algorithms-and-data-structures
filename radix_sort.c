#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void radix_sort(uint8_t * data, size_t size) {
  size_t i, ps0, ps1;

  uint8_t   r;
  uint8_t * p[2];

  p[0] = (uint8_t *)malloc(size);
  p[1] = (uint8_t *)malloc(size);

  if (NULL == p[0] || NULL == p[1]) {

    if (p[0]) free(p[0]);
    if (p[1]) free(p[1]);
    
    exit(1);
  }

  r = 1;

  while (1) {
    ps0 = 0;
    ps1 = 0;

    for (i = 0; i < size; i++) {
      if (data[i] & r) {
        p[0][ps0] = data[i];

        ps0++;
      }
      else {
        p[1][ps1] = data[i];

        ps1++;
      }
    }

	memcpy(data,       p[1], ps1);
	memcpy(data + ps1, p[0], ps0);

    if (r & 0x80) {
      break;
    }

    r <<= 1;
  }

  free(p[0]);
  free(p[1]);
}

int main(void) {
  int i;
  uint8_t d[20] = {17,8,11,4,7,5,10,1,15,0,2,12,3,9,13,16,6,14,19,18};

  radix_sort(&d[0], 20);

  for (i = 0; i < 20; i++)
    printf("%d\t", d[i]);

  printf("\n");

  return 0;
}

