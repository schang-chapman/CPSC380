# CPSC 380 Assignment 3: Monte Carlo

## Sharon Chang
## March 3, 2023

This project uses C to run Monte Carlo simulations that estimate the value of pi.

### Known Bugs/Errors
* -

### References
* Threads example files from class
* pthread C functions
  * https://man7.org/linux/man-pages/man3/pthread_create.3.html
  * https://man7.org/linux/man-pages/man3/pthread_join.3.html
* Undefined reference compile error solutions
  * https://stackoverflow.com/questions/10409032/why-am-i-getting-undefined-reference-to-sqrt-error-even-though-i-include-math
  * https://stackoverflow.com/questions/1662909/undefined-reference-to-pthread-create-in-linux

### Source File(s)
* mcarlo.c

### Build Instructions
1. gcc mcarlo.c -o mcarlo -lm -pthread
2. ./mcarlo \<Integer Number\>
