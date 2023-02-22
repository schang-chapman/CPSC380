# CPSC 380 Assignment 1: Simple File Copy

## Sharon Chang
## Feb. 17, 2023

This project uses system calls to copy the contents of one file into another file. It is written in C.

### References
* System call usage
    * https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
* strerror() usage
    * https://www.tutorialspoint.com/c_standard_library/c_function_strerror.htm

### Source File(s)
* syscpy.c

### Build Instructions
1. gcc syscpy.c -o syscpy
2. ./syscpy \<input file\> \<output file\>
