#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

int str_len(const char * str) {
  int i = 0;

  while(str[i]) i++;

  return i;
}

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

void swap(int * a, int * b) {
  int tmp = *a;
  
  *a = *b;
  *b = tmp;
}

void sort(char ** arr_str, int * arr_len, int size) {
  int i, j;
  int mp;

  char * tmp;

  for (i = 0; i < size-1; i++) {
    mp = i;

    for (j = i+1; j < size; j++) {
      if (arr_len[j] < arr_len[mp])
        mp = j;
    }

    if (mp > i) {
      swap(&arr_len[i], &arr_len[mp]);

      tmp         = arr_str[i];
      arr_str[i]  = arr_str[mp];
      arr_str[mp] = tmp;
    }
  }
}

int sort_complete(int * arr_len, int size) {
  int i;

  for (i = 0; i < size-1; i++) {
    if (arr_len[i] > arr_len[i+1]) {
      return FALSE;
    }
  }

  return TRUE;
}

/* toporno i ne krasivo schtob ego; pervoe chto proschlo v golovu */
void str_sort(char ** arr_str, int qu) {

  int   i;
  int * arr_len = (int *)malloc(sizeof(int) * qu);

/* length all string from array pointers */
  for (i = 0; i < qu; i++) {
    arr_len[i] = str_len(arr_str[i]);
  }

/* sort length string and swap pointers */
  sort(arr_str, arr_len, qu);

/* compire and sort strings */
  do {
    for (i = 0; i < qu-1; i++) {
      arr_len[i] = str_cmp(arr_str[i], arr_str[i+1]);
      printf("---- %d ----\n", arr_len[i]);
    }

    arr_len[qu-1] = -arr_len[qu-2];
    printf("---- %d ----\n", arr_len[qu-1]);

    sort(arr_str, arr_len, qu);
  } while (sort_complete(arr_len, qu));

  free(arr_len);
}

/* gcc -Wall -O3 str_sort.c -o str_sort */
int main(int argc, char * argv[]) {

  int    i, n;
  char * strv[10];

  if (argc == 1) {
    printf("Enter strings!\n");
    return 1;
  }

  i = 0;
  while (argv[i+1] && i < 10) {
    strv[i] = argv[i+1];
    i++;
  }

  n = i;

  str_sort(strv, i);

  i = 0;
  while (1) {
    if (i == n) break;

    printf("%s\n", strv[i]);
    i++;
  }

  return 0;
}









