#include <stduio.h>
#include <unistd.h>

#define MAX_LINE 80 //The maximum length command

int main (void) {
    char *args[MAX_LINE/2 + 1]; //Command line arguments
    int shouldRun = 1; //Flag to determine when to exit program

    while (shouldRun) {
        printf("osh>");
        fflush(stdout);

        // Read user input

        // Fork child with fork()

        // Child process invoke execvp()

        // If command has &, parent invoke wait()
    }

    return 0;
}