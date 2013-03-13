#include<stdio.h>
#include<stdlib.h>

typedef struct{
     int id;
     char *first_name;
     char *last_name;
     int quizzes;
     int hw;
     int attendance;
     int final_exam;
     int grade;
}Student;

typedef struct node{
     void* data;
     struct node *next;
     struct node *prev;
}Node;

typedef struct class{
     int id;
     char *name;
     Node *students;
}Class;


void insert(Node *pointer, void* data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (Node *)malloc(sizeof(Node));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     pointer->data = data;
     pointer->next = NULL;
}

void* find(Node *pointer, void* key) {
     pointer =  pointer -> next; 
     while(pointer!=NULL) {
          if(pointer->data == key){ 
               return pointer->data;
          }
          pointer = pointer -> next;
     }
     return NULL;
}
void delete(Node *pointer, void* data) {
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

int main(){

     return 0;
}
