#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  int number;
  struct stack * prev;

} stack_t;

void stack_free(stack_t ** stack) {
  stack_t * tmp;

  while(*stack) {
    tmp = *stack;
    *stack = (*stack)->prev;
    free(tmp);
  }
}

void stack_push(stack_t ** stack, int number) {
  stack_t * tmp = (stack_t *)malloc(sizeof(stack_t));

  if (!tmp)
    exit(1);

  tmp->number = number;
  tmp->prev = *stack;
  *stack = tmp;
}

void stack_pop(stack_t ** stack, int * number) {
  if (NULL == *stack) return;

  stack_t * tmp = *stack;

  *number = (*stack)->number;
  *stack = (*stack)->prev;

  free(tmp);
}

#define  FALSE  0
#define  TRUE   1

/*
  ./str_math "434693463762395724962432 +-+-++++****+++-/+-+/++"  --> 328
*/

int main(int argc, char * argv[]) {

  stack_t * stack = NULL;

  int i;
  int len;
  int number = 0;
  int tmp;

  char * str = argv[1];

  if (argc < 2) {
    printf("[!] Enter: %s [command]\n", argv[0]);
    return 1;
  }

  len = strlen(argv[1]);

  for (i = 0; i < len; i++) {
    if (str[i] == ' ') {
      continue;
    }

    if (str[i] >= '0' && str[i] <= '9') {
      stack_push(&stack, str[i] - '0');
      continue;
    }

    if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
      if (!stack) {
        printf(">>Stack are enpty!\n");
        exit(1);
      }

      stack_pop(&stack, &number);

      if (!stack) {
        printf(">>Stack are enpty!\n");
        exit(1);
      }

      switch(str[i]) {
        case '+':
          tmp = number + stack->number;
          printf(">>(%8d + %d) = %d\n", number, stack->number, tmp);
          stack->number = tmp;
          break;
        case '-':
          tmp = number - stack->number;
          printf(">>(%8d - %d) = %d\n", number, stack->number, tmp);
          stack->number = tmp;
          break;
        case '*':
          tmp = number * stack->number;
          printf(">>(%8d * %d) = %d\n", number, stack->number, tmp);
          stack->number = tmp;
          break;
        case '/':
          if (number == 0) {
            stack_free(&stack);
            printf(">>Div by zero!\n");
            exit(1);
          }
          tmp = number / stack->number;
          printf(">>(%8d / %d) = %d\n", number, stack->number, tmp);
          stack->number = tmp;
          break;
      }
    }
  }

  if (!stack) {
    printf(">>Stack are enpty!\n");
    exit(1);
  }

  printf(">>(%s) = %d\n", str, stack->number);

  stack_free(&stack);

  return 0;
}














