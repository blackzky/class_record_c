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

#define STUDENTS_PER_PAGE 15

int SELECTOR = 0;
int STATE = 0;
int SIZE = 0;
int INDEX = 0;
int INPUT = 0;
int CURRENT_STUDENT = 0;

/*temp*/
char *CLASSES[80] = {"ComE 321", "ComE 322", "Come 323"};
char *STUDENTS[80] = {"Carlo Sarile", "Neil David", "Eric Tampos", "Four", "Five", "Sixe", "seven", "eight", "nine", "ten", "11", "12", "13", "14", "15"};

char *MENU_OPTIONS[80] = {"Select a Class", "Add a new Class", "Delete a Class", "Exit"};
char *STUDENT_OPTIONS[80] = {"Add a new student", "Find a student", "Sort list", "Next list", "Previous list", "Menu"};

char *CURRENT_CLASS = "";

typedef struct Student{
	int id;
	char *name;
	int quizzes;
	int hw;
	int attendance;
	int final_exam;
	int grade;
}student;


char isSelected(int id){ return ( (SELECTOR == id) ? 'O' : ' '); }

int cycleInput(){
	INPUT = getch();	
	if(INPUT == UP_KEY)		SELECTOR = (SELECTOR <= 0) ? (SIZE-1) : (SELECTOR - 1); 
	else if(INPUT == DOWN_KEY)	SELECTOR = (SELECTOR + 1) % SIZE; 

	return (INPUT == ENTER_KEY) ? ENTER_KEY : -1;
}

void showMainMenu(){
	SIZE = 4;
	system("cls");
	printf("Welcome (Navigate using the arrow keys, press enter to select)\n");
	for(INDEX = 0; INDEX < SIZE; INDEX++){
		printf("[%c] %s\n", isSelected(INDEX), MENU_OPTIONS[INDEX]);
	}
}

void handleMainMenu(){
	do{
		showMainMenu();
	}while(cycleInput() != ENTER_KEY);

	switch(SELECTOR){
		case 0: STATE = SELECT_CLASS; 	break;	
		case 1: STATE = ADD_CLASS; 	break;	
		case 2: STATE = DELETE_CLASS; 	break;	
		case 3: STATE = EXIT;		break;	
	}
}

void showClassList(){
	for(INDEX = 0; INDEX < 3; INDEX++){
		printf("[%c] %s\n", isSelected(INDEX), CLASSES[INDEX]);
	}
}

void showSelectClass(){
	SIZE = 4;
	system("cls");
	printf("Select a Class\n");
	showClassList();
	printf("[%c] %s\n", isSelected(SIZE - 1), "Menu");
}

void handleSelectClass(){
	do{
		showSelectClass();
	}while(cycleInput() != ENTER_KEY);

	if(SELECTOR == SIZE-1){
		STATE = MENU;
	}else{
		CURRENT_CLASS =  CLASSES[SELECTOR];		
		STATE = SELECT_STUDENT;
	}
}

void handleAddClass(){ //incomplete
	printf("Enter class name (ESC to cancel): ");
	char name[100];
	scanf ("%[^\n]%*c", name);
	printf("%s", name);
	STATE = MENU;
	printf("\nClass was added! (Press any key to return to the menu)");
	getch();
}

void showDeleteClass(){
	SIZE = 4;
	system("cls");
	printf("Select a Class you want to delete:\n");
	showClassList();
	printf("[%c] %s\n", isSelected(SIZE - 1), "Cancel");
}

void handleDeleteClass(){//incomplete
	do{
		showDeleteClass();
	}while(cycleInput() != ENTER_KEY);

	if(SELECTOR == 3){
		STATE = MENU;
	}else{
		printf("selected class: %s", CLASSES[SELECTOR]);		
	}
}

void showStudentList(int start, int end){
	for(INDEX = start; INDEX < end; INDEX++){
		printf("[%c] %s\n", isSelected(INDEX), STUDENTS[INDEX]);
	}
}

void showSelectStudent(){
	SIZE = 6 + STUDENTS_PER_PAGE;
	system("cls");
	printf("Class: %s\nSelect a Student: (Showing %d to %d)\n", 
		CURRENT_CLASS, CURRENT_STUDENT, (CURRENT_STUDENT + STUDENTS_PER_PAGE)-1);
	showStudentList(CURRENT_STUDENT, STUDENTS_PER_PAGE);
	printf("\nSelect an option: \n");
	for(INDEX = 0; INDEX < 6; INDEX++){
		printf("[%c] %s\n", isSelected(INDEX + STUDENTS_PER_PAGE), STUDENT_OPTIONS[INDEX]);
	}
}

void handleSelectStudent(){
	do{
		showSelectStudent();
	}while(cycleInput() != ENTER_KEY);

	if(SELECTOR == SIZE - 1){//menu
		STATE = MENU;
	}else if(SELECTOR == SIZE - 2){//prev
		printf("prev");
	}else if(SELECTOR == SIZE - 3){//next
		printf("next");
	}else if(SELECTOR == SIZE - 4){//sort
		printf("sort");
	}else if(SELECTOR == SIZE - 5){//find
		printf("find");
	}else if(SELECTOR == SIZE - 6){//add
		printf("add");
	}else{
		printf("selected student: %s", STUDENTS[SELECTOR]);		
	}

}

void handleState(){
	SELECTOR = 0;
	system("cls");
	switch(STATE){
		case MENU:		handleMainMenu(); 		break;
		case SELECT_CLASS: 	handleSelectClass(); 		break;
		case ADD_CLASS: 	handleAddClass(); 		break;
		case DELETE_CLASS: 	handleDeleteClass(); 		break;
		case SELECT_STUDENT: 	handleSelectStudent(); 		break;
		case EXIT: 		printf("Goodbye!\n"); exit(0); break;
	}
	handleState();	
}
int main(){
	handleState();
	getch();
	return 0;
}

