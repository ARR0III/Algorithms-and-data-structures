#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void radix_sort(uint8_t * data, size_t size) {
  size_t i, ps0, ps1;

  uint8_t   k = 0;
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

  /* optimization ??? */
  /* search and set high bit in numbers array */
  for (i = 0; i < size; i++) {
    k = k | data[i];

    if (k & 0x80)
      break;
  }

  /* optimization ??? */
  /* search first 1 bit in number */
  i = 8 - 1;

  while (i >= 0) {
    if ((k >> i) & 1) {
      break;
    }

    if (i == 0) {
      break;
    }

    i--;
  }

  /* optimization ??? */
  /* k = (width number bits) - (position 1 bit in number) */
  k = 8 - (8 - (i + 1));

  printf("Original algoritm     O(N * r)         = %d\n"
         "Optimization algoritm O(N * k + N + r) = %d\n",
          size * 8,
          size * k + size + 8);

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

    if ((k == 0) || (r & 0x80)) {
      break;
    }

    r <<= 1;
    k--;
  }

  free(p[0]);
  free(p[1]);
}

int main(void) {
  int i;
  uint8_t d[20] = {17,8,11,4,7,5,10,1,15,0,2,12,3,9,13,16,6,14,19,18};

  radix_sort(&d[0], 20);

  for (i = 0; i < 20; i++)
    printf("%3d%c", d[i], i == 19 ? '\n' : ' ');

  return 0;
}

