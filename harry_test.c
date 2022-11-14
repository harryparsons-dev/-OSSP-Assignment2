#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bst.h"
//#include "bst.c"
//#include "serve_client.c"
Node *root;

void clean()
{
  /*****************************************************/
  /******   Free resources before program ends  ********/
  /*****************************************************/

  root = freeSubtree(root);
  root = NULL;
  return;
}

int main()
{

  Node *a, *b, *c;
  a = addNode(NULL, 1);
  a = addNode(a, 49);
  a = addNode(a, 48);
  a = addNode(a, 47);
  a = addNode(a,46);
  a = addNode(a,45);
 a = addNode(a,44);
 a = addNode(a,60);
  // b = addNode(NULL,50);
  // c= NULL;
  // displaySubtree(a);
  // printf("\n");
  // displaySubtree(b);
  // int f = nodeDepth (a, a->right->right->right->right->right);
  // int node = nodeDepth(a,NULL);
  // printf("Before balancing node depth: %d\n", f);
  // a = balanceTree(a);
  // f = nodeDepth (a, a->right->left);
  // printf("After balancing node depth: %d\n", f);

  displaySubtree(a);
  printf("after balancing\n");
  a = balanceTree(a);
  displaySubtree(a);

 

  a = freeSubtree(a);
  a = NULL;
  b = freeSubtree(b);
  b = NULL;


  clean();
  

  // printf("test: %d\n", a->data );
  // printf("%d, ", a->data);
  // printf("%d, ", a->right->data);
  // printf("%d, ", a->right->right->data);
  // printf("%d\n", a->right->right->left->data);
  // printf("%d" , c->right->data);
  // int count = countNodes(a);
  // printf("Number of node: %d\n", count);
  // displaySubtree(a);
  //   a = balanceTree(a);
  //   printf("%d, " , a->data);
  //   printf("%d, " , a->right->data);
  //   printf("%d, " , a->right->left->data);
  //   printf("%d\n" , a->left->data);
  // printf("After balanced: \n");
  // displaySubtree(a);
  // printf("Average: %f", avgSubtree(a));
  //ServeClient("client6_test");
  


  return 0;
}