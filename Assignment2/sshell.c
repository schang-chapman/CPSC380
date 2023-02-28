#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
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

        // Check for exit
        if (strcmp(cmdLine, "exit\n") == 0) {
            shouldRun = 0;
            break;
        }
        
        // Clean input
        int cmdLen = strlen(cmdLine);
        cmdLine[cmdLen-1] = '\0';
        cmdLine[strcspn(cmdLine, "\n")] = 0;

        // String tokenization
        char *cmdToken = strtok(cmdLine, " ");
        int i = 0;
        int shouldWait = 0;

        while (cmdToken != NULL) {
            if (strcmp(cmdToken, "&") == 0) {
                shouldWait = 1;
            } else {
                args[i] = cmdToken;
                i++;
            }

            cmdToken = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Fork child with fork()
        pid_t pid = fork();

        // Child process invoke execvp()
        if (pid == 0) {
            // execvp() error catch
            if (execvp(args[0], args) == -1) {
                fprintf(stderr, "execvp() function failed.\n");
            } else {
                return 0;
            }
        // fork() error catch
        } else if (pid < 0) {
            fprintf(stderr, "fork() function failed.\n");
            return -1;
        // Parent check to invoke wait()
        } else if (pid > 0) {
            if (shouldWait) {
                wait(NULL);
            }
        }

    }

    return 0;
}