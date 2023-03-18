# CPSC 380 Assignment 4: CPU Scheduling

## Gillian Canicosa & Sharon Chang
## Mar. 17, 2023

This project uses demonstrates various methods of scheduling tasks to the CPU. It is written in C.

### References
* How to sort a LinkedList
    * https://stackoverflow.com/questions/35914574/sorting-linked-list-simplest-way
* Insert to tail of a LinkedList
    * https://www.log2base2.com/data-structures/linked-list/inserting-a-node-at-the-end-of-a-linked-list.html

### Source File(s)
Template Files
* Makefile
* book.txt
* pri-schedule.txt
* rr-schedule.txt
* schedule.txt
* cpu.c
* cpu.h
* driver.c
* list.c
* list.h
* schedulers.h
* task.h

Project Files
* schedule_fcfs.c
* schedule_priority.c
* schedule_priority_rr.c
* schedule_rr.c
* schedule_sjf.c

### Build Instructions
1. make fcfs
2. ./fcfs \<input file\>
3. make priority
4. ./priority \<input file\>
5. make priority_rr
6. ./priority_rr \<input file\>
7. make rr
8. ./rr \<input file\>
9. make sjf
10. ./sjf \<input file\>