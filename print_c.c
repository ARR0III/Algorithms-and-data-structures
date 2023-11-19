#include <stdio.h>
#include <stdarg.h>

void print_c(const char * str, ...) {
  va_list ap;
  int count;
  
  va_start(ap, str);
  
  for (const char * ps = str; NULL != ps; ps = va_arg(ap, const char *)) {
    count = va_arg(ap, int);
    
    while(count) {
      fputs(ps, stdout);
      count--;
    }
  }
  
  va_end(ap);
}

int main(void) {
  print_c("HELLO\n", 2, "MOTO\n", 10);
  return 0;
}
