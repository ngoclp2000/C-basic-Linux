#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "tree.h"
// Driver code 
int generateRandomNumber(int limit){
    int num = rand() % limit;
    return num;
}
int main(){
    tree number = createTree();
    int limit = 1000000;
    srand(time(NULL));
    int choice;
    do{
        printf("1.Generate number\n2.Search for number\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                makeNULLTree(&number);
                //number = createTree();
                for(int i = 0; i < limit; i++){
                    int t = 0;
                    int num = generateRandomNumber(5000);
                    //printf("%d\n",num);
                    if(search(number, num,&t) != NULL) continue;
                    insert(&number, num);
                }
                printf("Height of Tree: %d\n",heightTree(number));
                
            break;
            case 2:
                printf("Enter the number you want to search\n");
                int num;
                int comparasionCount = 0;
                scanf("%d",&num);
                tree numberInTree = search(number,num,&comparasionCount);
                if(numberInTree != NULL) printf("Found the number after %d comparasion\n",comparasionCount);
                else printf("Not Found\n");
            break;
        }
    }while(choice != 3);
} 