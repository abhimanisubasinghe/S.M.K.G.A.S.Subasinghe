#include <stdio.h>
#include <malloc.h>

struct node{
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *end = NULL;

void createll(int x){
    struct node *ptr,*new;
    new = (struct node *)malloc(sizeof(struct node)); 
    new -> data = x;
    new -> next = NULL;
    if(head == NULL){
        head = end = new;
    }
    else{
        ptr = head;
        while(ptr != end)
            ptr = ptr -> next;
        ptr ->  next = new;
        end = new;
    }
}

void printll(){
    int count = 0;
    struct node *ptr;
    ptr = head;
    if(head == NULL )
        printf("\nERROR::link list is empty");
    else{
        printf("\nData in the ll:\t");
        while(ptr != NULL){
            count ++;
            printf("%d   ",ptr -> data);
            ptr = ptr -> next;
        }
        printf("\n");
        printf("Number of elements in the list: %d\n",count);
    }
}

void insertinend(int x){
    struct node *ptr,*new;
    new = (struct node *)malloc(sizeof(struct node)); 
    new -> data = x;
    new -> next = NULL;
    if(head == NULL){
        head = end = new;
    }
    else{
        ptr = head;
        while(ptr != end)
            ptr = ptr -> next;
        ptr ->  next = new;
        end = new;
    }
}

void insertinbeg(int x){
    struct node *ptr,*new;
    new = (struct node *)malloc(sizeof(struct node)); 
    new -> data = x;
    new -> next = NULL;
    if(head == NULL){
        head = end = new;
    }
    else{
        ptr = head;
        new -> next = ptr;
        head = new;
    }
}

void insertbefore(int x,int y){
    struct node *ptr,*new;
    new = (struct node *)malloc(sizeof(struct node)); 
    new -> data = x;
    new -> next = NULL;
    if(head == NULL){
        head = end = new;
    }
    else{
        ptr = head;
        while(ptr -> next -> data != y)
            ptr = ptr -> next;
        new -> next = ptr -> next;
        ptr ->  next = new;
    }
}

void insertafter(int x,int y){
    struct node *ptr,*new;
    new = (struct node *)malloc(sizeof(struct node)); 
    new -> data = x;
    new -> next = NULL;
    if(head == NULL){
        head = end = new;
    }
    else{
        ptr = head;
        while(ptr -> data != y)
            ptr = ptr -> next;
        new -> next = ptr -> next;
        ptr ->  next = new;
    }
}

void delete(int y){
    struct node *ptr,*preptr;
    ptr = head;
    while(ptr ->  data != y){
        preptr = ptr;
        ptr = ptr -> next;
    }
    if( ptr == head ){
        head = head -> next;
        free(ptr);
    }
    if(ptr -> data == y){
        preptr -> next = ptr -> next;
        printf("\n%d data is deleated from the list\n",ptr -> data);
        free(ptr);
    }
    else{
        printf("\nERROR::Node not found");
    }
}

void main(){
    int opt,x,y;
    do{
        printf("\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("MAIN MENUE\n1.CREATE LINK LIST\t2.PRINT\t3.INSERT IN THE BEGINING\t4.INSERT IN THE END\t5.INSERT BEFORE A NODE\t6.INSERT AFTER A NODE\t7.DELETE\t8.EXIT");
        printf("\nInsert your option: ");
        scanf("%d",&opt);
        switch (opt){
            case 1:
                printf("\nInsert elements to be entered in the link list\nenter -1 to finish entering data\n");
                printf("Insert data: ");
                scanf("%d",&x);
                while(x != -1){
                    createll(x);
                    printf("\nInsert data: ");
                    scanf("%d",&x);
                }
                break;
            case 2:
                printll();
                break;
            case 3: 
                printf("\nInsert data: ");
                scanf("%d",&x);
                insertinbeg(x);
                break;
            case 4: 
                printf("\nInsert data: ");
                scanf("%d",&x);
                insertinend(x);
                break;
            case 5: 
                printf("\nInsert data to enter in the list: ");
                scanf("%d",&x);
                printll();
                printf("Before which node do you need to enter the new node?\n");
                scanf("%d",&y);
                insertbefore(x,y);
                break;
            case 6: 
                printf("\nInsert data to enter in the list: ");
                scanf("%d",&x);
                printll();
                printf("After which node do you need to enter the new node?\n");
                scanf("%d",&y);
                insertafter(x,y);
                break;
            case 7:
                if ( head == NULL){
                    printf("ERROR:: No data found\n");
                    break;
                }
                else{
                    printf("\nWhich node do you want to delete?");
                    printll();
                    scanf("%d",&y);
                    delete(y);
                    break;
                }
            case 8:
                break;
            default:
                printf("\nERROR:: Enter a valid option\n");
        }
    }while(opt != 8);
}