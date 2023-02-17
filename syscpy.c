#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *paths[]) {
    // Get paths from input.
    char *inPath = paths[1];
    char *outPath = paths[2];

    // Open input file to read, throw error if can't.
    int inFile = open(inPath, O_RDONLY);
    if (inFile == -1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    // Open output file to write, create file if doesn't exist.
    // Throw error if can't.
    int outFile = open(outPath, O_WRONLY | O_CREAT);
    if (outFile == -1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    // Write to output file.

    // Close input and output files.
    if (close(inFile) < 0) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }
    if (close(outFile) < 0) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    return 0;
}
