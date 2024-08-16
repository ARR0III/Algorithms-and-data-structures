#include <stdio.h>
#include <stdlib.h>

typedef struct list2 {
  int data;
  struct list2 * next;
} list;

void list_push(list ** lst, int data) {
  list * tmp = (list *)malloc(sizeof(struct list2));

  if (!tmp)
    exit(1);

  tmp->data = data;
  tmp->next = *lst;

  *lst = tmp;
}

void list_burn(list ** lst) {
  list * tmp;

  while (*lst) {
    tmp = (*lst)->next;
    free(*lst);
    *lst = tmp;
  }
}

void list_rev_print(list ** lst) {
  list * tmp = *lst;

  while (tmp) {
    printf("%d\n", tmp->data);
    tmp = tmp->next;
  }
}

int main (void) {
  list * begin = NULL;

  int data;

  while(scanf("%d", &data) == 1) {
    list_push(&begin, data);
  }

  list_rev_print(&begin);
  list_burn(&begin);

  return 0;
}


