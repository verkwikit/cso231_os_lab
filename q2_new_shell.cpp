#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<wait.h>
#include<bits/stdc++.h>
using namespace std;
#define MAX_LINE 80

typedef struct
{
    char commandName[15];
} history;

history hist[30];
int cnt = -1;
map<string,int>mp;

void usagedCommands()
{
    printf("\nList of usaged command:\n");
    
    for(int i=0;i<=cnt;i++)
    {
        mp[hist[i].commandName]++;
    }
    map<string,int>:: iterator itr;
    for(itr=mp.begin();itr!=mp.end();itr++)
    {
        cout<<itr->first<<" "<<itr->second<<"\n";
    }
    printf("\n");
}

int commands(char inputBuffer[], char *args[], int *flag)
{
    int length, start = -1, count2 = 0;
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    start = -1;
    if (length == 0)
        exit(0);
    if (length < 0)
    {
        printf("Command not read.. \n");
        exit(-1);
    }
    for (int i = 0; i < length; i++)
    {
        switch (inputBuffer[i])
        {
        case ' ':
        case '\t':
            if (start != -1)
            {
                args[count2] = &inputBuffer[start];
                count2++;
            }
            inputBuffer[i] = '\0';
            start = -1;
            break;

        case '\n':
            if (start != -1)
            {
                args[count2] = &inputBuffer[start];
                count2++;
            }
            inputBuffer[i] = '\0';
            start = -1;
            break;

        default:
            if (start == -1)
                start = i;
            if (inputBuffer[i] == '&')
            {
                *flag = 1;
                inputBuffer[i] = '\0';
            }
        }
    }

    args[count2] = NULL;
    if (strcmp(args[0], "history") == 0)
    {
        if (cnt > -1)
            usagedCommands();
        else
            printf("No Commands in the history..\n");

        return -1;
    }

    else if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    else
    {
        cnt++;
        //cout<<inputBuffer<<" ";
        strcpy(hist[cnt].commandName, inputBuffer);
    }
    return 0;
}

void ClearScreen()
{
    static int first_time = 1;
    if (first_time)
    {
        const char *CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
        write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
        first_time = 0;
    }

    printf("> ");
}

int main(void)
{

    char inputBuffer[MAX_LINE];
    int flag;
    char *args[MAX_LINE / 2 + 1];

    pid_t pid, tpid;
    int i;

    while (1)
    {
        ClearScreen();
        flag = 0;
        fflush(stdout);

        if (-1 != commands(inputBuffer, args, &flag))
        {
            pid = fork();
            if (pid < 0)
            {
                printf("Fork failed.\n");
                exit(1);
            }

            else if (pid == 0)
            {
                if (execvp(args[0], args) == -1)
                    printf("Error executing command\n");
            }

            else
            {
                i++;
                if (flag == 0)
                {
                    i++;
                    wait(NULL);
                }
            }
        }
    }
}