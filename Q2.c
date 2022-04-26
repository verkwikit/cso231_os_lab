#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // UNIX Standard Library
//#include <sys/wait.h>

FILE *fp;
char *filename;


int checkCustomInput(char *args);
int execute(char **ags);
char **parseArgs(char *line);
void initialiseHistory();
void addToHistory(char *args);
void showHistory();
void initialiseShell();

int main()
{
    initialiseShell();
    return 0;
}

int checkCustomInput(char *args)
{
    if (!strcmp(args, "exit"))
    {
        exit(EXIT_FAILURE);
        return -1;
    }
    else if (!strcmp(args, "history"))
    {
        showHistory();
        return 1;
    }
    return 0;
}

int execute(char **args)
{
    if (!strcmp(args[0], "cd") && args[1] != NULL)
    {
        if (chdir(args[1]) != 0)
        {
            printf("Enter Valid Path ! !");
            exit(EXIT_FAILURE);
        }
        return 1;
    }

    pid_t pid = fork();
    
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            printf("Enter valid Command ! !\n");
            exit(EXIT_FAILURE);
        }
        exit(0);
       
    }
    else if (pid < 0)
    {
        printf("! ! FORK ERROR ! !");
    }
    else
    {
        wait(NULL);
    }

    return 1;
}

char **parseArgs(char *line)
{
    int pos = 0;
    char **tokens = malloc(101 * sizeof(char *));
    char *token = NULL;
    token = strtok(line, " \n\t");
    while (token != NULL)
    {
        tokens[pos] = token;
        pos++;
        token = strtok(NULL, " \n\t");
    }
    tokens[pos] = NULL;
    return tokens;
}

void addToHistory(char *args)
{
    char *line;
    strcpy(line, args);
    char *token = strtok(line, " \t");
    if (strcmp(token, "\n"))
    {
        fp = fopen(filename, "a");
        fputs(args, fp);
        fclose(fp);
    }
}

void showHistory()
{
    char *line;
    int i = 1;
    fp = fopen(filename, "r");
    while (fgets(line, 100, fp))
    {
        printf("%d : %s\n", i++, line);
    }
    fclose(fp);
}

void initialiseHistory(){
    filename = strcat(getenv("HOME"), "/customShellHistory.txt");
    fp = fopen(filename, "w");
    fclose(fp);
}

void initialiseShell()
{
    printf("-----------------------------------\n");
    printf("---- CUSTOM SHELL CREATED IN C ----\n");
    printf("-----------------------------------\n\n");

    initialiseHistory();

    while(1)
    {
        char input[100];
        char **parsedInput;
        printf("\n--> ");
        fgets(input, 100, stdin);
        if (input[strlen(input) - 1] != '\n')
        {
            printf("Input length limit exceeded ! !\n");
            while (getchar() != '\n')
                continue;
            continue;
        }
        else
        {
            addToHistory(input);
            parsedInput = parseArgs(input);
            int flg = checkCustomInput(input);
            if (!flg)
                execute(parsedInput);
        }
    }
}