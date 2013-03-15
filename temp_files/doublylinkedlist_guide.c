#include<stdio.h>
#include<stdlib.h>

#define UP_KEY 107
#define DOWN_KEY 106 
#define ENTER_KEY 111

int selector = 0;
int isRunning = 1;

typedef struct node{
     int data;
     struct node *next;
     struct node *prev;
}Node;

void insert(Node *pointer, int data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (Node *)malloc(sizeof(Node));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     pointer->data = data;
     pointer->next = NULL;
}

int find(Node *pointer, int key) {
     pointer =  pointer -> next; 
     while(pointer!=NULL) {
          if(pointer->data == key){ 
               return 1;
          }
          pointer = pointer -> next;
     }
     return 0;
}
void delete(Node *pointer, int data) {
     while(pointer->next!=NULL && (pointer->next)->data != data) {
          pointer = pointer -> next;
     }
     if(pointer->next==NULL) {
          printf("Element %d is not present in the list\n",data);
          return;
     }
     Node *temp;
     temp = pointer -> next;
     pointer->next = temp->next;
     temp->prev =  pointer;
     free(temp);
     return;
}


int getSize(Node *pointer){
     int count = 0;
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
          count++;
     }
     return count;
}

/*PRINT LIST ---for debugging */
void print(Node *pointer) {
     if(pointer==NULL) {
          printf("Empty\n");
          return;
     }
     printf("%d ",pointer->data);
     print(pointer->next);
}

/*for GUI*/
char getSelector(int id){
	return ( (selector == id) ? 'x' : ' ');
}
void showOptions(){
	system("cls");
	printf("Use the 'j' for down, 'k' for up and 'o' to select:\n");
	printf("[%c] Add\n", getSelector(0));
	printf("[%c] Edit\n", getSelector(1));
	printf("[%c] View\n", getSelector(2));
	printf("[%c] Delete\n", getSelector(3));
	printf("[%c] Find\n", getSelector(4));
	printf("[%c] Exit\n", getSelector(5));
}

void handleInput(int size){
	int in = 0;
	do{
		showOptions();
		in = getch();	
		if(in == UP_KEY)	selector = (selector <= 0) ? (size-1) : (selector - 1); 
		else if(in == DOWN_KEY)	selector = (selector + 1) % size; 
	}while(in != ENTER_KEY);
}


int main() {
     int data, newdata;
     /* start always points to the first Node of the linked list.
        temp is used to point to the last Node of the linked list.*/
     Node *head,*tail;
     head = (Node *)malloc(sizeof(Node)); 
     tail = head;
     tail -> next = NULL;
     tail -> prev = NULL;

     do{
          handleInput(6);
          printf("\nCurrent size of list: %d\n", getSize(head));

          switch(selector){
               case 0:
                    printf("Enter data: ");
                    scanf("%d",&data);
                    insert(head,data);
                    printf("\nData added.");
                    free(data);
                    break;
               case 1:
                    printf("Select data to edit: ");
                    scanf("%d",&data);
                    printf("Enter new data: ");
                    scanf("%d",&newdata);
                    printf("\nData removed.");
                    free(data);
                    break;
               case 2: 
                    printf("The list is ");
                    print(head->next);
                    printf("\n");
                    break;
               case 3: 
                    printf("Select data to delete: ");
                    scanf("%d",&data);
                    delete(head,data);
                    printf("\nData removed.");
                    free(data);
                    break;
               case 4:
                    printf("Enter data to find: ");
                    scanf("%d",&data);
                    int status = find(head,data);
                    if(status) {
                         printf("Element Found\n");
                    } else {
                         printf("Element Not Found\n");
                    }
                    free(data);
                    break;
     
               case 5: printf("Exiting program...\n");isRunning = 0; break;
          }
          getch();
     }while(isRunning);

     return 0;
}

