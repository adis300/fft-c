#include "fft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define IFAC 15

void discrete_fourier_transform()
{
    int n = 201; // 10 seconds of data, n has to be greater than 1
    double sample_rate = 20; // signal sampling rate
    double f = 2;    // frequency of the artifical signal
    int ifac[IFAC];
    double * input = (double *) alloca(n * sizeof(double));   //Input signal
    for(int i = 0; i < n; i ++) input[i] = sin(2 * PI * f * i/sample_rate);
    double * wsave = (double *) alloca((2 * n + IFAC) * sizeof(double));  //Initialize a working space with length at least 2*n + 15

    fft_real_init(n, wsave, ifac);
    fft_real_forward(n, input, wsave, ifac);
    for(int i = 0; i < n; i ++) printf("freq:%f, mag: %f\n",i/sample_rate, fabs(wsave[i]/n));
}

int main() {   
    printf("========= FFT example =========\n\n");
    discrete_fourier_transform();
    printf("========= Done. =========\n\n");
    return 0;
}

