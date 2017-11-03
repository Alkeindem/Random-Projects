#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
  int content[4];
  struct Node* next;
} node;

Node* get()
void addBranch(node* head, int parent, int key, int childL, childR)
{
  node* current = head;
  
  while(current->next != NULL)
  {
    current = current->next;
  }
  
  node* aux = (node*) malloc(sizeof(node));
  aux->content = {parent, key, childL, childR}
  aux->next = NULL;
  
  




/*/--------------------------------------------------------------/*/
// Crea e inicializa con ceros un arbol binario en blanco.
int seedStatic(int n)
{
  int tree[n][4];
  for (int i=0; i<n; i++)
  {
    tree[i] = {0, 0, 0, 0};   // {padre, clave, hijoizq, hijoder}
  }
  return tree
}  
