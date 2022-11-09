#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"
#include "serve_client.c"
Node *a;



void clean(){
  /*****************************************************/
  /******   Free resources before program ends  ********/
  /*****************************************************/

  a=freeSubtree(a);
  a= NULL;
  return;
}



int main(){

   
    Node *a, *b, *c;
    a = addNode(NULL,50);
    a = addNode(a,40);
    a = addNode(a,30);
    a = addNode(a,31);
    //a = addNode(a,50);
    //a = addNode(a,60);
   // a = addNode(a,65);

     //printf("test: %d\n", a->data );
     printf("%d, " , a->data);
     printf("%d, " , a->right->data);
     printf("%d, " , a->right->right->data);
     printf("%d\n" , a->right->right->left->data);
    //printf("%d" , c->right->data);
    int count = countNodes(a);
    printf("Number of node: %d\n", count);
    //displaySubtree(a);
    //  a = balanceTree(a);
    //  printf("%d, " , a->data);
    //  printf("%d, " , a->right->data);
    //  printf("%d, " , a->right->left->data);
    //  printf("%d\n" , a->left->data);
    //printf("After balanced: \n");
    //displaySubtree(a);
   // printf("Average: %f", avgSubtree(a));
   ServeClient("client1");
   clean();


    return 0;
}