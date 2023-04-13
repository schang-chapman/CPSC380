# CPSC 380 Assignment 5: Thread Synchronization

## Gillian Canicosa, Sharon Chang, & Michael Woodward
## April 12, 2023

This project uses multithreading, semaphores, and mutex locks to solve the bounded buffer problem.

### References
* Thread functions
  * https://www.geeksforgeeks.org/thread-functions-in-c-c/
* Semaphore functions
  * https://www.geeksforgeeks.org/use-posix-semaphores-c/
* Program exit
  * https://en.cppreference.com/w/c/program/EXIT_status
* Mutex lock
  * https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/

### Source File(s)
* buffer.h
* prodcon.c

### Build Instructions
1. gcc prodcon.c -o prodcon -pthread
2. ./prodcon \<Delay\> \<Number of Producers\> \<Number of Consumers\>