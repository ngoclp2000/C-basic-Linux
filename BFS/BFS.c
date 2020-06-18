#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
typedef struct _Tree{
    char name[27];
    char phone_num[21];
    char email[27];
    struct _Tree *leftNode;
    struct _Tree *rightNode;
}Tree;
int countNode();
typedef struct Queue_t{
    int front,rear,size;
    unsigned limit;
    Tree *_Data;
}Queue;
// Passing & before struct
void MakeNullTree(Tree **Root){
    (*Root) = NULL;
}
int _isEmpty(Tree *Root){
    return (Root == NULL);
}
void createNewNode(Tree **Root,Tree *newNode){
    if((*Root) == NULL){
        (*Root) = newNode;
    }else{
         //printf("%d\n",strcmp(newNode->email,(*Root)->email));
        if(strcmp(newNode->name,(*Root)->name) < 0){
            createNewNode(&(*Root)->leftNode,newNode);
        }else{
            createNewNode(&(*Root)->rightNode,newNode);
        }
    }
}
int countNode(Tree *Root){
    if(Root == NULL)
        return 0;
    return 1 +  countNode(Root->leftNode) + countNode(Root->rightNode);
}
// But it count from 1, so you minus the result with 1 to get the right result
int Height_Tree(Tree *Root){
    if(Root == NULL) return 0;
    return MAX(1+Height_Tree(Root->leftNode),1+Height_Tree(Root->rightNode));
}
Tree  *Finding(Tree *Root,char email_finding[]){
    if(Root == NULL) return NULL;
    int sign = strcmp(email_finding,Root->email);
    if (sign >0){
        return Finding(Root->rightNode,email_finding);
    }else if(sign < 0){
        return Finding(Root->leftNode,email_finding);
    }else return Root;
}
int IsEmpty(Queue *_Queue){
    return (_Queue->size == 0);
}
int IsFull(Queue *_Queue){
    return (_Queue->size == _Queue->limit);
}
Queue *CreateNewQueue(Tree *Root){
    Queue *newQueue = (Queue *) malloc(sizeof(Queue));
    newQueue->front = 0;
    newQueue->rear = 0;
    newQueue->size = 0;
    newQueue->limit = countNode(Root);
    newQueue->_Data = (Tree *) malloc(sizeof(Tree) * countNode(Root));
    return newQueue;
}

void enqueue(Queue **_Queue,Tree *Node){
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
Tree *Dequeue(Queue *_Queue){
    if(IsEmpty(_Queue)) {
        printf("The queue is empty\n");
        return NULL;
    }
    Tree *returnTree = (_Queue->_Data + _Queue->front );
    if(_Queue->front + 1 < _Queue->limit) _Queue->front +=1;
    else _Queue->front = 0;
    _Queue->size -= 1;
    return returnTree;
}
void breath_first_search(Tree *Root,FILE *ptr){
    Queue *queue = CreateNewQueue(Root);
    Tree *RunNode = Root;
    if(RunNode != NULL){
        enqueue(&queue,RunNode);
        while(!IsEmpty(queue)){
            RunNode = Dequeue(queue);
            //fprintf(ptr,"%s %s %s",RunNode->name,RunNode->phone_num,RunNode->email);
            printf("%s %s %s\n",RunNode->name,RunNode->phone_num,RunNode->email);
            if(RunNode->leftNode != NULL || RunNode->rightNode != NULL || !IsEmpty(queue)) fputs("\n",ptr);
            if(RunNode->leftNode != NULL) enqueue(&queue,RunNode->leftNode);
            if(RunNode->rightNode != NULL) enqueue(&queue,RunNode->rightNode);
        }
    }
}
int main(){
    Tree *Root = NULL;
    FILE *ptr = fopen("input.txt","r");
    int i = 0;
    while(!feof(ptr)){
        Tree *newNode = (Tree *) malloc(sizeof(Tree));
        newNode->leftNode = NULL;
        newNode->rightNode = NULL;
        fscanf(ptr,"%s %s %s\n",newNode->name,newNode->phone_num,newNode->email);
        createNewNode(&Root,newNode);
    }
    fclose(ptr);
    ptr = fopen("output.txt","w");
    //printf("Enter the email\n");
    // char email_finding[27];
    // scanf("%s",email_finding);
    // Tree *Finding_Node = Finding(Root,email_finding);
    // if(Finding_Node != NULL)
    //     fprintf(ptr,"%s %s %s",Finding_Node->name,Finding_Node->phone_num,Finding_Node->email);
    // else printf("Not match\n");
    breath_first_search(Root,ptr);
    //printf("%s\n",Root->rightNode->name);
}