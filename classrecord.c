#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------------------*/
/*------------------------------ START VARIABLE DECLARATIONS -------------------------*/
#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75 
#define RIGHT_KEY 77
#define ENTER_KEY 13
#define ESC_KEY 27

#define STUDENT_MENU_STATE 1
#define EXIT -1

int SELECTOR = 0,
    ID = 0,
    CURRENT_STUDENT = 0,
    STATE = STUDENT_MENU_STATE;

char *STUDENT_MENU[80] = {"View all students", "Find a student", "Add a student", "Exit"};
char *SELECT_STUDENT_OPTIONS[80] = {"View", "Edit", "Delete", "Cancel"};

typedef struct student{
     int id;
     char firstname[80];
     char lastname[80];
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

Node *students, *searchResults;
/*------------------------------- END VARIABLE DECLARATIONS --------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------ START FUNCTION DECLARATIONS -------------------------*/
//helpers: ------------------------------------------------
char *getSelector(int id);
char *getSelectorAndStudentID(int id, int student_id);
int cycleInput(int size);
void displayOptions(char *options[], int start, int end);
int isNumber(char str[]);
int getNumber(char *msg);

//student module: -----------------------------------------
void	showStudentOptions(int size);
void handleStudentMenuInput();
void printStudent(Student s);
void printStudentForTable(Student s, int select_id);
Student createStudent();
int computeGrade(Student s);
void handleAddStudent();
void handleFindStudent();
void handleViewAllStudents();
void showSelectedStudentOptions();
void handleDeleteStudent();

//doubly linked list module:-------------------------------
Node *createNode();
void addStudent(Node *pointer, Student data); 
void addSearchResult(Node *pointer, Student data);
void findStudent(Node *pointer, char key[]); 
void deleteStudent(Node *pointer, int id); 
int getSize(Node *pointer);
Student getStudent(Node *pointer,int id);

//state module: -------------------------------------------
void handleState();
/*------------------------------- END FUNCTION DECLARATIONS --------------------------*/
/*------------------------------------------------------------------------------------*/
/*-------------------------------- START HELPERS FUNCTONS ----------------------------*/
char *getSelector(int id){ return ( (SELECTOR == id) ? ">>" : "  "); }
char *getSelectorAndStudentID(int id, int student_id){
     if(SELECTOR == id){
          CURRENT_STUDENT = student_id;
          return ">>";
     }else{
          return "  ";
     }
}

int cycleInput(int size){
	int INPUT = getch();	
     if(size > 0){
          if(INPUT == UP_KEY)		SELECTOR = (SELECTOR <= 0) ? (size-1) : (SELECTOR - 1); 
          else if(INPUT == DOWN_KEY)	SELECTOR = (SELECTOR + 1) % size; 
     } else if(INPUT == ESC_KEY) return INPUT;
	return (INPUT == ENTER_KEY) ? ENTER_KEY : -1;
}

void displayOptions(char *options[], int start, int end){
     int i = 0;
     for(i = start; i < end; i++){
          printf("\t\t\t   %s %s\n", getSelector(i), options[i]);
     }
}

int isNumber(char str[]){
     int i = 0;
     do{
          if(!isdigit(str[i++])){
               return 0;
          }
     }while(i < strlen(str));
     return 1;
}

int getNumber(char *msg){
     char input[] = "0";
     do{
          if(!isNumber(input)) printf("(Incorrect input! Please try again)\n");
          printf("%s", msg);
          gets(input);
     }while(!isNumber(input));
     return (atoi(input));     
}
/*--------------------------------- END HELPERS FUNCTIONS ----------------------------*/
/*------------------------------------------------------------------------------------*/
/*---------------------------- START DOUBLY LINKEDLIST FUNCTIONS ---------------------*/

Node *createNode(){
     Node *head, *tail;
     head = (Node *)malloc(sizeof(Node)); 
     tail = head;
     tail->next = NULL;
     tail->prev = NULL;
     return head;
}
void addStudent(Node *pointer, Student data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (Node *)malloc(sizeof(Node));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     data.id = ID++;
     data.grade = computeGrade(data);
     pointer->data = data;
     pointer->next = NULL;
}
void addSearchResult(Node *pointer, Student data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (Node *)malloc(sizeof(Node));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     pointer->data = data;
     pointer->next = NULL;
}
void findStudent(Node *pointer, char key[]) {
     pointer =  pointer -> next; 
     searchResults = createNode();
     while(pointer!=NULL) {
          if((strcasecmp(pointer->data.firstname, key) == 0) || (strcasecmp(pointer->data.lastname, key) == 0)){ 
               addSearchResult(searchResults, pointer->data);
          }
          pointer = pointer -> next;
     }
}
Student getStudent(Node *pointer, int id){
     Student temp = {-1, "", "", 1, 1, 1, 1, 1};
     pointer =  pointer -> next; 
     while(pointer!=NULL) {
          if((pointer->data.id == id)){ 
               return pointer->data;
          }
          pointer = pointer -> next;
     }
     return temp;
}
void deleteStudent(Node *pointer, int id) {
     while(pointer->next!=NULL && (pointer->next)->data.id != id) {
          pointer = pointer -> next;
     }
     if(pointer->next==NULL) {
          printf("Student is not present in the list\n");
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

/*----------------------------- END DOUBLY LINKEDLIST FUNCTIONS ----------------------*/
/*------------------------------------------------------------------------------------*/

/*------------------------------- STUDENT MODULE (START) -----------------------------*/

void	showStudentOptions(int size){
     int  start = 0,
          end = size;
	system("cls");
     printf("\n\t\t\t\tClass Record\n\n");
	printf("\t   (Use the arrow keys to navigate and press enter to select)\n\n");
     displayOptions(STUDENT_MENU, start, end);
}
/* Print a student, select_id is for the id of the student in the list */
void printStudentForTable(Student s, int select_id){
     printf("\n   %s", getSelectorAndStudentID(select_id, s.id));
     printf("\t[ID: %d]", s.id);
     printf("\n\tName: %s", s.firstname);
     printf(" %s", s.lastname);
     printf("\n\tScores: %d", s.quiz);
     printf(" %d", s.hw);
     printf(" %d", s.attendance);
     printf(" %d", s.final_exam);
     printf("\n\tGrade: %d\n\n", s.grade);
}
void printStudent(Student s){
     system("cls");
     printf("\n\n\tStudent: %s %s", s.firstname, s.lastname);
     printf("\n\tID: %d\n", s.id);
     printf("\n\tFirstname: %s", s.firstname);
     printf("\n\tLastname %s\n", s.lastname);
     printf("\n\t[Scores]\n\tQuizzes: %d", s.quiz);
     printf("\n\tHomework/Seatwork:  %d", s.hw);
     printf("\n\tAttendance: %d", s.attendance);
     printf("\n\tFinal exam:  %d\n", s.final_exam);
     printf("\n\tGrade: %d\n\n", s.grade);
}
/* Create a student based from the input of the user. Trap if input is not a number */
Student createStudent(){
     char input[80];
     Student s; 
     system("cls");
     printf("\nCreate a new student: \n\n");
     printf("Enter firstname: ");
     gets(s.firstname);
     printf("Enter lastname: ");
     gets(s.lastname);

     s.quiz = getNumber("Enter score in quizzes: ");
     s.attendance = getNumber("Enter attendance: ");
     s.hw = getNumber("Enter score Homework/Seatwork: ");
     s.final_exam = getNumber("Enter score in final exam: ");
     return s;     
}
void printStudentList(Node *pointer){
     int size = getSize(students); 
     int i = 0;
     printf("\n\n\t\t\t\tList of students:");
     if(size == 0){
          printf("\n\n\t\t\t\tThe list is empty\n");
          printf("\n\n\t\t\t    (Press enter to continue)\n");
     }else{
          while(pointer->next!=NULL) {
               pointer = pointer -> next;
               printStudentForTable(pointer->data, i++);
          }
     }
}
void handleAddStudent(){
     Student temp = createStudent(); 
     addStudent(students, temp);
     printf("\nStudent %s was added to the list. (Press any key to continue)\n", temp.firstname);
}
void handleFindStudent(){
     char input[80];
     system("cls");
     printf("\n\nSearch a student");
     printf("\nEnter firstname or lastname: ");
     gets(input);
     findStudent(students, input) ;

     system("cls");
     printf("\nStudents found: %d\n", (getSize(searchResults) > 0 ? getSize(searchResults) : 0));
     printStudentList(searchResults);
}
void showSelectedStudentOptions(){
     do{
          system("cls");
          printf("\n\nStudent ID: %d", CURRENT_STUDENT);
          printf("\n\nWhat would you like to do?\n");
          displayOptions(SELECT_STUDENT_OPTIONS, 0, 4);
     }while(cycleInput(4) != ENTER_KEY);
}
void handleDeleteStudent(){
     char in[20];
     printf("\nAre you sure you want to delete this student? [Y/N]: ");
     gets(in);
     if(strcmp(in, "Y") == 0 || strcmp(in, "y") == 0) {
          deleteStudent(students, CURRENT_STUDENT); 
          printf("\n\nStudent was removed. (Press any key to continue)");
          getch();
     }
     STATE = STUDENT_MENU_STATE;
}
void handleViewAllStudents(){
     /* show the list of students and allow user to select them */
     do{  system("cls"); printStudentList(students); }while(cycleInput(getSize(students)) != ENTER_KEY);

     SELECTOR = 0;

     if(getSize(students) > 0){
          /* show options if user selects a student */
          showSelectedStudentOptions();

          /* proccess the option the user selected */
          switch(SELECTOR){
               case 0: printStudent(getStudent(students, CURRENT_STUDENT)); getch();break;
               case 1: printf("edit"); getch();break;
               case 2: handleDeleteStudent(); break;
               case 3: STATE = STUDENT_MENU_STATE; break;
          }
     }
}

void handleStudentMenuInput(){
     int size  = 4;
     /* show the student options until the user press enter */
     do{ showStudentOptions(size); }while(cycleInput(size)!= ENTER_KEY);
     
     /* process the selected option of the user */
     switch(SELECTOR){
          case 0: handleViewAllStudents(); break;
          case 1: handleFindStudent(); getch(); break;
          case 2: handleAddStudent(); getch(); break;
          case 3: printf("\nGoodbye..\n"); STATE = EXIT; break;
     }
     SELECTOR = 0;
}

int computeGrade(Student s){ return (s.quiz + s.attendance + s.hw + s.final_exam); }
/*-------------------------------- STUDENT MODULE (END) ------------------------------*/

/* State handler */
void handleState(){
     do{
          switch(STATE){
               case STUDENT_MENU_STATE: handleStudentMenuInput(); break;
               case EXIT: exit(0); break;
          }
     }while(STATE != EXIT);
}

/* The main function */
int main(){
     students = createNode();
     searchResults = createNode();
     //load students from file..
     //get last id based from the list of all students loaded
     //set id to last id
     //...code here..

     handleState();

     free(students);
     free(searchResults);
	getch();
	return 0;
}
