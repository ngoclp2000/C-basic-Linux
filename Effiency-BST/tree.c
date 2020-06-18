#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"
tree createTree(){
  return NULL;
}
int isNullTree(tree t) {
  return (t == NULL);
}
void makeNULLTree(tree *t){
    if((*t) == NULL) return;
    makeNULLTree(&(*t)->left);
    makeNULLTree(&(*t)->right);
    free((*t));
}
element_t createData(int x){
  element_t n = (element_t) malloc(sizeof(struct Node));
  n->data = x;
  return n;
}
tree createNewNode(element_t x){
  treeNode newNode = (treeNode) malloc(sizeof(struct Tree));
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->data = x;
  return newNode;
}
tree leftNode(tree t){
  if (t == NULL) return t;
  return leftNode(t->left);
}
tree rightNode(tree t){
  if (t == NULL) return t;
  return rightNode(t->left);
}
// addRightMost and addLeftMost For normal Tree
tree addLeftMost(tree t,treeNode x){
  while(t->left != NULL)
    t = t->left;
  t->left = x;
  return t;
}
tree addRightMost(tree t,treeNode x){
  while(t->right != NULL)
    t = t->right;
  t->right = x;
  return t;
}
int countNode(tree t){
  if (t == NULL) return 0;
  return 1 + countNode(t->right) + countNode(t->left);
}
int heightTree(tree t){
if (t==NULL)  
       return 0; 
   else 
   { 
       /* compute the depth of each subtree */
       int lDepth = heightTree(t->left); 
       int rDepth = heightTree(t->right); 
  
       /* use the larger one */
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}
int isLeaf(tree t){
  return (t->left == NULL && t->right == NULL);
}
int countLeaf(tree t){
  if(t == NULL) return 0;
  if(t->left != NULL || t->right != NULL) return 0 + countLeaf(t->left) + countLeaf(t->right);
  return 1;
}
int countInnerNode(tree t){
    if(t == NULL) return 0;
    if(t->left != NULL || t->right != NULL) return 1 + countInnerNode(t->right) + countInnerNode(t->left);
    else return 0;
}
int rightChildCount(tree t) {
  if(t == NULL) return 0;
  return 1 + rightChildCount(t->right);
}
tree search(tree t ,keyvalue x,int *count){
  (*count)+=1;
  if (t == NULL) return NULL;
  if( x > t->data->data ){
      return search(t->right,x,count);
  }else if( x < t->data->data ){
      return search(t->left,x,count);
  }
  return t;
}
void insert(tree *t,keyvalue x){
   if((*t) == NULL){
        (*t) = createNewNode(createData(x));
        return;
    }
    else if(x < (*t)->data->data)
        insert(&(*t)->left,x);
    else
        insert(&(*t)->right,x);
}
tree  minValueNode(tree node) 
{ 
    tree current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
tree deleteNode(tree root,keyvalue x){
        if (root == NULL) return root;
    if(x < root->data->data){
        root->left = deleteNode(root->left,x);
    }else if(x > root->data->data){
        root->right = deleteNode(root->right,x);
    }else{
        if(root->left == NULL){
            tree temp = root->right;
            free(root);
            return temp;
        }else if(root->right == NULL){
            tree temp = root->left;
            free(root);
            return temp; 
        }else{
            tree temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right,temp->data->data);
        }
    }
    return root;
}
tree findMin(tree t){
  return (t->left == NULL) ? t : findMin(t->left);
} 
tree findMax(tree t){
  return (t->right == NULL) ? t : findMin(t->right);
}
char* treeToString(tree t) {
  char *result;
  char *left;
  char *right;

  if (isNullTree(t)) {
    result = (char*)malloc(4);
    strcpy(result, "Nil");
    return result;
  } else {
    left = treeToString(t->left);
    right = treeToString(t->right);
    
    result = (char*)malloc(40 + strlen(left) + strlen(right));
    sprintf(result, "node(%d,%s,%s)", t->data->data, left, right);
    free(left);
    free(right);
    return result;
  }
}