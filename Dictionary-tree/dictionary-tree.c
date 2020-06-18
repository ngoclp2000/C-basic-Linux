#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdio_ext.h>
#include "tree.h"
void traversal(tree t){
    if (t == NULL) return;
    traversal(t->right);
    printf("%s\n",t->data->meaning);
    traversal(t->left);
}
struct List *insertToList(struct List *w,char word[]){
    struct List *newNode = (struct List *) malloc(sizeof(struct List));
    struct List *original = w;
    newNode->next = NULL;
    strcpy(newNode->word,word);
    if(w == NULL) return newNode;
    for(w;w->next != NULL;w = w->next);
    w->next = newNode;
    return original;
}
struct List *deleteNodeList(struct List *w,char word[]){
    struct List *original = w;
    struct List *pre = NULL;
    while(w != NULL && strcmp(w->word,word) != 0){
        pre = w;
        w = w->next;
    }
    if(original == w) return original->next;
    pre->next = w->next;
    free(w);
    return original;
}
void printList(struct List *w){
    while(w !=NULL){
        printf("%s",w->word);
        if(w->next == NULL) printf("\n");
        else printf(", ");
        w = w->next;
    }
}
int main(){
    tree dictionary = NULL;
    tree synonymous = NULL;
    int choice;
    do{
        printf("1.Import to BST\n2.Translate\n3.Delete words\n4.Add new words\n5.Import into file\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Importing........\n");
                FILE *fin = fopen("dictionary.txt","r+");
                while(!feof(fin)){
                    element_t n = (element_t) malloc(sizeof(struct Node));
                    fscanf(fin, "%s ",n->word);
                    fgets(n->meaning,256,fin);
                    if(n->meaning[ strlen(n->meaning) - 1] == '\n') n->meaning[ strlen(n->meaning) - 1] = '\0';
                    insert(&dictionary,n);
                    tree found_synonymous = search(synonymous,createData(n->meaning,n->word));
                    if(found_synonymous == NULL)
                        insert(&synonymous,createData(n->meaning,n->word));
                    else
                        found_synonymous->synonymous = insertToList(found_synonymous->synonymous,n->word);
                }
                fclose(fin);
                printf("Importing process finished\n");
                // char *r = (char *) malloc(sizeof(char)*10000);
                // r = treeToString(dictionary);
                // printf("%s\n",r);
                //traversal(synonymous);
                break;
            case 2:
                printf("Enter the words you want to find\n");
                char word[256];
                scanf("%s",word);
                tree found_word = search(dictionary,createData(word,""));
                if(found_word != NULL){
                    printf("Words: %s\nMeaning: %s\n",word,found_word->data->meaning);
                }else{
                    printf("Not found\n");
                    continue;
                }
                
                tree found_synonymous = search(synonymous,createData(found_word->data->meaning,word));
                if(found_synonymous != NULL){
                     printf("Synonymous of this words: ");
                     printList(found_synonymous->synonymous);
                }
            break;
            case 3:
                printf("Enter the words you want to delete\n");
                scanf("%s",word);
                tree t = search(dictionary,createData(word,""));
                tree st = search(synonymous,createData(t->data->meaning,""));
                if(st != NULL) st->synonymous = deleteNodeList(st->synonymous,word);
                dictionary = deleteNode(dictionary,createData(word,""));
                // char *r = (char *) malloc(sizeof(char)*10000);
                // r = treeToString(dictionary);
                // printf("%s\n",r);
                break;
            case 4:
                printf("Enter the new word and its meaning\n");
                char meaning[256];
                printf("Word: ");
                scanf("%s",word);
                __fpurge(stdin);
                printf("Meaning: ");
                scanf("%[^\n]s",meaning);
                __fpurge(stdin);
                insert(&dictionary,createData(word,meaning));
                break;
            case 5:
                printf("Exporting....\n");
                FILE *fout = fopen("dictionary.txt","w");
                breadth_first_search(dictionary,fout);
                printf("Exporting process finished\n");
                fclose(fout);
                break;
        }
    }while(choice!= 6);
    // FILE *fout = fopen("dout.txt","w+");
    // breadth_first_search(dictionary,fout);
    // fclose(fout);
}