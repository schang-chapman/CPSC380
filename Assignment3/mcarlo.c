// Generates double precision random number
double random_double() {
    return random() / ((double)RAND_MAX + 1);
}

// Check for points w/i circle
int i;
int npoints;
int hitcount;

for (i = 0; i < npoints; i ++) {
    // Generate random numbers from -1.0 to +1.0 (exclusive)
    x = random_double() * 2.0 - 1.0;
    y = random_double() * 2.0 - 1.0;

    if (sqrt(x*x + y*y) < 1.0) {
        ++hitcount;
    }
}