#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <termios.h>

#define OK       0
#define ERR_TERM 1
#define ERR_EOF  2

#define PASSWORD_STR "12439524"

enum {buffer_size = 256};

int main(void) {
  int i;
  struct termios trms, trms_ld;
  char pass[buffer_size];

  memset(pass, 0x00, buffer_size);

  if (!isatty(0)) {
    fprintf(stderr, "Not a terminal, sorry...\n");
    return ERR_TERM;
  }

  tcgetattr(0, &trms);                   /* get settings termios system */
  memcpy(&trms_ld, &trms, sizeof(trms)); /* copy normal settings */
  trms.c_lflag &= ~ECHO;                 /* flush flag ECHO */
  tcsetattr(0, TCSANOW, &trms);          /* set new settings */

  printf("[$] Enter password:");

  if (!fgets(pass, sizeof(pass), stdin)) {
    fprintf(stderr, "Unexpected end of file.\n");
    return ERR_EOF;
  }

  for (i = 0; i < buffer_size; i++) {
    if ('\n' == pass[i]) {
      pass[i] = '\0';
    }
  }

  if (strcmp(pass, PASSWORD_STR) == 0) {
    printf("\nThe code you entered is \"%s\"\n", pass);
  }
  else {
    printf("[X] Password wrong!\n");
  }

  tcsetattr(0, TCSANOW, &trms_ld); /* reability settings */

  return OK;
}

