#include <stdlib.h>
#include <stdio.h>
#include "list.h"

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
    //TODO
}