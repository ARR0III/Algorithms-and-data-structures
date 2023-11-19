#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

void quicksort(unsigned int * data, unsigned int min, unsigned int max) {
  unsigned int i, j, t, m;

  if (min >= max) return;
  
  i = min;
  j = max;
  m = data[(min + max) >> 1];

  do {
    while (data[i] < m) i++;  
    while (data[j] > m) j--;
        
    if (i <= j) {
      t = data[i];
      data[i] = data[j];
      data[j] = t;

      i++;
      j--;
    }

  } while (i <= j);

  quicksort(data, min, j);
  quicksort(data, i, max);
}

int main (void) {
  unsigned int i;
  unsigned int * data = (unsigned int *)malloc(N * sizeof(unsigned int));

  if (NULL == data) {
    exit(1);
  }

  srand(time(NULL));

  for (i = 0; i < N; i++) {
    data[i] = rand() % N;
  }

  quicksort(data, 0, N-1);

  for (i = 0; i < N; i++) {
    printf("%5u%c", data[i], (i + 1) % 8 ? '\t' : '\n');
  }

  free(data);

  return 0;
}
