#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <stdlib.h>
void writing(void)
{
 FILE *writing;

 //getch();
 char filename[200];
 char text[100000];

    printf("What's the title ?\n");
    fgets(filename,200,stdin);
    filename[strcspn(filename,"\n")] = '\0';
    strcat(filename,".txt");
    system("cls");

 writing = fopen(filename,"w");

  fgets(text,100000,stdin);
 fprintf(writing,"%s",text);
 fclose(writing);
 //return filename;

}
int main()
{
    printf("\n\n\n \t\t\t\t\t      Welcome !!!!");
    printf("\n\n\n\n \t\t\t\t\t     How are you ? ");
   while (1)
   {

       printf("\n \t\t\t\t\tWhat's on your mind ? ");

       printf("\n \t\t\t\t Do you want to write anything today ? ");
       printf("\n \t\t\t\t\t a) YES      b) Exit     \n");

       char choice;
           choice = getch();

       switch(choice)
       {
               case 'a':
                    system("cls");
                   writing();
                   system("cls");

                   break;

               case 'b':
                   return 0;
       }

   }

   return 0;

}
