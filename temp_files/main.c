#include <stdio.h>
#include <string.h>

/* STATES */
#define MENU 0
#define SELECT_CLASS 1
#define ADD_CLASS 2
#define DELETE_CLASS 3
#define SELECT_STUDENT 4
#define EXIT 9

/* KEY CODES */
#define UP_KEY 72
#define DOWN_KEY 80
#define ENTER_KEY 13

#define STUDENTS_PER_PAGE 15

/* IDENTEFIERS */
int SELECTOR = 0,
    STATE = 0,
    SIZE = 0,
    INDEX = 0,
    INPUT = 0,
    CURRENT_STUDENT = 0,
    OCCURANCE = 0; 
/* temp */
char *CLASSES[80] = {"ComE 321", "ComE 322", "Come 323"};
char *STUDENTS[80] = {"Carlo Sarile", "Neil David", "Eric Tampos", "Four", "Five", "Sixe", "seven", "eight", "nine", "ten", "11", "12", "13", "14", "15"};

/* MENU OPTIONS */
char *MENU_OPTIONS[80] = {"Select a Class", "Add a new Class", "Delete a Class", "Exit"};
char *STUDENT_OPTIONS[80] = {"Add a new student", "Find a student", "Sort list", "Next list", "Previous list", "Menu"};

char *CURRENT_CLASS = "";

/* Student (Struct)*/ 
typedef struct{
     int id;
     char first_name[100];
     char last_name[100];
     int quiz;
     int hw;
     int attendance;
     int final_exam;
     int grade;
}Student;


//////////////////////////////////////////////////////////////////////////////////////////
/* START OF DOUBLY LINKED LIST */

/* Node */
typedef struct node{
     Student data;
     struct node *next;
     struct node *prev;
}Node;

Node *students;
int ID = 0;

void insert(Node *pointer, Student data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (Node *)malloc(sizeof(Node));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     pointer->data = data;
     pointer->data.id = ID++;
     pointer->next = NULL;
}

Student find(Node *pointer, Student key) {
     Student s;
     pointer =  pointer -> next; 
     while(pointer!=NULL) {
          if(pointer->data.id == key.id){ 
               return pointer->data;
          }
          pointer = pointer -> next;
     }
     return s;
}

void delete(Node *pointer, Student data) {
     while(pointer->next!=NULL && (pointer->next)->data.id != data.id) {
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

void printStudent(Student s){
     printf("id: %d, firstname: %s, last_name %s\n", s.id, s.first_name, s.last_name);

}

void printStudentList(Node *pointer) {
     if(pointer==NULL) {
          if(getSize(pointer) < 1) printf("Empty\n");
          return;
     }
     printStudent(pointer->data);
     printStudentList(pointer->next);
}

/* END OF DOUBLY LINKED LIST */
//////////////////////////////////////////////////////////////////////////////////////////

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
		case 1: STATE = ADD_CLASS; 	     break;	
		case 2: STATE = DELETE_CLASS; 	break;	
		case 3: STATE = EXIT;	     	break;	
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
	//showStudentList(CURRENT_STUDENT, STUDENTS_PER_PAGE);
     printStudentList(students); //temp
	printf("\nSelect an option: \n");
	for(INDEX = 0; INDEX < 6; INDEX++){
		printf("[%c] %s\n", isSelected(INDEX + STUDENTS_PER_PAGE), STUDENT_OPTIONS[INDEX]);
	}
}

/* TRAP IF INPUT IS NOT INT */
void inputNumber(int *n){
     scanf("%d", n); 
}

/* Get the student information */
Student createStudent(){
     Student s;
     system("cls");
     if(OCCURANCE >= 1) gets(s.first_name);

     printf("Add new student: \n");
     
     printf("\nEnter first name: ");
     gets(s.first_name);

     printf("Enter last name: ");
     gets(s.last_name);

     printf("Enter quiz score: ");
     inputNumber(&s.quiz);

     printf("Enter HW/SW score: ");
     inputNumber(&s.hw);

     printf("Enter attendance score: ");
     inputNumber(&s.attendance);

     printf("Enter final exam score: ");
     inputNumber(&s.final_exam);

     s.grade = getStudentGrade(s);
     OCCURANCE++;
     return s;
}

int getStudentGrade(Student s){ return (s.quiz + s.hw + s.attendance + s.final_exam); }

void printStudentInfo(Student s){
     system("cls");
     printf("Student: %s %s\n\n", s.first_name, s.last_name);
     printf("Firstname: %s\n", s.first_name);
     printf("Lastname: %s\n", s.last_name);
     printf("Quiz: %d\n", s.quiz);
     printf("Hw/Sw: %d\n", s.hw);
     printf("Attendance: %d\n", s.attendance);
     printf("Final Exam: %d\n", s.final_exam);
     printf("\nGrade: %d\n", getStudentGrade(s));
}

void handleSelectStudent(){
     Student student;
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
          student = createStudent();
          printStudentInfo(student);
          insert(students, student);
		STATE = SELECT_STUDENT;
          getch();
	}else{
		printf("selected student: %s", STUDENTS[SELECTOR]);		
	}

}

void handleState(){
	SELECTOR = 0;
	system("cls");
	switch(STATE){
		case MENU:	     	handleMainMenu(); 		     break;
		case SELECT_CLASS: 	     handleSelectClass(); 		break;
		case ADD_CLASS: 	     handleAddClass(); 		     break;
		case DELETE_CLASS: 	     handleDeleteClass(); 		break;
		case SELECT_STUDENT: 	handleSelectStudent(); 		break;
		case EXIT: 		     exit(0);                      break;
	}
	handleState();	
}

void initClassRecord(){
     Node *temp;
     students = (Node*)malloc(sizeof(Node)); 
     temp = students;
     temp -> next = NULL;
     temp -> prev = NULL;
}

int main(){
     initClassRecord();
	handleState();
	getch();
	return 0;
}

