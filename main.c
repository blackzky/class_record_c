#include <stdio.h>
#include <string.h>

#define MENU 0
#define SELECT_CLASS 1
#define ADD_CLASS 2
#define DELETE_CLASS 3
#define SELECT_STUDENT 4
#define EXIT 9

#define UP_KEY 72
#define DOWN_KEY 80
#define ENTER_KEY 13

int SELECTOR = 0;

char getSelector(int id){
	return ( (SELECTOR == id) ? 'x' : ' ');
}

int STATE = 0;
int index = 0;
char *CLASSES[80] = {"ComE 321", "ComE 322", "Come 323"};
char *STUDENTS[80] = {"Carlo Sarile", "Neil David", "Eric Tampos"};


typedef struct Student{
	int id;
	char *name;
	int quizzes;
	int hw;
	int attendance;
	int final_exam;
	int grade;
}student;

int getInput(int min, int max){
	int input = getch();
	input = input - 48;
	if((input >= min) && (input <= max)){
		return input;
	}else{
		printf("\nInvalid input! Try again: ");
		return getInput(min, max);
	}

}

void showMenu(){
	printf("Welcome\n");
	printf("[1] Select a Class\n");
	printf("[2] Add a new Class\n");
	printf("[3] Delete a Class\n");
	printf("[4] Exit\n");
	printf("What would you like to do: ");
	handleMenu(getInput(1, 4));
}

void handleMenu(int option){
	switch(option){
		case 1: STATE = SELECT_CLASS; 	break;	
		case 2: STATE = ADD_CLASS; 	break;	
		case 3: STATE = DELETE_CLASS; 	break;	
		case 4: STATE = EXIT;		break;	
	}
}

/*unfinished*/
void showClassList(){
	for(index = 0; index < 3; index++){
		printf("[%d] %s\n", index + 1, CLASSES[index]);
	}
		
}

void showSelectClass(){
	printf("Select a Class\n");
	showClassList();
	printf("[4] Menu\n");
	printf("What would you like to do: ");
	handleSelectClass(getInput(1, 4));
}

/*unfinished*/
void handleSelectClass(int option){
	if(option == 4){
		STATE = MENU;
	}else{
		selectClass(option);
		STATE = SELECT_STUDENT;
	}
}

/*unfinished*/
void showAddClass(){
	printf("Enter class name (ESC to cancel): ");
	char name[100];
	scanf ("%[^\n]%*c", name);
	printf("%s", name);
	STATE = MENU;
	printf("\nClass was added! (Press any key to return to the menu)");
	getch();
}

/*unfinished*/
void showDeleteClass(){
	printf("Select a Class you want to delete:\n");
	showClassList();
	printf("[4] Cancel\n");
	printf("Choice: ");
	handleSelectClass(getInput(1, 4));
}

void selectClass(int class_id){
	printf("\nYou selected class: %s\n", CLASSES[class_id-1]);
}

void showStudentList(){
	for(index = 0; index < 3; index++){
		printf("[%d] %s\n", index + 1, STUDENTS[index]);
	}
}

void showSelectStudent(){
	printf("Select a Student: (Showing %d to %d)\n", 1, 5);
	showStudentList();
	printf("[5] Add a new student\n");
	printf("[6] Find a student\n");
	printf("[7] Sort list\n");
	printf("[8] Next List\n");
	printf("[9] Previous List\n");
	printf("[0] Menu\n");
	printf("What would you like to do: ");
	handleSelectClass(getInput(1, 4));
}

void handleState(){
	system("cls");
	switch(STATE){
		case MENU:		showMenu(); 		break;
		case SELECT_CLASS: 	showSelectClass(); 	break;
		case ADD_CLASS: 	showAddClass(); 	break;
		case DELETE_CLASS: 	showDeleteClass(); 	break;
		case SELECT_STUDENT: 	showSelectStudent(); 	break;
		case EXIT: 		printf("Goodbye!\n"); exit(0); break;
	}
	handleState();	
}
int main(){
	int index = 0;
	handleState();
	getch();
	return 0;
}

