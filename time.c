#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  time_t my_time;
  struct tm * s_tm;
  char data[80] = {0x00};
  int pid;

  my_time = time(NULL);
  s_tm = localtime(&my_time);

  pid = fork();
  
  if (pid == -1) {
    perror("fork");
    exit(1);
  }

  if (pid == 0) { /* process sleeping 5 seconds */
    int priority = nice(-10);
    sleep(5);

    if (priority != -10) {
      printf("I\'am NOT ADMINISTRATOR!\n");
    }

    printf("\nI\'am forked!\n");
    strftime(data, 79, "%A, %d %B %Y, %R\n", s_tm);
    printf("%s\n", data);
    exit(0);
  }

  printf("STR:\t%s\n", asctime(s_tm));

  printf("Day:\t%d\n"
	 "Mon:\t%d\n"
	 "Year:\t%d\n",
          0    + s_tm->tm_mday,
	  1    + s_tm->tm_mon,
	  1900 + s_tm->tm_year);

  wait(NULL);

  return 0;
}

