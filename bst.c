#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include "bst.h"

/*

Place for the BST functions from Exercise 1.

*/

struct _Node
{
  int data;
  struct _Node *left;
  struct _Node *right;
};

Node *addNode(Node *root, int data)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  Node *temp;
  Node *prev = NULL;

  temp = root;
  while (temp)
  {
    prev = temp;
    if (temp->data > newNode->data)
      temp = temp->right;
    else if (temp->data < newNode->data)
      temp = temp->left;
    else
    {
      free(newNode);
      return NULL;
    }
  }
  if (prev == NULL)
    root = newNode;
  else
  {
    if (prev->data > newNode->data)
      prev->right = newNode;
    else
      prev->left = newNode;
  }

  return root;
}

Node *freeSubtree(Node *N)
{
  if (N == NULL)
    return NULL;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
  return NULL;
}

void removeSubtreeWorker(Node *R, int data)
{
  if (R == NULL)
    return;

  if (R->left && R->left->data == data)
  {
    freeSubtree(R->left);
    R->left = NULL;
    return;
  }

  if (R->right && R->right->data == data)
  {
    freeSubtree(R->right);
    R->right = NULL;
    return;
  }

  if (R->data < data)
    removeSubtreeWorker(R->left, data);
  else
    removeSubtreeWorker(R->right, data);
}

Node *removeSubtree(Node *R, int data)
{
  if (R == NULL)
    return NULL;

  if (R->data == data)
  {
    freeSubtree(R);
    return NULL;
  }
  removeSubtreeWorker(R, data);
  return R;
}

void displaySubtree(Node *N)
{
  if (N == NULL)
  {
    return;
  }
  displaySubtree(N->right);
  printf("%d\n", N->data);
  displaySubtree(N->left);
}

int countNodes(Node *N)
{
  int count = 0;
  if (N == NULL)
    return 0;
  count = count + countNodes(N->right);
  count = count + countNodes(N->left);
  count = count + 1;
  return count;
}

// this is the most complicated task
Node *removeNode(Node *root, int data)
{
  // Ensure root isn't null.
  if (root == NULL)
  {
    return NULL;
  }

  if (data > root->data)
  { // data is in the left sub-tree.
    root->left = removeNode(root->left, data);
  }
  else if (data < root->data)
  { // data is in the right sub-tree.
    root->right = removeNode(root->right, data);
  }
  else
  { // Found the correct node with data
    // Check the three cases - no child, 1 child, 2 child...
    // No Children
    if (root->left == NULL && root->right == NULL)
    {
      free(root);
      root = NULL;
    }
    // 1 child (on the right)
    else if (root->left == NULL)
    {
      Node *temp = root; // save current node
      root = root->right;
      free(temp);
    }
    // 1 child (on the left)
    else if (root->right == NULL)
    {
      Node *temp = root; // save current node
      root = root->left;
      free(temp);
    }
    // Two children
    else
    {
      // find minimal data of right sub tree
      Node *temp = root->left;
      while (temp->right != NULL)
      {
        temp = temp->right;
      }
      root->data = temp->data;                         // duplicate the node
      root->left = removeNode(root->left, root->data); // delete the duplicate node
    }
  }
  return root; // parent node can update reference
}

int numberLeaves(Node *N)
{
  if (N == NULL)
    return 0;

  if (N->left == NULL && N->right == NULL)
    return 1;

  return numberLeaves(N->left) + numberLeaves(N->right);
}

int nodeDepth(Node *R, Node *N)
{
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

float sum(Node *N)
{ // helper to calculcate the sum
  float total = 0;
  if (N == NULL)
  {
    return 0;
  }
  total = sum(N->right) + N->data + sum(N->left);

  return total;
}

float avgSubtree(Node *N)
{

  // TODO: Implement this function
  return (sum(N) / countNodes(N));
}

// Turn BST tree to sorted array

void BST_to_array(Node *root, int *BSTarr)
{

  // int* BSTarr = malloc(sizeof(int) * countNodes(root));
  static int index = 0;

  if (root == NULL)
  {
    return;
  }
  if (root->right != NULL)
  {
    BST_to_array(root->right, BSTarr);
  }
  BSTarr[index++] = root->data;
  if (root->left != NULL)
  {
    BST_to_array(root->left, BSTarr);
  }
}

Node *balanceTree_helper(int *arr, int start, int end)
{
  if (start > end)
  {
    return NULL;
  }
  int middle = (end + start) / 2;
  Node *balanced;
  balanced = addNode(NULL, arr[middle]);

  balanced->right = balanceTree_helper(arr, start, middle - 1);
  balanced->left = balanceTree_helper(arr, middle + 1, end);

  return balanced;
}

// This functions converts an unbalanced BST to a balanced BST
Node *balanceTree(Node *root)
{

  // TODO: Implement this function

  int *BSTarr = malloc(sizeof(int) * countNodes(root));
  BST_to_array(root, BSTarr);
  Node *balanced;

  balanced = balanceTree_helper(BSTarr, 0, countNodes(root) - 1);
  free(BSTarr);
  return balanced;
}
