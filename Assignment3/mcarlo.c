#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data shared by threads
int npoints;
int hitCount = 0;
double x;
double y;
void *runner(void *param);

// Generates double precision random number
double random_double() {
    return random() / ((double)RAND_MAX + 1);
}

// Check for points w/i circle
void *runner(void *param) {
    for (int i = 0; i < npoints; i ++) {
        // Generate random numbers from -1.0 to +1.0 (exclusive)
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;

        if (sqrt(x*x + y*y) < 1.0) {
            ++hitCount;
        }
    }
    pthread_exit(0);
}

int main(int argc, char* points[]) {
    pthread_t tid; // Thread ID
    pthread_attr_t attr; // Thread attributes

    // Get number of points from input
    npoints = atoi(points[1]);
    printf("Points Generated: %d\n", npoints);

    // Create & join thread
    int threadInt;

    threadInt = pthread_create(&tid,&attr,runner,points[1]);
    // Create error check
    if (threadInt != 0) {
        printf("Thread creation error: %s\n", strerror(errno));
    }
    threadInt = pthread_join(tid, NULL);
    // Join error check
    if (threadInt != 0) {
        printf("Thread join error: %s\n", strerror(errno));
    }

    printf("Points in Circle: %d\n", hitCount);
}