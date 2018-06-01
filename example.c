#include "fft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

void fftpack_fourier_forward()
{
    printf("---------- fftpack fourier transform example ----------\n");
    int n = 201; // 10 seconds of data, n has to be greater than 1
    double sample_rate = 20; // signal sampling rate
    double f = 2;    // frequency of the artifical signal
    int ifac[FFT_IFAC];
    double * input = (double *) alloca(n * sizeof(double));   //Input signal
    for(int i = 0; i < n; i ++) input[i] = sin(2 * PI * f * i/sample_rate);
    double * wsave = (double *) alloca((2 * n + FFT_IFAC) * sizeof(double));  //Initialize a working space with length at least 2*n + 15

    __fft_real_init(n, wsave, ifac);
    __fft_real_forward(n, input, wsave, ifac);
    for(int i = 0; i < n; i ++) printf("freq:%f, mag: %f\n",i/sample_rate, fabs(wsave[i]/n));

    printf("---------- fftpack fourier example end ----------\n");

}

void fourier_example()
{
    printf("---------- wrapped fourier transform example ----------\n");

    // Construct input signal
    double sample_rate = 20; // signal sampling rate
    int T = 10; 
    int n = T * sample_rate + 1; // 10 seconds of data, n has to be greater than 1
    double f = 2;    // frequency of the artifical signal
    double * input = (double *) alloca(n * sizeof(double));   //Input signal
    for(int i = 0; i < n; i ++) input[i] = sin(2 * PI * f * i/sample_rate);

    // Initialize fourier transformer
    FFTTransformer* transformer = create_fft_transformer(n, FFT_SCALED_OUTPUT);

    // Transform signal
    double * output = fft_forward(transformer, input);

    // Print output
    for(int i = 0; i < transformer -> n; i ++) printf("freq:%f, mag: %f\n", (double)i/(2*T), fabs(output[i]));

    free_fft_transformer(transformer);
    printf("---------- wrapped fourier transform example end ----------\n");

}

int main() {   
    printf("========= FFT example =========\n\n");
    fftpack_fourier_forward();
    fourier_example();
    printf("========= Done. =========\n\n");
    return 0;
}

