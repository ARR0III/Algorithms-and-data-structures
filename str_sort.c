#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

int str_cmp(const char * a, const char * b) {
  int i = 0;
  const char *aa = a;
  const char *bb = b;

  while (*aa && *bb) {
    if (*aa != *bb) {
      i = *aa - *bb;
      break;
    }

    aa++;
    bb++;
  }

  if (i != 0) return i;

  if (*aa) {
    while (*aa) {
      aa++;
      i++;
    }
    return i;
  }

  while (*bb) {
    bb++;
    i--;
  }

  return i;
}

void str_sort(char ** arr_str, int qu) {
  int    i, swp;
  char * tmp;

  while (1) {
    swp = FALSE;
    i   = 0;

    while (i < qu-1) {
      if (str_cmp(arr_str[i], arr_str[i+1]) > 0) {
        tmp          = arr_str[i];
        arr_str[i]   = arr_str[i+1];
        arr_str[i+1] = tmp;
        swp = TRUE;
      }
      i++;
    }

    qu--;

    if (!swp) break;
  }
}

/* gcc -Wall -O3 str_sort.c -o str_sort */
int main(int argc, char * argv[]) {

  int i;

  if (argc < 2) {
    printf("Enter strings!\n");
    return 1;
  }

  str_sort(&argv[1], argc-1);

  i = 1;
  while (1) {
    if (i == argc) break;

    printf("%s\n", argv[i]);
    i++;
  }

  return 0;
}
