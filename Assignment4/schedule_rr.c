#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

struct node* head = NULL;

// Create a new task and insert to the list
void add(char *name, int priority, int burst){
    // Create task
    Task *task = malloc(sizeof(task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    // Insert to list
    insertTail(&head, task);
}   

void schedule(){
    // Sort the LinkedList
    struct node* iterateNode = head;
    int burstDiff = 0;

    // Traverse list and check bursts
    while (iterateNode != NULL) {
        burstDiff = iterateNode->task->burst - QUANTUM;
        // If burst is greater than quantum, add task with quantum subtracted from the burst
        // Set burst of current task to quantum
        if (burstDiff > 0) {
            add(iterateNode->task->name, iterateNode->task->priority, burstDiff);
            iterateNode->task->burst = QUANTUM;
        }
        iterateNode = iterateNode->next;
    }

    // Loop to run tasks thru LinkedList
    iterateNode = head;
    while (iterateNode != NULL) {
        run(iterateNode->task, iterateNode->task->burst);
        iterateNode = iterateNode->next;
    }
}