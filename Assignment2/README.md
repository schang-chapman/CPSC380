# CPSC 380 Assignment 2: Fork Process

## Sharon Chang
## Feb. 22, 2023

This project uses C to create a shell interface that can accept and execute user commands.

### Known Bugs/Errors
* "osh>" will not appear immediately after completing an input command. Instead, the shell stays stuck at the end of the command's output. Hit enter after completing a command to see "osh>" again.
  * I thought this had something to do with buffering problems on my output stream but I put flushes everywhere and still couldn't get rid of it so now I give up.

### References
* Getting user input
  * https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
* Stripping newlines
  * https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
* String to array tokenization
  * https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
* String comparison
  * https://www.programiz.com/c-programming/library-function/string.h/strcmp
* fork() usage
  * https://www.geeksforgeeks.org/fork-system-call/
* execvp() usage
  * https://www.qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_lib_ref/e/execvp.html
* wait() usage
  * https://www.geeksforgeeks.org/wait-system-call-c/

### Source File(s)
* sshell.c

### Build Instructions
1. gcc sshell.c -o sshell
2. ./sshell

### Example Output
```
osh>cat ex.txt
osh>This is an example.
osh>exit
```
