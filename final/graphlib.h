#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define INFI 9999

//number of vertices are input by the user
int noof_vertices;

//structure for a stack data type
//this is used in the DFS traversal
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

//structure for a stack data type
//this is used in the BFS traversal
struct queue{
    int qdata;
    //int dis;
    struct queue *qnext;
};

struct list{
    int distance;
    struct vertex *ldata;
    struct list *next;
};

//initializing the graph structure
struct vertex *start = NULL;
//initializing the queue structure
struct queue *qstart = NULL;
//initializing the stack structure
struct stack *stop = NULL;
struct list *lstart = NULL;

//funtion to add data in to the queue
void enqueue(int x){
    struct queue *newnode;
    newnode = (struct queue *)malloc(sizeof(struct queue));
    newnode -> qdata = x;
    //newnode -> dis = d;
    newnode -> qnext = NULL;
    if(qstart==NULL){
        qstart = newnode;
    }
    else{
        struct queue *ptr;
        ptr = qstart;
        while(ptr->qnext!=NULL)
            ptr = ptr -> qnext;
        ptr -> qnext = newnode;
    }
}

//funtion to delete nodes from the queue
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

//funtion to add data into the stack
void push(int x){
    struct stack *newnode;
    newnode = (struct stack *)malloc(sizeof(struct stack));
    newnode -> sdata = x;
    newnode -> snext = NULL;
    if(stop==NULL){
        stop = newnode;
    }
    else{
        newnode -> snext = stop;
        stop = newnode;
    }
}

//funtion to delete data from the stack
int pop(){
    struct stack *ptr;
    ptr = stop;
    if(stop == NULL)
        printf("\nERROR::Stack is empty");
    else{
        stop = stop -> snext;
    }
    return ptr -> sdata;
}

void addlist(struct vertex *x,int y){
    struct list *newnode,*ptr,*preptr;
    newnode = (struct list *)malloc(sizeof(struct list));
    ptr = lstart; 
    while(ptr!=NULL){
        preptr = ptr;
        if(ptr->ldata->data==x->data)
            break;
        ptr = ptr -> next;
    }
    if(ptr==NULL){
        newnode -> ldata = x;
        newnode -> next = NULL;
        if(lstart==NULL){
            newnode -> distance = 0;
            lstart = newnode;
        }
        else{
            preptr -> next = newnode;
            newnode -> distance = y;
        }
    }
    else{
        if(y<ptr->distance)
            ptr -> distance = y;
    }
}

void printlist(){
    struct list *ptr;
    ptr = lstart;
    while(ptr!=NULL){
        printf("\n%d\t%d\n",ptr->ldata,ptr->distance);
    }
}

//funtion to create a vertex 
void createvertex(int x){
    struct vertex *newnode,*ptr;
    newnode = (struct vertex *)malloc(sizeof(struct vertex));
    newnode -> data = x;
    newnode -> status = 0;
    newnode -> next = NULL;
    newnode -> head = NULL;
    ptr = start;
    if(start == NULL)
        start = newnode;
    else{
        while(ptr->next != NULL)
            ptr = ptr -> next;
        ptr -> next = newnode;
    }
}

//funtion to add adjacent vertex to given vertex
void createadj(struct vertex *p){
    int noof_adj;
    printf("\nHow many adj vertices: ");
    scanf("%d",&noof_adj);
    int i = noof_adj;
    while(i!=0){
        struct adj *newnode;
        newnode = (struct adj *)malloc(sizeof(struct adj));
        newnode -> parent = p;
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
            free(newnode);
        }
        else if( ptr -> data == adjvertex ){
            printf("\nEnter the weight of the edge: ");
            int w;
            scanf("%d",&w);
            newnode -> d = w;
            newnode -> child = ptr;
            newnode -> next = NULL;
            if(p->head == NULL)
                p -> head = newnode;
            else{
                struct adj *a;
                a = p -> head;
                while(a->next!=NULL)
                    a = a -> next;
                a -> next = newnode;
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

//funtion to add a new vertex into an existing graph
void addvertex(){
    printf("\nCreating a newnode vertex");
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

//function to create an edge between existing vertices
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

//funtion to delete an existing edge
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

//this funtion will delete the edges that have been created with given vertex
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

//this funtion will clear all the edges in the given vertex
void clearvertex(struct vertex *p){
    struct adj *a,*b;
    a = p -> head;
    while(a!=NULL){
        b = a;
        deletedj(p,a->child->data);
        a = b -> next;
    }
}

//this funtion will delete the vertex from the graph
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

//this funtion is used to set status back to 0 after a traversal
void remark(){
    struct vertex *restate;
    restate = start;
    while(restate!=NULL){
        restate->status = 0;
        restate = restate -> next;
    }
}


/*
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
                //printf("\n");
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
    remark();
}*/

//from a given vertex this funtion will do the BFS traversal
void BFS(struct vertex *x){
    struct vertex *ptr;
    ptr = x;
    //while(ptr != NULL){
        if(ptr->status == 0){
            printf("\nVertices reachable from source\t");
            enqueue(ptr->data);
            ptr -> status = 1;
            while(qstart!=NULL){
                struct adj *a;
                struct vertex *search;
                search = start;
                while(search->data!=qstart->qdata)
                    search = search -> next;
                a = search -> head;
                //printf("\n");
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
        //ptr = ptr -> next;
    //}
    remark();
}

//this funtion will do the DFS traversal from a given vertex
void DFS(struct vertex *x){
    struct vertex *ptr;
    ptr = x;
    //while(ptr != NULL){
        if(ptr->status == 0){
            printf("\nReachable \t");
            push(ptr->data);
            ptr -> status = 1;
            while(stop!=NULL){
                struct adj *a;
                struct vertex *search;
                search = start;
                while(search->data!=stop->sdata)
                    search = search -> next;
                int out;
                out = pop();
                struct vertex *outv;
                outv = start;
                while(outv->data!=out)
                    outv = outv -> next;
                if(outv->status==1){
                    outv -> status = 2;
                    printf("%d\t",out);
                }
                a = search -> head;
                while(a!=NULL){
                    if(a->child->status==0){
                        a->child->status = 1;
                        push(a->child->data);
                    }
                    a = a -> next;
                }
                
            }
        }
        //ptr = ptr -> next;
    //}
    remark();        

}

//funtion to delete an existing graph
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

//still working ...
/*struct STP1{
    struct vertex *data;
    struct STP1 *next;
};

struct STP1 * stpstart1 = NULL;

void stp1push(struct vertex *x){
    struct STP1 *newnode;
    newnode = (struct STP1 *)malloc(sizeof(struct STP1));
    newnode -> data = x;
    newnode -> next = NULL;
    if(stpstart1==NULL)
        stpstart1 = newnode;
    else{
        newnode -> next = stpstart1;
        stpstart1 = newnode;
    }
}

void stp1print(){
    struct STP1 *ptr;
    ptr = stpstart1;
    while(ptr!=NULL){
        printf("\n%d\t%d",ptr->data->data,ptr->data->status);
    }
}

struct vertex * stp1pop(){
    struct STP1 *ptr;

}

int searchstp1(struct vertex *x){
    struct STP1 *ptr;
    int flag = 0;
    ptr = stpstart1;
    while(ptr!=NULL){
        if(ptr->data->data==x->data){
            flag = 1;
            break;
        }
        ptr = ptr -> next;
    }
    return flag;
}

void redes(){
    struct vertex *restate;
    restate = start;
    while(restate!=NULL){
        restate->status = INFI;
        restate = restate -> next;
    }
}

struct vertex * minweight(struct vertex *x){
    struct vertex *ptr,*min;
    min = ptr = x;
    while(ptr->next !=NULL){
        int check;
        check = searchstp1(ptr);
        if(((ptr->status)<(min->status)) && check==0)
            min = ptr;
        ptr = ptr -> next;
    }
    return min;
}

void dijkstra(struct vertex *source){
    struct vertex * ptr;
    redes();
    source -> status = 0;
    ptr = minweight(source);
    stp1push(ptr);
    while(ptr->status!=INFI){
        struct adj *a;
        a = ptr -> head;
        while(a!=NULL){
            if((a->child->status)==INFI){
                (a->child->status) = (stpstart1 ->data->status) + (a->d);
            }
            else{
                if((a->child->status)>((stpstart1 ->data->status) + a->d))
                    (a->child->status) = (stpstart1 ->data->status) + (a->d);
            }
            a = a->next;
        }
        ptr = minweight(start);
        stp1push(ptr);
    }
    stp1print();
    stpstart1 = NULL;
    remark();
}*/