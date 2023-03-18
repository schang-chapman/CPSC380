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
    struct node* iterateNode = head;

    // Loop to run tasks in LinkedList
    iterateNode = head;
    while (iterateNode != NULL) {
        run(iterateNode->task, iterateNode->task->burst);
        iterateNode = iterateNode->next;
    }
}