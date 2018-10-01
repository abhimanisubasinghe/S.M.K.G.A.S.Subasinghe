#include <stdio.h>
#include <malloc.h>
#include "graphlib.h"

void main(){
    int opt,del;
    do{
        printf("\n-----------------------------------------------------------------------------------\n");
        printf("MAIN MENUE\n1.CREATE GRAPH\t2.DISPLAY\t3.INSERT A NEW VERTEX\t4.INSERT EDGES\t5.DELETE AN EDGE\t6.CLEAR \t7.DELETE VERTEX\t8.BFS\t9.DFS\t10.DELETE GRAPH\t11.EXIT\t12.DIJKSTRA\n");
        printf("\nInsert your option: ");
        scanf("%d",&opt);
        switch (opt){
            case 1:
                if(start!=NULL){
                    if(deletegraph() == 2){
                        printf("\nEnter the number of vertices: ");
                        scanf("%d",&noof_vertices);
                        creategraph();
                    }
                }
                else{
                    printf("\nEnter the number of vertices: ");
                    scanf("%d",&noof_vertices);
                    creategraph();
                }
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
                printf("\nEnter the source node: ");
                int home;
                scanf("%d",&home);
                struct vertex *phome;
                phome = start;
                while(phome != NULL){
                    if(phome->data==home)
                        break;
                    phome = phome -> next;
                }
                printf("\nBFS:\t");
                BFS(phome);
                printf("\n");
                break;
            case 9:
                printf("\nEnter the source node: ");
                int dhome;
                scanf("%d",&dhome);
                struct vertex *pdhome;
                pdhome = start;
                while(pdhome != NULL){
                    if(pdhome->data==dhome)
                        break;
                    pdhome = pdhome -> next;
                }
                printf("\nDFS:\t");
                DFS(pdhome);
                printf("\n");
                break;
            case 10:
                deletegraph();
                break;
            case 11:
                break;
            case 12:
                printf("\nEnter the source node: ");
                int dijhome;
                scanf("%d",&dijhome);
                struct vertex *pdijhome;
                pdijhome = start;
                while(pdijhome != NULL){
                    if(pdijhome->data == dijhome)
                        break;
                    pdijhome = pdijhome -> next;
                }
                //printf("\nDFS:\t");
                //printf("\npass1 %d",pdijhome->data);
                rotate(pdijhome);
                dijkstra(pdijhome);
                un = NULL;
                printf("\n");
                break;
            default:
                printf("\nERROR:: Enter a valid option\n");
        }
    }while(opt != 11);
}
