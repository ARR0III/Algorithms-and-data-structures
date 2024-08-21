#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

size_t str_len(const char * str) {
  size_t i = 0;

  while(str[i]) i++;

  return i;
}

void swap(size_t * a, size_t * b) {
  size_t tmp = *a;
  
  *a = *b;
  *b = tmp;
}

void sort(char ** arr_str, size_t * arr_len, size_t size) {
  size_t i, j;
  size_t mp;

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

/* toporno i ne krasivo schtob ego; pervoe chto proschlo v golovu */
void str_sort(char ** arr_str, size_t qu) {
  size_t i, j, p, k;
  size_t begin, end;
  size_t * arr_len = (size_t *)malloc(sizeof(size_t) * qu);

  size_t len;
  int crash_sort = FALSE;

/* length all string from array pointers */
  for (i = 0; i < qu; i++) {
    arr_len[i] = str_len(arr_str[i]);
  }

/* sort length string and swap pointers */
  sort(arr_str, arr_len, qu);

/* sort strings */

  begin = 0;
  end   = 0;

  while(begin < qu) {
    for (i = begin; i < qu-1; i++) {
      if (arr_len[i+1] > arr_len[begin]) {
        end = i;
        break;
      }
    }

    if (begin == end) {
      begin++;
      continue;
    }

    if (begin < end) {
      len = arr_len[end];

      for (j = 0; j < len; j++) {
        for (k = begin; k < end; k++) {
          
        }
      }
    }

    begin = begin + end;
  }

  free(arr_len);
}

int main(int argc, char * argv[]) {

  int i, n;
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









