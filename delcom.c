#include <stdio.h>
#include <stdlib.h>

/* This program deleting comments from C language source code */

#define FALSE        0
#define TRUE         1

#define BLOCK_SIZE 128

int str_read(FILE * f, char * str, int bounder) {
  int data;
  int i = 0;

  if (f == NULL || !str || bounder == 0) {
    return 0;
  }

  while (1) {
    if (i >= bounder) break;

    data = fgetc(f);

    if (data == '\0' || data == EOF) {
      break;
    }

    str[i] = (char)data;
    i++;

    if (data == '\n') {
      break;
    }
  }

  return i;
}

int main(int argc, char * argv[]) {

  FILE  *fin;
  int    i, read;

  int    comment = FALSE;
  size_t strings = 0;

  char   data[BLOCK_SIZE] = {0};

  if (argc != 2) {
    fprintf(stderr, "[!] Enter: %s [filename]\n", argv[0]);
    return 1;
  }

  fin = fopen(argv[1], "rb");

  if (!fin) {
    fprintf(stderr, "[!] File %s not openned.\n", argv[1]);
    return 2;
  }

  while (1) {
    read = str_read(fin, data, BLOCK_SIZE);
    
    if (read == 0) break;

    strings++;

    if (read == BLOCK_SIZE) {
      fprintf(stderr, "[!] %8d: string length more %d\n", strings, BLOCK_SIZE);
      break;
    }

   /*
    * find bounders the comment in string
    */
    for (i = 0; i < read-1; i++) {
      if (comment == FALSE && data[i] == '/' && data[i+1] == '*') {
        comment = TRUE;
        i++;
        continue;
      }

      if (comment == TRUE && data[i] == '*' && data[i+1] == '/') {
        comment = FALSE;
        i++;
        continue;
      }

      if (!comment) {
        putchar(data[i]);
      }
    }

    if (!comment) {
      putchar('\n');
    }
  }

  putchar('\n');

  fclose(fin);

  return 0;
}



