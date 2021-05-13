#include <stdio.h>
#define VERSION 1.0
#define MAX_STRING 255

int counter = 0;

void enterAndInterprete();

void helloWorld()
{
    printf("Hello, world!\n");
}

void printFile(char* filename)
{
    FILE* file = fopen(filename, "r");
    char string[MAX_STRING];

    while (fgets(string, MAX_STRING, file))
    {
        fputs(string, stdout);
    }

    fclose(file);
}

void bottles()
{ 
    int i = 99;

    while (i > 0)
    {
        printf("%d bottles of beer on the wall, ", i);
        printf("%d bottles of beer\n", i);
        printf("Take one down, pass it around, ");
        i--;
        printf("%d bottles of beer on the wall.\n", i);
    }

    printf("No more bottles of beer on the wall, no more bottles of beer.\n");    
    printf("We've taken them down and passed them around; "
        "now we're drunk and passed out! \n");
}

void increase()
{
    counter++;
}

int doCommand(char command)
{
    if (command == 'H')
        helloWorld();
    else if (command == 'Q')
        printf("Error: cannot do this command in a shell.\n");
    else if (command == '9')
        bottles();
    else if (command == '+')
        increase();
    else if (command == 'q')
        printf("Quiting the shell...\n");
    else if (command == 'f')
        enterAndInterprete();
    else    
    {    
        printf("Error: no such command as %c.\n", command);
        return 1;
    }    

    return 0;
}

void shell()
{
    char command;

    printf("HQ9+ intrepreter shell.\n");
    printf("Input q to exit the shell; f to interprete a file.\n");

    while (command != 'q')
    {
        printf(">>> ");
        scanf(" %c", &command);
        doCommand(command);
        while (fgetc(stdin) != '\n');
    }
}

char getMode()
{
    char answer;
    
    do
    {
        printf("Input 1 to run shell, input 2 to run a file: ");
        scanf(" %c", &answer);
        while (fgetc(stdin) != '\n');
    } while(answer != '1' && answer != '2');

    return answer;
}

void interpreteFile(char* filename)
{
    FILE* file = fopen(filename, "r");
    char string[MAX_STRING];
    int error = 0;

    while (fgets(string, MAX_STRING, file) && !error)
    {
        for (int i = 0;(!error) && string[i] != '\0'; i++)
        {
            if (string[i] == '\n')
                continue;
            if (string[i] == 'Q')
            {
                printFile(filename);
            }
            else if ((string[i] == 'q') || (string[i] == 'f'))
            {
                error = 1;
                printf("Error: no such command as %c.\n", string[i]);
            }
            else
                error = doCommand(string[i]); 
        }
    }
}

void enterAndInterprete()
{
    char filename[MAX_STRING];

    printf("Input the name of the file: ");
    scanf(" %s", filename);

    interpreteFile(filename);
}

int main()
{
    printf("HQ9+ C interpeter.\n");    
    printf("Version %.1f.\n\n", VERSION);   

    if (getMode() == '1')
       shell();
    else
        enterAndInterprete();

    return 0;
}

