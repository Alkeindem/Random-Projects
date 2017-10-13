#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
  int data;
  int id;
  struct Node* next;
} Node;

int matrix[][];
