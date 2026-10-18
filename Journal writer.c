#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

#define MAX_ENTRIES 200

// adds ".txt" only if the name doesn't already end with it
void addExtension(char *name)
{
    int n = strlen(name);
    if(n < 4 || strcmp(name + n - 4, ".txt") != 0)
        strcat(name, ".txt");
}

void writing(void)
{
    FILE *writing;
    char filename[200];
    char line[1000];
    int len = 0;
    int ch;

    printf("What's the title ?\n");
    fgets(filename,200,stdin);
    filename[strcspn(filename,"\n")] = '\0';
    addExtension(filename);
    system("cls");

    writing = fopen(filename,"w");
    if(writing == NULL)
    {
        printf("Could not create file.\nPress any key to continue.....");
        getch();
        return;
    }

    printf("%s (Esc to save)\n\n", filename);

    while((ch = getch()) != 27)           // 27 = Esc
    {
        if(ch == '\r')
        {
            fprintf(writing,"%.*s\n",len,line);
            len = 0;
            printf("\n");
        }
        else if(ch == 8)
        {
            if(len > 0)
            {
                len--;
                printf("\b \b");
            }
        }
        else if(len < (int)sizeof(line)-1)
        {
            line[len++] = (char)ch;
            putch(ch);
        }
    }

    if(len > 0)
    {
        fprintf(writing,"%.*s",len,line);
    }

    fclose(writing);

    system("cls");
    printf("Saved as %s\nPress any key to continue...", filename);
    getch();
}

void reading(void)
{
    char names[MAX_ENTRIES][MAX_PATH];    // list of file names
    int count = 0;
    char input[50];
    int choice;
    int ch;
    FILE *fp;

    // find every .txt file in the current folder
    WIN32_FIND_DATAA data;
    HANDLE h = FindFirstFileA("*.txt", &data);

    if(h != INVALID_HANDLE_VALUE)
    {
        do
        {
            if(count < MAX_ENTRIES)
            {
                strcpy(names[count], data.cFileName);
                count++;
            }
        } while(FindNextFileA(h, &data));
        FindClose(h);
    }

    if(count == 0)
    {
        printf("No entries found yet.\nPress any key to go back...");
        getch();
        return;
    }

    printf("Your entries:\n\n");
    for(int i = 0; i < count; i++)
    {
        printf("  %d) %s\n", i + 1, names[i]);
    }

    printf("\nType a number to open (0 to go back): ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    if(choice < 1 || choice > count)
    {
        return;                           // 0 or invalid: back to menu
    }

    system("cls");

    fp = fopen(names[choice - 1], "r");
    if(fp == NULL)
    {
        printf("Could not open %s\nPress any key to continue...", names[choice - 1]);
        getch();
        return;
    }

    printf("%s\n\n", names[choice - 1]);

    while((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);

    printf("\n\nPress any key to go back...");
    getch();
}

int main()
{
    printf("\n\n\n \t\t\t\t\t      Welcome !!!!");
    printf("\n\n\n\n \t\t\t\t\t     How are you ? ");
    while (1)
    {
        printf("\n \t\t\t\t\tWhat's on your mind ? ");
        printf("\n \t\t\t\t Do you want to write anything today ? ");
        printf("\n \t\t\t\t a) Write    b) Read past entries    c) Exit     \n");

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
                system("cls");
                reading();
                system("cls");
                break;

            case 'c':
                return 0;
        }
    }

    return 0;
}
