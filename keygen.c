#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <time.h>

int genrand(const int min, const int max) {
  return (int)(rand() % (max - min + 1) + min);
}

#define USERNAME_SIZE 33

int main(int argc, char* argv[]) {
  unsigned char username[USERNAME_SIZE];

  uint32_t tmp;
  uint32_t res, i;
  uint32_t dec, sec = 0;
  uint32_t username_len = 0;

  srand(time(0));

  memset((void *)username, 0x00, USERNAME_SIZE);

  printf("Please, enter your username:");
  fgets((char *)username, USERNAME_SIZE - 1, stdin);

  if (username[0] == 0x00) {
    printf("Username length correct min 1 and max 32 symbols.\n");    
    return -1;
  }

  username_len = strlen(username);

  for (i = 0; i < username_len; i++) {
    sec  += ((uint32_t)(username[i])) << 8;
    sec  += 0x0000CD8A;
    sec  += 1;
  }

  printf("Control sum your username: %ld\n", sec);

  int count = 8;

  while (count--) {
    dec = sec;
    i = 0;

    while (i < 8*3) {
      if (tmp & 3) {
        tmp = (uint32_t)genrand('A', 'Z');
      }
      else {
        tmp = (uint32_t)genrand('0', '9');
      }

      res  = (tmp + dec + i);

      if ((tmp % 3) && (res % 3)) {
        dec += i + 1;
        printf("%C", tmp);

        if (i == (8*3-1)) {
          printf("\n");
          break;
        }
        else
        if (((i + 1) % 8) == 0)
          printf("-");

        i++;
      }
    }
  }

  return 0;
}
