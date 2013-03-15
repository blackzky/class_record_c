#include <stdio.h>
#include "doublylinkedlist.h"

/* KEYCODES */
#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75 
#define RIGHT_KEY 77
#define ENTER_KEY 13

int SELECTOR = 0;

/* Menus */
char *STUDENT_MENU[80] = {"View all students", "Add a student", "Edit a student", "Delete a student", "Exit"};

/* Helper function */
char *getSelector(int id){ return ( (SELECTOR == id) ? ">>" : "  "); }

/* Helper function */
int cycleInput(int size){
	int INPUT = getch();	
	if(INPUT == UP_KEY)		SELECTOR = (SELECTOR <= 0) ? (size-1) : (SELECTOR - 1); 
	else if(INPUT == DOWN_KEY)	SELECTOR = (SELECTOR + 1) % size; 

	return (INPUT == ENTER_KEY) ? ENTER_KEY : -1;
}

/* Helper function */
void displayOptions(char *options[], int start, int end){
     for(start = 0; start < end; start++){
          printf("\t\t\t   %s %s\n",getSelector(start), options[start]);
     }
}

/* Menu (Students) */
void showStudentOptions(){
     int size = 5,
         start = 0,
         end = size;
	system("cls");
     printf("\n\t\t\t\tClass Record\n\n");
	printf("\t   (Use the arrow keys to navigate and press enter to select)\n\n");
     displayOptions(STUDENT_MENU, start, end);
}

/* Input handler (Students) */
void handleStudentMenuInput(){
     int size  = 5;
	int in = 0;
	do{
		showStudentOptions();
          printf("\n%s\n", STUDENT_MENU[SELECTOR]);
	}while(cycleInput(size)!= ENTER_KEY);
}


int main(){
     handleStudentMenuInput(5);
	getch();
	return 0;
}
