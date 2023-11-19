#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

typedef struct stack {
  int number;
  struct stack * prev;
} stack_t;

void push_stack(stack_t ** stack, int number) {
  stack_t * tmp = malloc(sizeof(stack_t));

  if (!tmp) exit(2);

  tmp->number = number;
  tmp->prev   = *stack;
  *stack      = tmp;
}

int pop_stack(stack_t ** stack) {
  int number;
  stack_t * tmp;

  number = (*stack)->number;
  tmp    = (*stack)->prev;

  free(*stack);
  *stack = tmp;

  return number;
}

stack_t * stack_search(stack_t ** stack,  int number) {
  stack_t * tmp = *stack;

  while (tmp) {
    if (tmp->number == number)
      return tmp;

    tmp = tmp->prev;
  }

  return NULL;
}

/* I don't understand HOW this SHIT works! */
void stack_node_delete(stack_t ** stack,  int number) {
  while (*stack) {
    if ((*stack)->number == number) {
      stack_t * tmp = *stack;
      *stack = (*stack)->prev;
      free(tmp);
    }
    else {
      stack = &((*stack)->prev);
    }
  }
}

int stack_empty(stack_t ** stack) {
 return *stack == NULL;
}

int main(void) {
  int number;
  int counter = 0;

  stack_t * stack = NULL;

  while (scanf("%d", &number) == 1) {
    push_stack(&stack, number);
    counter++;
  }

  printf("search number for delete:");
  fflush(stdout);

  if (scanf("%d", &number) != 1) {
    printf("[!] Not number!\n");
    exit(1);
  }

  stack_node_delete(&stack, number);

  while (!stack_empty(&stack)) {
    printf("[%8d] ->> %d\n", counter, pop_stack(&stack));
    counter--;
  }

  return 0;
}
