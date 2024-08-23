#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

#define FALSE         0
#define TRUE          1

#define STACK_SIZE (4)

typedef struct stack {
  int    number[STACK_SIZE];
  size_t counter;

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

void stack_new(stack_t ** stack, int number) {
  stack_t * tmp = (stack_t *)malloc(sizeof(stack_t));

  if (NULL == tmp) {
    stack_free(stack);
    exit(1);
  }

  tmp->number[0] = number;
  tmp->counter   = 1;
  tmp->prev      = *stack;
  *stack         = tmp;
#ifdef DEBUG
    printf("[O_DEBUG] addr:%p; data:%d; counter:%d\n",
           &((*stack)->number[0]), number, (*stack)->counter);
#endif
}

void stack_push(stack_t ** stack, int number) {
  if (*stack && (*stack)->counter < STACK_SIZE) {
    (*stack)->number[(*stack)->counter] = number;
#ifdef DEBUG
    printf("[O_DEBUG] addr:%p; data:%d; counter:%d\n",
           (char*)((*stack)->number) + (*stack)->counter, number,
                   (*stack)->counter+1);
#endif
    (*stack)->counter++;
    return;
  }

  stack_new(stack, number);
}

void stack_pop(stack_t ** stack, int * number) {
  stack_t * tmp;

  if (NULL == *stack) return;

  if (0 == (*stack)->counter) {
    tmp = (*stack)->prev;
    free(*stack);
    *stack = tmp;
  }

  if (NULL == *stack) return;

  *number = (*stack)->number[(*stack)->counter-1];
#ifdef DEBUG
    printf("[O_DEBUG] addr:%p; data:%d; counter:%d\n",
           (char*)((*stack)->number) + (*stack)->counter - 1, *number,
                   (*stack)->counter-1);
#endif
  (*stack)->counter--;
}

/*
  ./str_math "98765432123456789+*+/++*+-+*+-+++" --> 65
*/

int main(int argc, char * argv[]) {

  stack_t * stack = NULL;

  int number = 0;
  int i, len, result;

  int  * tmp;
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

      tmp = &(stack->number[stack->counter-1]);

      switch(str[i]) {
        case '+':
          result = *tmp + number;
          break;
        case '-':
          result = *tmp - number;
          break;
        case '*':
          result = *tmp * number;
          break;
        case '/':
          if (number == 0) {
            stack_free(&stack);
            printf(">>Div by zero!\n");
            exit(1);
          }
          result = *tmp / number;
          break;
      }

      printf(">>(%d %c %8d) = %d\n", *tmp, (char)str[i], number, result);
      *tmp = result;
    }
  }

  if (stack) {
    printf(">>(%s) = %d\n", str, *tmp);
    stack_free(&stack);
  }

  return 0;
}

