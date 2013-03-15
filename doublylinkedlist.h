#include<stdio.h>
#include<string.h>

typedef struct student{
     int id;
     char first_name[80];
     char last_name[80];
     int quiz;
     int hw;
     int attendance;
     int final_exam;
     int grade;
}Student;

typedef struct node{
     Student data;
     struct node *next;
     struct node *prev;
}Node;

void addStudent(Node *pointer, Student data); 
Student findStudent(Node *pointer, int key); 
void deleteStudent(Node *pointer, int id); 
int getSize(Node *pointer);

