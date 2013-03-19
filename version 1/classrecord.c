#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------------------*/
/*------------------------------ VARIABLE DECLARATIONS (START) -----------------------*/
#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75 
#define RIGHT_KEY 77
#define ENTER_KEY 13
#define ESC_KEY 27
#define DEL_KEY 8 

#define STUDENT_MENU_STATE 1
#define CLASS_MENU_STATE 2
#define VIEW_ALL_STUDENTS_STATE 3
#define EXIT -1

int SELECTOR = 0,
    ID = 0,
    classID = 0,
    CURRENT_STUDENT = 0,
    CURRENT_CLASS = 0,
    STUDENTS_PER_PAGE = 15,
     CURRENT_PAGE = 0;
    STATE = CLASS_MENU_STATE;

char *STUDENT_MENU[80] = {"View all students", "Find a student", "Add a student", "Menu"};
char *SELECT_STUDENT_OPTIONS[80] = {"View", "Edit", "Delete", "Cancel"};
char *EDIT_STUDENT_OPTIONS[80] = {"Firstname", "Lastname", "Quiz", "Homework/Seatwork", "Attendance", "Final exam", "Cancel"};
char *CLASS_MENU[80] = {"View all class", "Add a class", "Exit"};

//dummy data
char *temp_classes[80] = {"ComE321", "Reed31", "ComE324"};

//for dummy data (students, just add values in the temp_fname and temp_lname, don't forget to adjust 'number_of_students')
int number_of_students = 3;
char *temp_fname[80] = {"Juan", "Juan", "Juan" };
char *temp_lname[80] = {"De La Cruz", "Lopez", "Doe" };


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
}StudentNode;

typedef struct class{
     int id;
     char name[80];
     StudentNode *students;
}Class;

typedef struct cNode{
     Class data;
     struct cNode *next;
     struct cNode *prev;
}ClassNode;


StudentNode *students, *searchResults;
ClassNode *classes;
/*------------------------------- VARIABLE DECLARATIONS (END) ------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------ FUNCTION DECLARATIONS (START) -----------------------*/
//helpers: ------------------------------------------------
char *getSelector(int id);
char *getSelectorAndStudentID(int id, int student_id);
char *getSelectorAndClassID(int id, int class_id);
int cycleInput(int size);
void displayOptions(char *options[], int start, int end);
int isNumber(char str[]);
int getNumber(char *msg);
void printInCenter(char str[]);
int getNumOfPages(StudentNode *pointer);

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
void handleEditStudent();

//class module:--------------------------------------------
void printClassForTable(Class c, int select_id);
void handleViewAllClass();
void printClassList(ClassNode *pointer);
void handleAddClass();
void	showClassOptions(int size);
void handleClassMenuInput();
void handleDeleteClass();

//doubly linked list module:-------------------------------
StudentNode *createStudentNode();
void addStudent(StudentNode *pointer, Student data); 
void addSearchResult(StudentNode *pointer, Student data);
void findStudent(StudentNode *pointer, char key[]); 
void deleteStudent(StudentNode *pointer, int id); 
int getSize(StudentNode *pointer);
Student getStudent(StudentNode *pointer,int id);
void editStudent(StudentNode *pointer, int id, void* newData, int selector);
void deleteClass(ClassNode *pointer, int id); 

ClassNode *createClassNode();
void addClass(ClassNode *pointer, Class data);
int getClassSize(ClassNode *pointer);

void populateData();
//state module: -------------------------------------------
void handleState();
/*------------------------------- FUNCTION DECLARATIONS (END) ------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*-------------------------------- HELPERS FUNCTONS (START) --------------------------*/
char *getSelector(int id){ return ( (SELECTOR == id) ? ">>" : "  "); }
char *getSelectorAndStudentID(int id, int student_id){
     if(SELECTOR == id){
          CURRENT_STUDENT = student_id;
          return ">>";
     }else{
          return "  ";
     }
}
char *getSelectorAndClassID(int id, int class_id){
     if(SELECTOR == id){
          CURRENT_CLASS = class_id;
          return ">>";
     }else{
          return "  ";
     }
}
void printInCenter(char str[]){
     int i;
     char space[80];
     if(strlen(str) < 1){
          return;
     }
     for(i = 0; i < (40 - (strlen(str)/2)); i++){
          printf(" ");
     }
     printf("%s\n", str);
}
int cycleInput(int size){
	int INPUT = getch();	
     int numPages= 0;
     if(size > 0){
          if(STATE == VIEW_ALL_STUDENTS_STATE){
               numPages = getNumOfPages(students);
          }else{
               numPages = getNumOfPages(searchResults);
          }
          if(INPUT == UP_KEY)		SELECTOR = (SELECTOR <= 0) ? (size-1) : (SELECTOR - 1); 
          else if(INPUT == DOWN_KEY)	SELECTOR = (SELECTOR + 1) % size; 
          else if(INPUT == LEFT_KEY){
               CURRENT_PAGE = (CURRENT_PAGE <= 0) ? (numPages-1) : (CURRENT_PAGE - 1); 
          }
          else if(INPUT == RIGHT_KEY){
               CURRENT_PAGE = (CURRENT_PAGE + 1) % numPages; 
          }
          else if(INPUT == ESC_KEY) return INPUT;
          else if(INPUT == DEL_KEY) return INPUT;
     }else if(INPUT == ESC_KEY) return INPUT; 
     else if(INPUT == DEL_KEY) return INPUT;
	return (INPUT == ENTER_KEY) ? ENTER_KEY : -1;
}
void displayOptions(char *options[], int start, int end){
     int i = 0;
     for(i = start; i < end; i++){
          printf("\t\t\t      %s %s\n", getSelector(i), options[i]);
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
int getNumOfPages(StudentNode *pointer){
     int pages = getSize(pointer)/STUDENTS_PER_PAGE; 
     pages = pages + (getSize(pointer)%STUDENTS_PER_PAGE > 0 ? 1 : 0);
     return (pages == 0 ? 1 : pages);
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
/*--------------------------------- HELPERS FUNCTIONS (END) --------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*---------------------------- DOUBLY LINKEDLIST FUNCTIONS (START) -------------------*/

StudentNode *createStudentNode(){
     StudentNode *head, *tail;
     head = (StudentNode *)malloc(sizeof(StudentNode)); 
     tail = head;
     tail->next = NULL;
     tail->prev = NULL;
     return head;
}
void addStudent(StudentNode *pointer, Student data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (StudentNode *)malloc(sizeof(StudentNode));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     data.id = ID++;
     data.grade = computeGrade(data);
     pointer->data = data;
     pointer->next = NULL;
}
void addSearchResult(StudentNode *pointer, Student data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (StudentNode *)malloc(sizeof(StudentNode));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     pointer->data = data;
     pointer->next = NULL;
}
void findStudent(StudentNode *pointer, char key[]) {
     pointer =  pointer -> next; 
     searchResults = createStudentNode();
     while(pointer!=NULL) {
          if((strcasecmp(pointer->data.firstname, key) == 0) || (strcasecmp(pointer->data.lastname, key) == 0)){ 
               addSearchResult(searchResults, pointer->data);
          }
          pointer = pointer -> next;
     }
}
Student getStudent(StudentNode *pointer, int id){
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
void deleteStudent(StudentNode *pointer, int id) {
     while(pointer->next!=NULL && (pointer->next)->data.id != id) {
          pointer = pointer -> next;
     }
     if(pointer->next==NULL) {
          printf("Student is not present in the list\n");
          return;
     }
     StudentNode *temp;
     temp = pointer -> next;
     pointer->next = temp->next;
     temp->prev =  pointer;
     free(temp);
     return;
}
void editStudent(StudentNode *pointer, int id, void* newData, int selector){
     pointer =  pointer -> next; 
     while(pointer!=NULL) {
          if(pointer->data.id == id){ 
               switch(selector){
                    case 0: strcpy(pointer->data.firstname, (char *)newData); break;
                    case 1: strcpy(pointer->data.lastname, (char *)newData); break;
                    case 2: pointer->data.quiz = newData; break;
                    case 3: pointer->data.hw = newData; break;
                    case 4: pointer->data.attendance = newData; break;
                    case 5: pointer->data.final_exam = newData; break;
               }
               pointer->data.grade = computeGrade(pointer->data);
               break;
          }
          pointer = pointer -> next;
     }
}
int getSize(StudentNode *pointer){
     int count = 0;
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
          count++;
     }
     return count;
}

ClassNode *createClassNode(){
     ClassNode *head, *tail;
     head = (ClassNode *)malloc(sizeof(ClassNode)); 
     tail = head;
     tail->next = NULL;
     tail->prev = NULL;
     return head;
}
void addClass(ClassNode *pointer, Class data) {
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
     }
     pointer->next = (ClassNode *)malloc(sizeof(StudentNode));
     (pointer->next)->prev = pointer;
     pointer = pointer->next;
     data.id = classID++;
     pointer->data = data;
     pointer->next = NULL;
}
Class getClass(ClassNode *pointer, int id){
     Class temp;
     temp.id = -1;
     strcpy(temp.name,"");
     temp.students = createStudentNode();
     pointer =  pointer -> next; 
     while(pointer!=NULL) {
          if((pointer->data.id == id)){ 
               return pointer->data;
          }
          pointer = pointer -> next;
     }
     return temp;
}
void deleteClass(ClassNode *pointer, int id) {
     while(pointer->next!=NULL && (pointer->next)->data.id != id) {
          pointer = pointer -> next;
     }
     if(pointer->next==NULL) {
          printf("Class is not present in the list\n");
          return;
     }
     ClassNode *temp;
     temp = pointer -> next;
     pointer->next = temp->next;
     temp->prev =  pointer;
     free(temp);
     return;
}
int getClassSize(ClassNode *pointer){
     int count = 0;
     while(pointer->next!=NULL) {
          pointer = pointer -> next;
          count++;
     }
     return count;
}

/*----------------------------- DOUBLY LINKEDLIST FUNCTIONS (END) --------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------- STUDENT MODULE (START) -----------------------------*/

void	showStudentOptions(int size){
     int  start = 0,
          end = size;
	system("cls");
     printf("\n");
     printInCenter("Class Record >> Students");
     printf("\n\n");
	printInCenter("(Use the arrow keys to navigate and press enter to select)");
     printf("\n\n");
     displayOptions(STUDENT_MENU, start, end);
}
/* Print a student, select_id is for the id of the student in the list */
void printStudentForTable(Student s, int select_id){
     printf("\n\t %s %s %s", getSelectorAndStudentID(select_id, s.id), s.firstname, s.lastname, s.grade);
}
void printStudent(Student s){
     system("cls");
     printf("\n");
     printInCenter("Class Record >> Student info");
     printf("\n\n\tStudent: %s %s\n", s.firstname, s.lastname);
     printf("\n\tFirstname: %s", s.firstname);
     printf("\n\tLastname %s\n", s.lastname);
     printf("\n\t[Scores]\n\tQuizzes: %d", s.quiz);
     printf("\n\tHomework/Seatwork:  %d", s.hw);
     printf("\n\tAttendance: %d", s.attendance);
     printf("\n\tFinal exam:  %d\n", s.final_exam);
     printf("\n\tGrade: %d\n\n", s.grade);
     printInCenter("(Press enter or esc to continue)");
}
/* Create a student based from the input of the user. Trap if input is not a number */
Student createStudent(){
     char input[80];
     Student s; 
     system("cls");
     printf("\n"); 
     printInCenter("Class Record >> Add student");
     printf("\n\n"); 
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
void printStudentList(StudentNode *pointer){
     int size = getSize(pointer); 
     int i = 0;
     int start = CURRENT_PAGE * STUDENTS_PER_PAGE;
     int counter = 0;
     if(size == 0){
          printInCenter("The list is empty");
          printInCenter("(Press enter or esc to continue)");
     }else{
          printf("\nShowing page %d out of %d page/s\n", CURRENT_PAGE+1, getNumOfPages(pointer));
          while(pointer->next!=NULL) {
               pointer = pointer -> next;
               counter++;
               if(counter > start) printStudentForTable(pointer->data, i++);
               if(counter >= ((CURRENT_PAGE*STUDENTS_PER_PAGE) + STUDENTS_PER_PAGE)) break;
          }
          printf("\n\n");
          printInCenter("(Press left arrow to show previous list and right arrow for next list)");
     }
}
void handleAddStudent(){
     Student temp = createStudent(); 
     addStudent(students, temp);
     printf("\nStudent %s was added to the list.\n(Press any key to continue)\n", temp.firstname);
}
void handleFindStudent(){
     char input[80];
     int size;
     system("cls");
     printf("\n");
     printInCenter("Class Record >> Find Student");
     printf("\n");
     printf("\nEnter firstname or lastname: ");
     gets(input);
     findStudent(students, input) ;
     
     CURRENT_PAGE = 0;
     SELECTOR = 0;
     if(getSize(searchResults) > 0){
          do{ 
               size = (getSize(searchResults) > STUDENTS_PER_PAGE ) ? STUDENTS_PER_PAGE : getSize(searchResults);
               if((CURRENT_PAGE+1) == getNumOfPages(searchResults)){
                    size = getSize(searchResults) - ((CURRENT_PAGE * STUDENTS_PER_PAGE));
                    if(size == 0 || size == STUDENTS_PER_PAGE){ size = STUDENTS_PER_PAGE; }
               }
               system("cls");
               printf("\n");
               printInCenter("Class Record >> Search Results");
               printf("\nStudents found: %d\n", (getSize(searchResults) > 0 ? getSize(searchResults) : 0));
               printStudentList(searchResults);
          }while(cycleInput(size) != ENTER_KEY);
          if(getSize(students) > 0){
               showSelectedStudentOptions();
               switch(SELECTOR){
                    case 0: printStudent(getStudent(students, CURRENT_STUDENT)); getch(); STATE = STUDENT_MENU_STATE; break;
                    case 1: handleEditStudent(); STATE = STUDENT_MENU_STATE; break;
                    case 2: handleDeleteStudent(); STATE = STUDENT_MENU_STATE; break;
                    case 3: STATE = STUDENT_MENU_STATE; break;
               }
          }
     }else{
          system("cls");
          printf("\n");
          printInCenter("Class Record >> Search Results");
          printf("\nStudents found: none\n");
     }
}
void showSelectedStudentOptions(){
     Student s = getStudent(students, CURRENT_STUDENT);
     do{
          system("cls");
          printf("\n");
          printInCenter("Class Record >> Student Options");
          printf("\n\n\t\t\tStudent: %s %s", s.firstname, s.lastname);
          printf("\n\n");
          printInCenter("What would you like to do?");
          printf("\n");
          displayOptions(SELECT_STUDENT_OPTIONS, 0, 4);
     }while(cycleInput(4) != ENTER_KEY);
}
void handleDeleteStudent(){
     char in[20];
     printf("\nAre you sure you want to delete this student? [Y/N]: ");
     gets(in);
     if(strcmp(in, "Y") == 0 || strcmp(in, "y") == 0) {
          deleteStudent(students, CURRENT_STUDENT); 
          printf("\n\nStudent was removed.\n(Press any key to continue)");
          getch();
     }
     STATE = STUDENT_MENU_STATE;
}
void handleEditStudent(){
     Student s = getStudent(students, CURRENT_STUDENT);
     int size = 7;
     char input[80];
     SELECTOR = 0;
     do{
          system("cls");
          printf("\n");
          printInCenter("Class Record >> Edit Student");
          printf("\n\t\t\tStudent: %s %s", s.firstname, s.lastname);
          printf("\n\n\t\t\tWhat data would you like to edit?\n\n");
          displayOptions(EDIT_STUDENT_OPTIONS, 0, size);
     }while(cycleInput(size) != ENTER_KEY);
     
     switch(SELECTOR){
          case 0: printf("Edit firstname: "); gets(input); editStudent(students, CURRENT_STUDENT, input, SELECTOR); break;
          case 1: printf("Edit lastname: "); gets(input); editStudent(students, CURRENT_STUDENT, input, SELECTOR); break;
          case 2: editStudent(students, CURRENT_STUDENT, getNumber("Edit quiz score: "), SELECTOR);break;
          case 3: editStudent(students, CURRENT_STUDENT, getNumber("Edit homework score: "), SELECTOR);break;
          case 4: editStudent(students, CURRENT_STUDENT, getNumber("Edit attendance: "), SELECTOR);break;
          case 5: editStudent(students, CURRENT_STUDENT, getNumber("Edit final exam score: "), SELECTOR);break;
          case 6: STATE = STUDENT_MENU_STATE; break;
     }
}
void handleViewAllStudents(){
     /* show the list of students and allow user to select them */
     int in = 0;
     int size;
     CURRENT_PAGE = 0;
     do{ 
          size = (getSize(students) > STUDENTS_PER_PAGE ) ? STUDENTS_PER_PAGE : getSize(students);
          if((CURRENT_PAGE+1) == getNumOfPages(students)){
               size = getSize(students) - ((CURRENT_PAGE * STUDENTS_PER_PAGE));
               if(size == 0 || size == STUDENTS_PER_PAGE){ size = STUDENTS_PER_PAGE; }
          }
          system("cls");
          printInCenter("Class Record >> Student List");
          printf("\n");
          printStudentList(students);
          in = cycleInput(size);
          if(in == ESC_KEY){ STATE = STUDENT_MENU_STATE; SELECTOR = 0; return;}
     }while(in != ENTER_KEY);

     SELECTOR = 0;

     if(getSize(students) > 0){
          showSelectedStudentOptions();

          switch(SELECTOR){
               case 0: printStudent(getStudent(students, CURRENT_STUDENT)); getch(); STATE = STUDENT_MENU_STATE; break;
               case 1: handleEditStudent(); STATE = STUDENT_MENU_STATE; break;
               case 2: handleDeleteStudent(); STATE = STUDENT_MENU_STATE; break;
               case 3: STATE = STUDENT_MENU_STATE; break;
          }
     }
     SELECTOR = 0;
}
void handleStudentMenuInput(){
     int size  = 4;
     /* show the student options until the user press enter */
     do{ showStudentOptions(size); }while(cycleInput(size)!= ENTER_KEY);
     
     /* process the selected option of the user */
     switch(SELECTOR){
          case 0: STATE = VIEW_ALL_STUDENTS_STATE; break;
          case 1: handleFindStudent(); getch(); break;
          case 2: handleAddStudent(); getch(); break;
          case 3: STATE = CLASS_MENU_STATE; break;
     }
     SELECTOR = 0;
}
int computeGrade(Student s){ return (s.quiz + s.attendance + s.hw + s.final_exam); }
/*-------------------------------- STUDENT MODULE (END) ------------------------------*/
/*------------------------------------------------------------------------------------*/
/*-------------------------------- CLASS MODULE (START) ------------------------------*/

//to get the current student list use: getClass(classes, CURRENT_CLASS).students
void printClassForTable(Class c, int select_id){
     printf("\n\t %s %s", getSelectorAndClassID(select_id, c.id), c.name);
}
void handleDeleteClass(){
     char in[20];
     printf("\nAre you sure you want to delete this class? [Y/N]: ");
     gets(in);
     if(strcmp(in, "Y") == 0 || strcmp(in, "y") == 0) {
          deleteClass(classes, CURRENT_CLASS); 
          printf("\n\nClass was removed.\n(Press any key to continue)");
          getch();
     }
}
void handleViewAllClass(){
     int size = getClassSize(classes); 
     int in; 
     do{
          system("cls");
          printClassList(classes);
          in = cycleInput(getClassSize(classes));
          if(in == ESC_KEY){ break; }
          if(in == ENTER_KEY) {
               if(size > 0){
                    students = getClass(classes, CURRENT_CLASS).students;
                    if(in != ESC_KEY) STATE = STUDENT_MENU_STATE;
               }
          }
          if(getClassSize(classes) > 0){
               if(in == DEL_KEY) { handleDeleteClass(); STATE = CLASS_MENU_STATE; break; }
          }
     }while(in != ENTER_KEY);
}
void printClassList(ClassNode *pointer){
     int size = getClassSize(classes); 
     int i = 0;
     printf("\n");
     printInCenter("Class Record >> Class List");
     printf("\n");
     if(size == 0){
          printInCenter("The list is empty");
          printInCenter("(Press enter or esc to continue)");
     }else{
          while(pointer->next!=NULL) {
               pointer = pointer -> next;
               printClassForTable(pointer->data, i++);
          }
          printf("\n");
          printInCenter("(Press backspace to delete class)");
          printInCenter("(Press enter or esc to go back to menu)");
     }
}
void handleAddClass(){
     char input[80];
     Class c;

     system("cls");
     printf("\n");
     printInCenter("Class Record >> Add Class");
     printf("\n\n");
     do{
          printf("Classname: ");
          gets(c.name);
     }while(strcmp(c.name, "") == 0);
     c.students = createStudentNode();
     addClass(classes, c);
     
     printf("\nClass %s was added.\n(Press enter to continue)", c.name);
     getch();
}
void	showClassOptions(int size){
     int  start = 0,
          end = size;
	system("cls");
     printf("\n"); 
     printInCenter("Class Record");
     printf("\n\n"); 
	printInCenter("(Use the arrow keys to navigate and press enter to select)");
     printf("\n\n"); 
     displayOptions(CLASS_MENU, start, end);
}
void handleClassMenuInput(){
     int size = 3;
     do{ showClassOptions(size); }while(cycleInput(size)!= ENTER_KEY);

     switch(SELECTOR){
          case 0: handleViewAllClass(); break;
          case 1: handleAddClass(); break;
          case 2: STATE = EXIT;  break;
     }
     SELECTOR = 0;
}

/*-------------------------------- CLASS MODULE (END) ------------------------------*/
/*------------------------------------------------------------------------------------*/

void populateData(){
     int i, j;
     char strnum[80];
     Class temp;
     Student tempS;
     for(i = 0; i < 3; i++){
          strcpy(temp.name, temp_classes[i]);
          temp.students = createStudentNode();
          addClass(classes, temp);
          students = getClass(classes, i).students;
          for(j = 0; j < 60 ;j++){
               strcpy(tempS.firstname, temp_fname[(j+1)%number_of_students]);
               sprintf(strnum, "%d", j);
               strcat(tempS.firstname, strnum);
               strcpy(tempS.lastname, temp_lname[(j+1)%number_of_students]);
               tempS.quiz = 1;
               tempS.hw = 1;
               tempS.attendance = 1;
               tempS.final_exam = 1;
               addStudent(students, tempS);
          }
     }
     
}

/* State handler */
void handleState(){
     do{
          switch(STATE){
               case STUDENT_MENU_STATE: handleStudentMenuInput(); break;
               case VIEW_ALL_STUDENTS_STATE: handleViewAllStudents();break;
               case CLASS_MENU_STATE: handleClassMenuInput(); break;
               case EXIT: exit(0); break;
          }
     }while(STATE != EXIT);
}

/* The main function */
int main(){
     students = createStudentNode();
     searchResults = createStudentNode();
     classes = createClassNode();

     populateData(); /* add temp data */

     handleState();
	return 0;
}

