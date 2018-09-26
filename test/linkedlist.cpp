#include <iostream>
#include <malloc.h>
#include <string.h>

using namespace std;

class node{
    private:
        int data;
        class node *next;
    public:
        void createll(int);
        void printll();
        void deletenode(int);
};

node *head = NULL;

void node::createll(int x){
    struct node *ptr,*newnode;
    newnode = (struct node *)malloc(sizeof(struct node)); 
    newnode -> data = x;
    newnode -> next = NULL;
    if(head == NULL){
        head = newnode;
    }
    else{
        ptr = head;
        while(ptr -> next != NULL )
            ptr = ptr -> next;
        ptr ->  next = newnode;
    }
}

void node::printll(){
    int count = 0;
    struct node *ptr;
    ptr = head;
    if(head == NULL )
        cout << "\nERROR::link list is empty";
    else{
        cout << "\nData in the ll:\t";
        while(ptr != NULL){
            count ++;
            cout << ptr -> data << "   ";
            ptr = ptr -> next;
        }
        cout << endl << "Number of elements in the list: " << count << endl;
    }
}

void node::deletenode(int y){
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
        cout << endl << ptr -> data << " data is deleated from the list\n";
        free(ptr);
    }
    else{
        cout << "\nERROR::Node not found";
    }
}

int main(){
    int opt,x,y;
    node *a;
    do{
        cout <<  "\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "MAIN MENUE\n1.CREATE LINK LIST\t2.PRINT\t3.DELETE\t4.INSERT DATA IN THE END\t5.EXIT";
        cout << "\nInsert your option: ";
        cin >> opt;
        switch (opt){
            case 1:
                cout << "\nInsert elements to be entered in the link list\nenter -1 to finish entering data\n";
                cout << "Insert data: ";
                cin >> x;
                while(x != -1){
                    a -> createll(x);
                    cout << "Insert data: ";
                    cin >> x;
                }
                break;
            case 2:
                a -> printll();
                break;
            case 4: 
                cout << "\nInsert data: ";
                cin >> x;
                a -> createll(x);
                break;
            case 3:
                if ( head == NULL){
                    cout << "ERROR:: No data found\n";
                    break;
                }
                else{
                    cout <<  "\nWhich node do you want to delete?";
                    a -> printll();
                    cin >>  y;
                    a -> deletenode(y);
                    break;
                }
            case 5:
                break;
            default:
                printf("\nERROR:: Enter a valid option\n");
        }
    }while(opt != 5);
    return 0;
}