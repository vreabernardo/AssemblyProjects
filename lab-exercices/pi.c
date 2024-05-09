#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double pi25DT = 3.141592653589793238462643;
double sumPi(int n); // assembly
int main(int argc, char *argv[])
{
    int n;
    double PI25DT = 3.141592653589793238462643; /* 25-digit-PI*/
    double pi, step, sum;
    n = atoi(argv[1]); /* the number of bins */
    step = 1.0 / (double)n;
    pi = 4.0 * step * sumPi(n);
    printf("Pi is approximately %.16f, Error is %.16f\n", pi,
           fabs(pi - PI25DT));
    return 0;
}