#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>

#include "global.h"
#include "darray.h"
#include "sorting.h"


// Can be redefined if Value_Type changes
int compare(Value_Type a, Value_Type b){
  return strcmp(a,b);
}


struct darray* initialize_set (int size)
{

  struct darray* arr = malloc(sizeof(struct darray));
  check(arr);
  arr->cells = (Value_Type*) (malloc(sizeof(Value_Type)*size));
  check(arr->cells);
  arr->capacity = size;
  arr->size = 0;
  arr->sorted = false;
  arr->resizes = 0;
  return arr;
}

void tidy(struct darray* arr)
{
  if(arr){
    // free memory created by strdup
    for(unsigned i=0; i<arr->size;i++){ free(arr->cells[i]); }
    // free array and struct
    free(arr->cells);
    free(arr);
  }
}

int size(struct darray* arr){ return arr->size; }

struct darray* insert (Value_Type value, struct darray* arr)
{
  // If we have reached capacity, double size and copy
  if(arr->size >= arr->capacity){
    struct darray* new_arr = initialize_set(arr->capacity*2);
    for(unsigned int i=0;i<arr->size;i++){
      new_arr->cells[i] = arr->cells[i];
    }
    new_arr->size = arr->size;
    new_arr->resizes = arr->resizes+1;
    free(arr->cells);
    free(arr);
    arr = new_arr;
  }

  arr->cells[arr->size] = strdup(value);
  arr->size++;

  // changing the array means it may no longer be sorted
  arr->sorted = false;

  return arr;
}

bool find (Value_Type value, struct darray* arr)
{
  // Linear search implementation
  if(mode == LINEAR_SEARCH){
    int i;
    for(i=0; i < arr->size; i++)
    {
      if(compare(arr->cells[i], value) == 0)
        return true;
    }
  }
  else{ // Binary Search
    if(!arr->sorted){
      if(verbose > 0){
        //printf("Dynamic Array not sorted, sorting...\n");
      }
      sort(arr,mode);
      if(verbose > 0){
        //printf("Dynamic Array sorted\n");
      }
      if(verbose > 2){
        print_set(arr);
      }
      arr->sorted = true;
    }
    int L = 0;             // Left element
    int R = arr->size - 1; // Right element
    int m;                 // Middle element
    // While there are elements in the array to compare our value to
    while(L <= R)
    {
      m = floor((L+R) / 2); // using floor function to get an int
      if(compare(arr->cells[m], value) < 0)
        L = m + 1;  // Left boundary of our subarray moves
      else if(compare(arr->cells[m], value) > 0)
        R = m - 1;  // Right boundary of our subarray moves
      else
        return true; // sorted!
    } // while
    // If element is not found in the list and the while loop terminates
    return false;
  } // Binary search
  // To supress warning, default return value
  return false;
} // find

// You can make any changes you want to this function
void print_set (struct darray* arr)
{
  printf("DArray:\n");
  for(unsigned i=0;i<arr->size;i++){
    printf("\t%s\n",arr->cells[i]);
  }
}

// You can make any changes you want to this function
void print_stats (struct darray* arr)
{
  printf("Dynamic array of capacity %d contains %d elements\n",arr->capacity,arr->size);
  printf("Dynamic array was resized %d times\n",arr->resizes);
}
