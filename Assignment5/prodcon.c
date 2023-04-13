#include "buffer.h"
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Buffer
buffer_item buffer[BUFFER_SIZE];

// Threads
void *producer(void *param);
void *consumer(void *param);

// Misc.
int in = 0;
int out = 0;
pthread_mutex_t mutex;
sem_t *empty;
sem_t *full;

uint16_t checksum(char *addr, uint32_t count) {
    register uint32_t sum = 0;
    uint16_t *buf = (uint16_t *) addr;
    
    // Main summing loop
    while (count > 1) {
        sum = sum + *(buf)++;
        count = count - 2;
    } 
    // Add left-over byte, if any
    if (count > 0) {
        sum = sum + *addr;
    }
    // Fold 32-bit sum to 16 bits
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    return (~sum);
}

// Insert item to buffer
int insert_item(buffer_item *item) {
    memcpy(&buffer[in], item, sizeof(buffer_item));
    in = (in+1) % NUM_ITEMS;
    return 0;
}

// Remove item from buffer
int remove_item(buffer_item *item) {
    memcpy(item, &buffer[out], sizeof(buffer_item));
    out = (out+1) % NUM_ITEMS;
    return 0;
}

// Producer thread
void *producer(void *param) {
    buffer_item item;
    while (true) {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            item.buffer[i] = rand() % 256;
        }
        item.cksum = checksum((char*)item.buffer, BUFFER_SIZE);

        // LOCK: Inserting to buffer
        sem_wait(empty);
        pthread_mutex_lock(&mutex);

        if (insert_item(&item) != 0) {
            printf("Buffer insertion error: %s\n", strerror(errno));
        }

        pthread_mutex_unlock(&mutex);
        sem_post(full);
        // RELEASE
    }
    pthread_exit(0);
}

// Consumer thread
void *consumer(void *param) {
    buffer_item item;
    while (true) {
        // LOCK: Removing from buffer
        sem_wait(full);
        pthread_mutex_lock(&mutex);

        if (remove_item(&item) != 0) {
            printf("Buffer removal error: %s\n", strerror(errno));
        }

        pthread_mutex_unlock(&mutex);
        sem_post(empty);
        // RELEASE

        int resultSum = checksum(item.buffer, BUFFER_SIZE);

        if (item.cksum != resultSum) {
            printf("Checksum error.\nExpected: %X\nResult: %X\n", item.cksum, resultSum);
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    // Get args from cmd line
    if (argc != 4) {
        printf("Error: 4 arguments needed.\n");
        return -1;
    }
    int delay = atoi(argv[1]);
    int prodNum = atoi(argv[2]);
    int conNum = atoi(argv[3]);
    
    // Initialize buffer
    buffer_item *item = malloc(sizeof(buffer_item));

    // Create mutex & semaphores
    sem_unlink("empty");
    sem_unlink("full");

    empty = sem_open("empty", O_CREAT, 0666, NUM_ITEMS);
    full = sem_open("full", O_CREAT, 0666, 0);

    if (empty == SEM_FAILED || full == SEM_FAILED) {
        printf("Semaphore creation error: %s\n", strerror(errno));
    }

    // Create threads
    for (int i = 0; i < prodNum; i++) {
        pthread_t prodThread;
        int prodID = pthread_create(&prodThread, NULL, producer, NULL);
        
        if (prodID != 0) {
            printf("Producer thread creation error: %s\n", strerror(errno));
            return -1;
        }
    }

    for (int i = 0; i < conNum; i++) {
        pthread_t conThread;
        int conID = pthread_create(&conThread, NULL, consumer, NULL);
        
        if (conID != 0) {
            printf("Consumer thread creation error: %s\n", strerror(errno));
            return -1;
        }
    }

    // Sleep
    sleep(delay);

    // Exit
    sem_close(empty);
    sem_unlink("empty");
    sem_close(full);
    sem_unlink("full");
    return 0;
}