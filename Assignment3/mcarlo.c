#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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
}

int main(int argc, char* paths[]) {
    
}