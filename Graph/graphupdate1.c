#include <stdio.h>
#include <malloc.h>

//in the code I have used word vertex for the vertex in the graph

int noof_vertices;

//structure for creating adjacent edges
struct adj{
    struct vertex *parent;
    struct vertex *child;
    struct adj *next;
};

//structure for a vertex 
struct vertex{
    int data;
    struct vertex *next;
    struct adj *head;
};

//initializing the graph structure
struct vertex *start = NULL;

//funtion to create a vertex 
void createvertex(int x){
    struct vertex *new,*ptr;
    new = (struct vertex *)malloc(sizeof(struct vertex));
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

void main(){
    printf("\nEnter the number of vertices: ");
    scanf("%d",&noof_vertices);
    int opt;
    do{
        printf("\n-----------------------------------------------------------------------------------\n");
        printf("MAIN MENUE\n1.CREATE GRAPH\t2.DISPLAY\t3.INSERT A NEW VERTEX\t4.INSERT EDGES\t5.DELETE AN EDGE\t6.CLEAR \t7.DELETE VERTEX\t8.EXIT");
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
                addvertex();
                break;
            case 4: 
                createdj();
                break;
            case 5:
                printf("\nWhich edge do you need to delete?");
                printf("\nEnter the first vertex: ");
                int x,y;
                scanf("%d",&x);
                struct vertex *ptr;
                ptr = start;
                while(ptr!=NULL){
                    if(ptr->data == x)
                        break;
                    ptr = ptr -> next;
                }
                if(ptr == NULL)
                    printf("\nERROR:: Vertex not found");
                else if(ptr->data == x){
                    printf("\nEnter the second vertex: ");
                    scanf("%d",&y);
                    deletedj(ptr,y);
                }
                break;
            case 6: 
                printf("\nWhich vertex do you want to clear? ");
                int a;
                scanf("%d",&a);
                struct vertex *pptr;
                pptr = start;
                while(pptr!=NULL){
                    if(pptr->data == a)
                        break;
                    pptr = pptr -> next;
                }
                if(pptr == NULL)
                    printf("\nERROR:: Vertex not found");
                else if(pptr->data == a){
                    deletevertexdj(pptr);
                }
                break;
            case 7:
                printf("\nWhich vertex do you want to delete? ");
                int b;
                scanf("%d",&b);
                struct vertex *cptr;
                cptr = start;
                while(cptr!=NULL){
                    if(cptr->data == b)
                        break;
                    cptr = cptr -> next;
                }
                if(cptr == NULL)
                    printf("\nERROR:: Vertex not found");
                else if(cptr->data == b){
                    deletevertex(cptr);
                }
                break;
            case 8:
                break;
            default:
                printf("\nERROR:: Enter a valid option\n");
        }
    }while(opt != 8);
}