#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *paths[]) {
    // Get paths from input.
    char *inPath = paths[1];
    char *outPath = paths[2];

    // Open input file.
    int inFile = open(inPath, O_RDONLY);
    if (inFile == -1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    // Open output file, create file if doesn't exist.
    int outFile = open(outPath, O_WRONLY | O_CREAT);
    if (outFile == -1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    // Copy input file to output file.
    char c[1];
    int inContents = 1;
    int writeOut = 1;
    while (inContents != 0) {
        // Read contents from input.
        inContents = read(inFile, c, 1);
        if (inContents == -1) {
            printf("Error: %s\n", strerror(errno));
            return -1;
        }
        // Write contents to output.
        else if (inContents != 0) {
            writeOut = write(outFile, c, 1);
                if (writeOut == -1) {
                    printf("Error: %s\n", strerror(errno));
                    return -1;
                }
        } 
    }

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
