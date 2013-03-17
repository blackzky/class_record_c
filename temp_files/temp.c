#include <stdio.h>
#include <string.h>

void validNumber(){
     int input, error, status;
     char skip_ch;

     do {
          error = 0;
          printf("Enter a number => ");
          status = scanf("%d",&input);
          printf("\n %d \n",input);

          if(status!=1) {
               error=1;
          }
          else if(input < 0 || input >15){
               error = 1;
          }

          do {
               scanf("%c",&skip_ch);
          }while(skip_ch != '\n');
     } while (error);

}

void ok(){
     char str[]="1776ad6";
     int year;
     if (isdigit(str[0])) {
          year = atoi (str);
          printf ("The year that followed %d was %d.\n",year,year+1);
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
     char input[80];
     do{
          printf("%s", msg);
     }while(!isNumber(input));
     return (atoi(input));     

}

int main(){
     char in[] = "17766";
     if(isNumber(in)){
          printf("ok!");
     }else{
          printf("nope!");
     }

     //validNumber();     
     printf("\nout\n");
     getch();

     return 0;
}
