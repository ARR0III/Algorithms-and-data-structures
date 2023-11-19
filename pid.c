#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int n, i;
  gid_t * p;

  n = getgroups(0, NULL);
  
  if (n == -1 || n == 0) {
    printf("[!] Groups counter: %d\n", n);
    exit(1);
  }
  
  p = (gid_t *)malloc(n * sizeof(gid_t));

  getgroups(n, p);

  for (i = 0; i < n; ++i) {
    printf("GROUP [%4d]:%8u\n", i, p[i]);
  }

  return 0;
}


