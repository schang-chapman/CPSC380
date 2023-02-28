# CPSC 380 Assignment 2: Fork Process

## Sharon Chang
## Feb. 22, 2023

This project uses C to create a shell interface that can accept and execute user commands.

### References
* Getting user input in C
  * https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
* String tokenizer in C
  * https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
* String comparison in C
  * https://www.programiz.com/c-programming/library-function/string.h/strcmp
* fork() in C
  * https://www.geeksforgeeks.org/fork-system-call/
* execvp() in C
  * https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/e/execvp.html
* wait() in C
  * https://www.geeksforgeeks.org/wait-system-call-c/

### Source File(s)
* sshell.c

### Build Instructions
1. gcc sshell.c -o sshell
2. ./sshell
