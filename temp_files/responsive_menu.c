#include <stdio.h>

#define UP_KEY 72
#define DOWN_KEY 80
#define ENTER_KEY 13

int selector = 0;

char getSelector(int id){
	return ( (selector == id) ? 'x' : ' ');
}
void showOptions(){
	system("cls");
	printf("Use the arrow keys and press enter to select:\n");
	printf("[%c] Add\n", getSelector(0));
	printf("[%c] Edit\n", getSelector(1));
	printf("[%c] View\n", getSelector(2));
	printf("[%c] Delete\n", getSelector(3));
	printf("[%c] Exit\n", getSelector(4));
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

int main(){
	handleInput(5);
	getch();
	return 0;
}

