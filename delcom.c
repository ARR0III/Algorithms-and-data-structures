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

  FILE *fin;
  int   i, read;

  int   pos_begin = 0;
  int   pos_end   = 0;
  int   length    = 0;

  int   comment   = FALSE;
  int   strings = 0;

  char  data[BLOCK_SIZE] = {0};

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
    pos_begin = 0;
    pos_end   = 0;

    read = str_read(fin, data, BLOCK_SIZE);
    
    if (read == 0) break;

    strings++;

    if (read == BLOCK_SIZE) {
      fprintf(stderr, "[!] %8d: string length more %d.\n", strings, BLOCK_SIZE);
      break;
    }

   /*
    * find bounders comment
    */
    for (i = 0; i < read-1; i++) {
      if (comment == FALSE && data[i] == '/' && data[i+1] == '*') {
        pos_begin = i;
        length    = 2;
        comment   = TRUE;
        continue;
      }

      if (comment == TRUE && data[i] == '*' && data[i+1] == '/') {
        pos_end = i+1;
        comment = FALSE;
        length += 2;
        break;
      }

      if (comment) length++;
    }

    if (comment) { /* in comment */
      continue;
      length = 0;
    }

    if (length >= 4) {
      fwrite(data, 1, pos_begin, stdout);
      fwrite(data + pos_end + 1, 1, read - pos_end - 1, stdout);
    }
    else {
      fwrite(data, 1, read, stdout);
    }

    length = 0;

    /**************************************************************************
    real comment found ???

    if ((pos_end - pos_begin) >= 3) {
      if (data[pos_begin + 1] == '*' && data[pos_end - 1] == '*') {
        fwrite(data, 1, pos_begin ? pos_begin - 1 : 0, stdout);
        fwrite(data + pos_end + 1, 1, read - pos_end, stdout);

        continue;
      }
    }

    write full buffer --> comment not found
    fwrite(data, 1, read, stdout);

    **************************************************************************/
  }

  return 0;
}



