#include <stdio.h>
#include <malloc.h>

//in the code I have used word node for the vertex in the graph

int noof_nodes;

//structure for creating adjacent edges
struct adj{
    struct node *parent;
    struct node *child;
    struct adj *next;
};

//structure for a node 
struct node{
    int data;
    struct node *next;
    struct adj *head;
};

//initializing the graph structure
struct node *start = NULL;

//funtion to create a node 
void createnode(int x){
    struct node *new,*ptr;
    new = (struct node *)malloc(sizeof(struct node));
    new -> data = x;
    new -> next = NULL;
    new -> head = NULL;
    ptr = start;
    if(start == NULL)
        start = new;
    else{
        while(ptr->next != NULL)
            ptr = ptr -> next;
        ptr -> next = new;
    }
}

//funtion to add adjacent vertex to given vertex
void createadj(struct node *p){
    int noof_adj;
    printf("\nHow many adj nodes: ");
    scanf("%d",&noof_adj);
    int i = noof_adj;
    while(i!=0){
        struct adj *new;
        new = (struct adj *)malloc(sizeof(struct adj));
        new -> parent = p;
        printf("\nEnter the adj node: ");
        int adjnode;
        scanf("%d",&adjnode);
        struct node *ptr;
        ptr = start;
        while(ptr != NULL){
            if(ptr -> data == adjnode)
                break;
            ptr = ptr -> next;
        }
        if(ptr == NULL){
            printf("\nERROR: Node not found");
            free(new);
        }
        else if( ptr -> data == adjnode ){
            new -> child = ptr;
            new -> next = NULL;
            if(p->head == NULL)
                p -> head = new;
            else{
                struct adj *a;
                a = p -> head;
                while(a->next!=NULL)
                    a = a -> next;
                a -> next = new;
            }
            i--;
        }
    }
}

//funtion to create a graph
void creategraph(){
    int i = noof_nodes;
    while(i!=0){
        int x;
        printf("\nInsert data: ");
        scanf("%d",&x);
        createnode(x);
        i--;
    }
    printf("\nNodes have been recorded");
    struct node *ptr;
    ptr = start;
    while(ptr != NULL){
        printf("\nRecording adj node details of %d",ptr -> data);
        createadj(ptr);
        ptr = ptr -> next;
    }
}

void addnode(){
    int x;
    printf("\nInsert data: ");
    scanf("%d",&x);
    createnode(x);
    printf("\nNode has been recorded");
    struct node *ptr;
    ptr = start;
    while(ptr -> next != NULL)
        ptr = ptr -> next;
    printf("\nRecording adj node details of %d",ptr -> data);
    createadj(ptr);
}

//funtion to display the graph
void display(){
    struct node *ptr;
    ptr = start;
    if(start == NULL )
        printf("\nERROR: Graph is empty");
    else{
        while(ptr!=NULL){
            printf("\nNode: %d\t\t",ptr->data);
            struct adj *a;
            a = ptr -> head;
            while(a!=NULL){
                printf("%d   ",a->child->data);
                a = a -> next;
            }
            ptr = ptr -> next;
        }
    }
}

void main(){
    printf("\nEnter the number of nodes: ");
    scanf("%d",&noof_nodes);
    creategraph();
    display();
}