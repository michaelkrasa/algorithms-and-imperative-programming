#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "global.h"
#include "bstree.h"


// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}

struct bstree* initialize_set (int size)
{
  // An empty tree is represented by NULL
  return NULL;
}

void tidy(struct bstree* tree)
{
  if(tree){
    tidy(tree->left);
    tidy(tree->right);
    free(tree->value);
    free(tree);
  }
}

int size(struct bstree* tree){
  if(tree){
    return (1 + size(tree->left) + size(tree->right));
  }
  return 0;
}

int height(struct bstree* tree)
{
  if(tree)
  {
    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);

    if(leftHeight > rightHeight)
      return (leftHeight + 1);
    else return (rightHeight + 1);
  }
  else
    return 0;
}

int comparisons(struct bstree* tree)
{
  if(tree)
  {
    return (tree->comparisons + comparisons(tree->left) + comparisons(tree->right));
  }
  else return 0;
}


struct bstree* insert(Value_Type value, struct bstree* tree)
{
  if(tree){
    // If tree is not NULL then insert into the correct sub-tree
    if (compare(value, tree->value) < 0)
    {
      tree->left = insert(value, tree->left);
      tree->comparisons++;
    }
    else if(compare(value, tree->value) > 0)
    {
      tree->right = insert(value, tree->right);
      tree->comparisons++;
    }
  }
  else{
    // Otherwise create a new node containing the value
    tree = malloc(sizeof(struct bstree));
    tree->value = strdup(value);
    tree->left = NULL;
    tree->right = NULL;
    tree->comparisons = 0;
  }
  return tree;
}

bool find(Value_Type value, struct bstree* tree)
{
  if(tree){
    // Complete the find function - same as in darray
    if (compare(value, tree->value) < 0)
    {
      tree->comparisons++;
      return find(value, tree->left);
    }
    else if(compare(value, tree->value) > 0)
    {
      tree->comparisons++;
      return find(value, tree->right);
    }
    else
      return true;
  }
  // If tree is NULL then it contains no values
  return false;
}

// You can update this if you want
void print_set_recursive(struct bstree* tree, int depth)
{
  if(tree){
    unsigned i;
    for(i=0;i<depth;i++){ printf(" "); }
    printf("%s\n",tree->value);
    print_set_recursive(tree->left,depth+1);
    print_set_recursive(tree->right,depth+1);
  }
}
// You can update this if you want
void print_set (struct bstree* tree)
{
 printf("Tree:\n");
 print_set_recursive(tree,height(tree));
}

void print_stats (struct bstree* tree)
{
  printf("Height of the tree is: %d\n", height(tree));
  printf("Size of the tree is: %d\n", size(tree));
  printf("Number of comparisons: %d\n", comparisons(tree));
}
