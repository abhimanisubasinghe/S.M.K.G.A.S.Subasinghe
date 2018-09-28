#include <stdio.h>
#include <malloc.h>
#include <string.h>
//#include "graphdata1.h"
//#include "bfslib.h"

int noof_vertices;

struct queue{
    int qdata;
    struct queue *qnext;
};

struct stack{
    int sdata;
    struct stack *snext;
};

//structure for creating adjacent edges
struct adj{
    int d;
    struct vertex *parent;
    struct vertex *child;
    struct adj *next;
};

//structure for a vertex 
struct vertex{
    int data;
    int status;
    struct vertex *next;
    struct adj *head;
};

//initializing the graph structure
struct vertex *start = NULL;
struct queue *qstart = NULL;
struct stack *sstart = NULL;

void enqueue(int x){
    struct queue *new;
    new = (struct queue *)malloc(sizeof(struct queue));
    new -> qdata = x;
    new -> qnext = NULL;
    if(qstart==NULL){
        qstart = new;
    }
    else{
        struct queue *ptr;
        ptr = qstart;
        while(ptr->qnext!=NULL)
            ptr = ptr -> qnext;
        ptr -> qnext = new;
    }
}

int dequeue(){
    struct queue *ptr;
    ptr = qstart;
    if(qstart==NULL)
        printf("\nERROR::Queue is empty");
    else{
        qstart = qstart -> qnext; 
    }
    return ptr->qdata;
}

void push(int x){
}

//funtion to create a vertex 
void createvertex(int x){
    struct vertex *new,*ptr;
    new = (struct vertex *)malloc(sizeof(struct vertex));
    new -> data = x;
    new -> status = 0;
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
void createadj(struct vertex *p){
    int noof_adj;
    printf("\nHow many adj vertices: ");
    scanf("%d",&noof_adj);
    int i = noof_adj;
    while(i!=0){
        struct adj *new;
        new = (struct adj *)malloc(sizeof(struct adj));
        new -> parent = p;
        printf("\nEnter the adj vertex: ");
        int adjvertex;
        scanf("%d",&adjvertex);
        struct vertex *ptr;
        ptr = start;
        while(ptr != NULL){
            if(ptr -> data == adjvertex)
                break;
            ptr = ptr -> next;
        }
        if(ptr == NULL){
            printf("\nERROR: Vertex not found");
            free(new);
        }
        else if( ptr -> data == adjvertex ){
            new -> d = 1;
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
    int i = noof_vertices;
    while(i!=0){
        int x;
        printf("\nInsert data: ");
        scanf("%d",&x);
        createvertex(x);
        i--;
    }
    printf("\nVertexs have been recorded");
    struct vertex *ptr;
    ptr = start;
    while(ptr != NULL){
        printf("\nRecording adj vertex details of %d",ptr -> data);
        createadj(ptr);
        ptr = ptr -> next;
    }
}

void addvertex(){
    printf("\nCreating a new vertex");
    int x;
    printf("\nInsert data: ");
    scanf("%d",&x);
    createvertex(x);
    printf("\nVertex has been recorded");
    struct vertex *ptr;
    ptr = start;
    while(ptr -> next != NULL)
        ptr = ptr -> next;
    printf("\nRecording adj vertex details of %d",ptr -> data);
    createadj(ptr);
}

//funtion to display the graph
void display(){
    printf("\nGRAPH");
    struct vertex *ptr;
    ptr = start;
    if(start == NULL )
        printf("\nERROR: Graph is empty");
    else{
        while(ptr!=NULL){
            printf("\nVertex: %d\t\t",ptr->data);
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
    struct vertex *ptr;
    ptr = start;
    printf("\nTo which vertex do you need to add an edge: ");
    int x;
    scanf("%d",&x);
    while(ptr != NULL){
        if(ptr -> data == x)
            break;
        ptr = ptr -> next;
    }
    if( ptr == NULL )
        printf("\nERROR: There is no such vertex");
    else if(ptr->data == x){
        createadj(ptr);
    }
}

void deletedj(struct vertex *p,int x){
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

void deletevertexdj(struct vertex *p){
    struct vertex *ptr;
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

void clearvertex(struct vertex *p){
    struct adj *a,*b;
    a = p -> head;
    while(a!=NULL){
        b = a;
        deletedj(p,a->child->data);
        a = b -> next;
    }
}

void deletevertex(struct vertex *p){
    deletevertexdj(p);
    clearvertex(p);
    struct vertex *ptr,*preptr;
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

void BFS(){
    struct vertex *ptr;
    ptr = start;
    while(ptr != NULL){
        if(ptr->status == 0){
            printf("\ncycle\t");
            enqueue(ptr->data);
            ptr -> status = 1;
            while(qstart!=NULL){
                struct adj *a;
                struct vertex *search;
                search = start;
                while(search->data!=qstart->qdata)
                    search = search -> next;
                a = search -> head;
                while(a!=NULL){
                    if(a->child->status==0){
                        a->child->status = 1;
                        enqueue(a->child->data);
                    }
                    a = a -> next;
                }
                int out;
                out = dequeue();
                struct vertex *outv;
                outv = start;
                while(outv->data!=out)
                    outv = outv -> next;
                if(outv->status==1){
                    outv -> status = 2;
                    printf("%d\t",out);
                }
            }
        }
        ptr = ptr -> next;
    }
    struct vertex *restate;
    restate = start;
    while(restate!=NULL){
        restate->status = 0;
        restate = restate -> next;
    }

}

int deletegraph(){
    char x[2];
    printf("\nAre you sure you want to delete the existing graph?(Y\\N) ");
    scanf("%s",x);
    if((strcmp(x,"y")==0) || (strcmp(x,"Y")==0)){
        start = NULL;
        printf("\nExisting Graph is deleted");
        return 2;
    }
    else if((strcmp(x,"n")==0) || (strcmp(x,"N")==0)){
        printf("\nExisting Graph is not deleted");
        return 1;
    }
    else{
        printf("\nERROR:: Enter a valid choice");
        deletegraph();
    }
}