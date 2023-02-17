#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main(int argc, char *paths[])
{
    // Get paths from input.
    char *inPath = paths[1];
    char *outPath = paths[2];

    // Open input file to read, throw error if can't.
    int openIn = open(inPath, O_RDONLY);
    if (openIn == -1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    // Open output file to write, create file if doesn't exist.
    // Throw error if can't.
    int openOut = open(outPath, O_WRONLY | O_CREAT);
    if (openOut == -1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    // Write to output file.

    // Close input and output files.

    return 0;
}
