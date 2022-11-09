#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

struct _Node {
  int data;
  struct _Node* left;
  struct _Node* right;
};

Node* addNode(Node *root, int data)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  Node *temp;
  Node *prev = NULL;

  temp = root;
  while(temp) {
    prev = temp;
    if (temp->data > newNode->data)
      temp = temp->right;
    else if (temp->data < newNode->data)
      temp = temp->left;
    else {
      free(newNode);
      return NULL;
    }
  }
  if (prev==NULL)
    root = newNode;
  else {
    if (prev->data > newNode->data)
      prev->right = newNode;
    else
      prev->left = newNode;
  }

  return newNode;
}

Node* freeSubtree(Node *N) {
  if (N == NULL)
    return NULL;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
  return NULL;
}

void removeSubtreeWorker(Node *R, int data) {
  if (R == NULL)
    return;

  if (R->left && R->left->data == data) {
    freeSubtree(R->left);
    R->left = NULL;
    return;
  }

  if (R->right && R->right->data == data) {
    freeSubtree(R->right);
    R->right = NULL;
    return;
  }

  if (R->data < data)
    removeSubtreeWorker(R->left, data);
  else
    removeSubtreeWorker(R->right, data);  
}

Node* removeSubtree(Node *R, int data) {
  if (R == NULL)
    return NULL;

  if (R->data == data) {
    freeSubtree(R);
    return NULL;
  }
  removeSubtreeWorker(R, data);
  return R;
}

void displaySubtree(Node *N)
{
  if (N==NULL)
    {
      return ;
    }
  displaySubtree(N->right);
  printf("%d\n", N->data);
  displaySubtree(N->left);
}

int countNodes(Node *N)
{
  int count=0;
  if(N==NULL)
    return 0;
  count = count + countNodes(N->right);
  count = count + countNodes(N->left);
  count = count + 1;
  return count;
}

// this is the most complicated task
Node* removeNode(Node* root, int data)
{
  // Ensure root isn't null.
  if (root == NULL) {
    return NULL;
  }
  	
  if (data > root->data) {  // data is in the left sub-tree.
    root->left = removeNode(root->left, data);
  } else if (data < root->data) { // data is in the right sub-tree.
    root->right = removeNode(root->right, data);
  } else { // Found the correct node with data
    // Check the three cases - no child, 1 child, 2 child...
    // No Children
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }
    // 1 child (on the right)
    else if (root->left == NULL) {
      Node *temp = root; // save current node
      root = root->right;
      free(temp);
    }
    // 1 child (on the left)
    else if (root->right == NULL) {
      Node *temp = root; // save current node
      root = root->left;
      free(temp);
    }
    // Two children
    else {
      // find minimal data of right sub tree
      Node *temp = root->left; 
      while(temp->right != NULL) {
        temp = temp->right;
      }
      root->data = temp->data; // duplicate the node
      root->left = removeNode(root->left, root->data); // delete the duplicate node
    }
  }	
  return root; // parent node can update reference
}

int numberLeaves(Node *N) {
  if (N == NULL)
    return 0;

  if (N->left == NULL && N->right == NULL)
    return 1;

  return numberLeaves(N->left) + numberLeaves(N->right);
}

int nodeDepth(Node *R, Node *N) {
  if (R == NULL || N == NULL)
    return -1;

  if (R == N)
    return 0;

  int subDepth = nodeDepth(R->data < N->data ? R->left : R->right, N);

  if (subDepth >= 0)
    return subDepth + 1;
  else
    return -1;
}
