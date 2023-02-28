#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80 //The maximum length command

int main (void) {
    char *args[MAX_LINE/2 + 1]; //Command line arguments
    int shouldRun = 1; //Flag to determine when to exit program

    while (shouldRun) {
        printf("osh>");
        fflush(stdout);

        // Get user input
        char cmdLine[MAX_LINE];
        fgets(cmdLine, MAX_LINE, stdin);
        
        puts(cmdLine);

        // Clean input
        int cmdLen = strlen(cmdLine);
        cmdLine[cmdLen-1] = '\0';

        // String tokenization
        char *cmdToken = strtok(cmdLine, " ");
        int i = 0;
        int shouldWait = 0;

        while (cmdToken != NULL) {

            if (strcmp(cmdToken, "&") == 0) {
                shouldWait = 1;
            } else {
                args[i] == cmdToken;
                i++;
            }

            cmdToken = strtok(NULL, " ");
        }

        // Fork child with fork()

        // Child process invoke execvp()

        // If command has &, parent invoke wait()

        // Remove
        shouldRun = 0;
    }

    printf("End\n");
    return 0;
}