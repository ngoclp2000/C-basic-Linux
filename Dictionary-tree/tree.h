#ifndef _MAIN_H_
#define _MAIN_H_
struct Node {
    char word[256];
    char meaning[256];   
};
struct List{
  char word[256]; 
  struct List *next;
};
struct Tree {
  struct Node *data;
  struct List *synonymous;
  struct Tree *left;
  struct Tree *right;
};
typedef struct Node* keyvalue;
typedef struct Node *element_t;
typedef struct Tree* treeNode;
typedef struct Tree* tree;

typedef struct Queue_t{
    int front,rear,size;
    unsigned limit;
    tree _Data;
}Queue;

tree createTree();
int isNullTree(tree t);
void makeNULLTree(tree *t);
element_t createData(char word[],char meaning[]);
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

void breadth_first_search(tree Root,FILE *ptr);
int _strcmp(char c1[],char c2[]);
int KPM_Search(char txt[],char pat[]);
tree searchSynonymous(tree t ,keyvalue x);
int isMatch(char des[],char part[]);
#endif