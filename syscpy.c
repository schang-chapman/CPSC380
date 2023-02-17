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

    // Open output file to write, throw error if can't.

    // Write to output file.

    // Close input and output files.

    return 0;
}
