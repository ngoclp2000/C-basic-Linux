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
element_t createData(char word[],char meaning[]){
  element_t n = (element_t) malloc(sizeof(struct Node));
  strcpy(n->word,word);
  strcpy(n->meaning,meaning);
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

tree search(tree t ,keyvalue x){
  if (t == NULL) return NULL;
  if(strcmp( x->word,t->data->word) > 0){
      return search(t->right,x);
  }else if(strcmp(x->word,t->data->word) < 0){
      return search(t->left,x);
  }
  return t;
}
tree searchSynonymous(tree t ,keyvalue x){
  if (t == NULL) return NULL;
  char temp1[256],temp2[256];
  strcpy(temp1,t->data->word);
  strcpy(temp2,x->word);
  int check1 = KPM_Search(temp1,temp2);
  int check2 = KPM_Search(temp1,temp2);
  int diff = strlen(temp1) - strlen(temp2);
  diff = (diff < 0) ? -diff : diff;
  if( strcmp( x->word,t->data->word) > 0 && check1  == 0 && check2 == 0){
      return searchSynonymous(t->right,x);
  }else if(strcmp(x->word,t->data->word) < 0 && check1  == 0 && check2 == 0){
      return searchSynonymous(t->left,x);
  }
  return t;
}
// int _strcmp(char c1[],char c2[]){
//   int length = (strlen(c1) > strlen(c2)) ? strlen(c2) : strlen(c1);
//   for(int i = 0 ; i < length ; i++){
//       if(c1[i] > c2[i]) return 1;
//       else if(c1[i] < c2[i]) return -1;
//   } 
//   if(strlen(c1) == strlen(c2)) return 0;
//   if(length == strlen(c1)) return -1;
//   return 1;
// }
void insert(tree *t,keyvalue x){
   if((*t) == NULL){
        (*t) = createNewNode(x);
        return;
    }
    else if( strcmp(x->word,(*t)->data->word) < 0)
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
    if(strcmp(x->word,root->data->word) < 0){
        root->left = deleteNode(root->left,x);
    }else if(strcmp(x->word,root->data->word) > 0){
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
            root->right = deleteNode(root->right,temp->data);
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
    
    result = (char*)malloc(100000 + strlen(left) + strlen(right));
    sprintf(result, "node(%s: %s,%s,%s)", t->data->word,t->data->meaning, left, right);
    free(left);
    free(right);
    return result;
  }
}


int IsEmpty(Queue *_Queue){
    return (_Queue->size == 0);
}
int IsFull(Queue *_Queue){
    return (_Queue->size == _Queue->limit);
}
Queue *CreateNewQueue(tree Root){
    Queue *newQueue = (Queue *) malloc(sizeof(Queue));
    newQueue->front = 0;
    newQueue->rear = 0;
    newQueue->size = 0;
    newQueue->limit = countNode(Root);
    newQueue->_Data = (tree) malloc(sizeof(struct Tree) * countNode(Root));
    return newQueue;
}

void enqueue(Queue **_Queue,tree Node){
    if(IsFull((*_Queue))) {
        printf("The queue is full\n");
        return;
    }
    (*_Queue)->_Data[(*_Queue)->rear] = (*Node);
    if((*_Queue)->rear + 1 < (*_Queue)->limit) (*_Queue)->rear +=1;
    else (*_Queue)->rear = 0;
    (*_Queue)->size += 1;
    return;
}   
tree Dequeue(Queue *_Queue){
    if(IsEmpty(_Queue)) {
        printf("The queue is empty\n");
        return NULL;
    }
    tree returnTree = (_Queue->_Data + _Queue->front );
    if(_Queue->front + 1 < _Queue->limit) _Queue->front +=1;
    else _Queue->front = 0;
    _Queue->size -= 1;
    return returnTree;
}
void breadth_first_search(tree Root,FILE *ptr){
    Queue *queue = CreateNewQueue(Root);
    tree RunNode = Root;
    if(RunNode != NULL){
        enqueue(&queue,RunNode);
        while(!IsEmpty(queue)){
            RunNode = Dequeue(queue);
            fprintf(ptr,"%s %s",RunNode->data->word,RunNode->data->meaning);
            if(RunNode->left != NULL || RunNode->right != NULL || !IsEmpty(queue)) fputs("\n",ptr);
            if(RunNode->left != NULL) enqueue(&queue,RunNode->left);
            if(RunNode->right != NULL) enqueue(&queue,RunNode->right);
        }
    }
}
int isMatch(char des[],char part[]){
    int pos = 0;
    int flag = 1;
    while(pos + strlen(des) <= strlen(part) && flag){
        for(int i = pos ; i < strlen(des) + pos ; i++){
            if(des[i-pos] != part[i])
                    goto next;
        }
        flag = 0;
        next:
            pos++;
    }
    if(flag)
        return 0;
    else
        return 1;
}
int Finding_new_pos(int pos,char txt[],char pat[]){
    for(int j = pos ; j < strlen(txt) ; j++)
                    if(txt[j] == pat[0])
                        return j;
    return -1;
}
int KPM_Search(char txt[],char pat[]){
    int pos_txt = 0;
    int pos_pat = 0;
    int size1 = strlen(txt);
    int size2 = strlen(pat);
    int sum = 0;
    while(pos_txt < size1){
        //printf("%d\n",pos_txt);
        int temp = pos_txt;
        for(int i = 0 ; i < size2; i++){
            //printf("%c %c\n",txt[temp],pat[i]);
            if(txt[temp] == pat[i]){
                temp++;
            }else{
                pos_pat = 0;
                int check = Finding_new_pos(pos_txt+1,txt,pat);
                if(check == -1) pos_txt=size1;
                else pos_txt = check;
                goto Skip;
            }
        }
        return 1;
        Skip:
        continue;
    }
    return 0;
}