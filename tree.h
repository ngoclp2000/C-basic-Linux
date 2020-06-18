#ifndef _MAIN_H_
#define _MAIN_H_
struct Node {
    int data;
};
struct Tree {
  struct Node *data;
  struct Tree *left;
  struct Tree *right;
};
typedef int keyvalue;
typedef struct Node *element_t;
typedef struct Tree* treeNode;
typedef struct Tree* tree;
tree createTree();
int isNullTree(tree t);
void makeNULLTree(tree *t);
element_t createData(int x);
tree createNewNode(element_t x);
tree leftNode(tree t);
tree rightNode(tree t);
tree addLeftMost(tree t,treeNode x);
tree addRightMost(tree t,treeNode x);
int countNode(tree t);
int heightTree(tree t);
int isLeaf(tree t);
int countLeaf(tree t);
tree mergeTwoSubNode(tree node1,tree node2,treeNode x);
tree search(tree t , keyvalue x);
void insert(tree *t, keyvalue x);
tree deleteNode(tree root,keyvalue x);
void freeTree(tree t);
tree findMin(tree t); 
tree findMax(tree t);
void prettyPrint(tree t,char *prefix);
int countInnerNode(tree t);
int rightChildCount(tree t);
char* treeToString(tree t);
#endif