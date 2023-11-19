#include <stdio.h>
#include <stdlib.h>

typedef struct bin_tree_type {
  int number;

  struct bin_tree_type * left;
  struct bin_tree_type * right;
} bin_tree;

void bin_tree_push(bin_tree ** node, int number) {
  if (*node) {
    if (number < (*node)->number) {
      bin_tree_push(&((*node)->left), number);
    }
    else
    if (number > (*node)->number) {
      bin_tree_push(&((*node)->right), number);
    }

    return;
  }

  *node = (bin_tree *)malloc(sizeof(bin_tree));

  if (NULL == *node)
    exit(-1);

  (*node)->number = number;
  (*node)->left   = NULL;
  (*node)->right  = NULL;
}

void tree_sum(void * sum, int number) {
  *((int *)sum) += number;
}

void bin_tree_sum(bin_tree ** node, void * number, void (*tree_sum)(void *, int)) {
  if (NULL == *node)
    return;

  bin_tree_sum(&((*node)->left), number, tree_sum);
  bin_tree_sum(&((*node)->right), number, tree_sum);

  (*tree_sum)(number, (*node)->number);
}

bin_tree * bin_tree_search(bin_tree ** node, int number) {
  if (*node) {
    bin_tree * sum;

    if (number == (*node)->number) {
      return *node;
    }

    sum = bin_tree_search(&((*node)->left), number);

    if (sum)
      return sum;

    return bin_tree_search(&((*node)->right), number);
  }

  return NULL;
}

void bin_tree_burn(bin_tree ** node) {
  if (NULL == *node)
    return;

  bin_tree_burn(&((*node)->left));
  bin_tree_burn(&((*node)->right));

  free(*node);
  *node = NULL;
}

int main(void) {
  bin_tree * root = NULL;
  int number;

  while(scanf("%d", &number) == 1) {
    bin_tree_push(&root, number);
  }

  if (!root) {
    return 0;
  }

  number = 0;

  printf("Enter number for search:");

  if (scanf("%d", &number) != 1) {
    fprintf(stderr, "You enter not number!\n");
    exit(-1);
  }

  printf("Number \"%d\"%sfound!\n", number, bin_tree_search(&root, number) ? " " : " not ");

  bin_tree_sum(&root, &number, &tree_sum);
  printf("bin tree sum:\t%d\n", number);

  bin_tree_burn(&root);

  return 0;
}
