#include <stdio.h>
#include <malloc.h>
#include "tstlib.h"
//#include "bfslib.h"

void main(){
    int opt,del;
    do{
        printf("\n-----------------------------------------------------------------------------------\n");
        printf("MAIN MENUE\n1.CREATE GRAPH\t2.DISPLAY\t3.INSERT A NEW VERTEX\t4.INSERT EDGES\t5.DELETE AN EDGE\t6.CLEAR \t7.DELETE VERTEX\t8.BFS\t9.DELETE GRAPH\t10.EXIT");
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
                //creategraph();
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
                printf("\nBFS:\t");
                BFS();
                printf("\n");
                break;
            case 9:
                deletegraph();
                break;
            case 10:
                break;
            default:
                printf("\nERROR:: Enter a valid option\n");
        }
    }while(opt != 10);
}