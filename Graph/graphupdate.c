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
    printf("\nCreating a new node");
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
    printf("\nGRAPH");
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
    printf("\n");
}

void createdj(){
    struct node *ptr;
    ptr = start;
    printf("\nTo which node do you need to add an edge: ");
    int x;
    scanf("%d",&x);
    while(ptr != NULL){
        if(ptr -> data == x)
            break;
        ptr = ptr -> next;
    }
    if( ptr == NULL )
        printf("\nERROR: There is no such node");
    else if(ptr->data == x){
        createadj(ptr);
    }
}

void deletedj(struct node *p,int x){
    struct adj *ptr,*preptr;
    ptr = p -> head;
    while(ptr!=NULL){
        if(ptr->child->data == x)
            break;
        preptr = ptr;
        ptr = ptr -> next;
    }
    if(ptr == NULL)
        printf("\nERROR::Edge not found");
    else if(ptr->child->data == x){
        if(ptr==p->head){
            p->head = p->head->next;
            free(ptr);
        }
        else{
            preptr -> next = ptr -> next;
            free(ptr);
        }
    }
}

void deletenodedj(struct node *p){
    struct node *ptr;
    ptr = start;
    while(ptr != NULL){
        struct adj *a,*b;
        a = ptr -> head;
        while(a!=NULL){
            b = a;
            if(a->child->data==p->data){
                deletedj(ptr,p->data);
            }
            a = b->next;
        }
        ptr = ptr -> next;    
    }
}

void clearnode(struct node *p){
    struct adj *a,*b;
    a = p -> head;
    while(a!=NULL){
        b = a;
        deletedj(p,a->child->data);
        a = b -> next;
    }
}

void deletenode(struct node *p){
    deletenodedj(p);
    clearnode(p);
    struct node *ptr,*preptr;
    ptr = start;
    while(ptr!=p){
        preptr = ptr;
        ptr = ptr -> next;
    }
    if(ptr == start){
        start = start -> next; 
        free(ptr);
    }
    else{
        preptr -> next = ptr -> next;
        free(ptr);
    }
}

void main(){
    printf("\nEnter the number of nodes: ");
    scanf("%d",&noof_nodes);
    int opt;
    do{
        printf("\n-----------------------------------------------------------------------------------\n");
        printf("MAIN MENUE\n1.CREATE GRAPH\t2.DISPLAY\t3.INSERT A NEW NODE\t4.INSERT EDGES\t5.DELETE AN EDGE\t6.DELETE A NODE EDGES\t7.DELETE NODE\t8.EXIT");
        printf("\nInsert your option: ");
        scanf("%d",&opt);
        switch (opt){
            case 1:
                creategraph();
                break;
            case 2:
                display();
                break;
            case 3: 
                addnode();
                break;
            case 4: 
                createdj();
                break;
            case 5:
                printf("\nWhich edge do you need to delete?");
                printf("\nEnter the first node: ");
                int x,y;
                scanf("%d",&x);
                struct node *ptr;
                ptr = start;
                while(ptr!=NULL){
                    if(ptr->data == x)
                        break;
                    ptr = ptr -> next;
                }
                if(ptr == NULL)
                    printf("\nERROR:: Node not found");
                else if(ptr->data == x){
                    printf("\nEnter the second node: ");
                    scanf("%d",&y);
                    deletedj(ptr,y);
                }
                break;
            case 6: 
                printf("\nWhich node do you want to clear?");
                int a;
                scanf("%d",&a);
                struct node *pptr;
                pptr = start;
                while(pptr!=NULL){
                    if(pptr->data == a)
                        break;
                    pptr = pptr -> next;
                }
                if(pptr == NULL)
                    printf("\nERROR:: Node not found");
                else if(pptr->data == a){
                    deletenodedj(pptr);
                }
                break;
            case 7:
                printf("\nWhich node do you want to delete?");
                int b;
                scanf("%d",&b);
                struct node *cptr;
                cptr = start;
                while(cptr!=NULL){
                    if(cptr->data == b)
                        break;
                    cptr = cptr -> next;
                }
                if(cptr == NULL)
                    printf("\nERROR:: Node not found");
                else if(cptr->data == b){
                    deletenode(cptr);
                }
                break;
            case 8:
                break;
            default:
                printf("\nERROR:: Enter a valid option\n");
        }
    }while(opt != 8);
}