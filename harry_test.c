#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

int main(){


    Node *a, *b, *c;
    a = addNode(NULL,40);
    a = addNode(a,63);
    a = addNode(a,30);
    a = addNode(a,45);
    a = addNode(a,50);
    a = addNode(a,60);
    a = addNode(a,65);

     //printf("test: %d\n", a->data );
    //printf("%d" , a->left->data);
    //printf("%d" , c->right->data);
    int count = countNodes(a);
    printf("Number of node: %d\n", count);
    displaySubtree(a);
    //balanceTree(a);
    printf("Average: %f", avgSubtree(a));
    return 0;
}