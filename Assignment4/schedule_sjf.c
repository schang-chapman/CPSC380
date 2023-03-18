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
    insert(&head, task);
} 

void schedule(){
    // Sort the LinkedList
    struct node* iterateNode = head;
    struct node* compareNode = NULL;
    Task *tempTask = malloc(sizeof(Task));

    // Loop to iterate thru LinkedList
    while (iterateNode != NULL) {
        compareNode = iterateNode;
        // Loop to compare data for sorting (Traverse to second to last node)
        while (compareNode->next != NULL) {
            // Compare burst of current node and next node
            if (compareNode->task->burst < compareNode->next->task->burst) {
                // Swap tasks
                tempTask = compareNode->task;
                compareNode->task = compareNode->next->task;
                compareNode->next->task = tempTask;
            }
            compareNode = compareNode->next; // Traverse
        }
        iterateNode = iterateNode->next; // Traverse
    }

    // Loop to run tasks in LinkedList
    iterateNode = head;
    while (iterateNode != NULL) {
        run(iterateNode->task, iterateNode->task->burst);
        iterateNode = iterateNode->next;
    }
}