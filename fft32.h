/*
 * fft.h
 *
 * Copyright (c) 2018 Disi A
 * 
 * Author: Disi A
 * Email: adis@live.cn
 * https://www.mathworks.com/matlabcentral/profile/authors/3734620-disi-a
 * 
 * http://www.netlib.org/fftpack/doc
 * 
 * PARAMETERS:
 * * int n;          The length of the sequence to be transformed.
 * * float *x;       A real array of length n which contains the sequenceto be transformed
 * * float *wsave;   A work array which must be dimensioned at least 2*n+15.
 * *                 the same work array can be used for both rfftf and rfftb
 * *                 as long as n remains unchanged. different wsave arrays
 * *                 are required for different values of n. the contents of
 * *                 wsave must not be changed between calls of rfftf or rfftb.
 * * int *ifac;      Array containing factors of the problem dimensions.
 * *                 (initialization requirements are probably similar to wsave)
 * *                 Some docs say it needs to be 15 elements, others say n.
 * *                 Maybe n + 15 is safest.
 * 
 * More documentation from original FFTPACK
 * http://www.netlib.org/fftpack/doc
 * 
 * Some other usage reference: https://www.experts-exchange.com/questions/21416267/how-to-use-C-version-of-fftpack-a-public-domain-DFT-library.html
 */

#ifndef _fft32_h
#define _fft32_h
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FFT_SCALED_OUTPUT 1
#define FFT_UNSCALED_OUTPUT 0
#define FFT_IFAC 15

typedef struct {

    int n;
    float * output;
    int * ifac;
    int scale_output; // 1 for scale and 0 for not scale

} FFTTransformer;

typedef struct {

    int n;
    float * output;
    int * ifac;
    int scale_output; // 1 for scale and 0 for not scale

} FFTCosqTransformer;

// Initialization real fft transform (__ogg_fdrffti)
void __fft_real_init(int n, float *wsave, int *ifac);
// Forward transform of a real periodic sequence (__ogg_fdrfftf)
void __fft_real_forward(int n,float *r,float *wsave,int *ifac);
// Real FFT backward (__ogg_fdrfftb)
void __fft_real_backward(int n, float *r, float *wsave, int *ifac); 

// Initialize cosine quarter-wave transform (__ogg_fdcosqi)
void __fft_cosq_init(int n, float *wsave, int *ifac);
// Real cosine quarter-wave forward transform (__ogg_fdcosqf)
void __fft_cosq_forward(int n,float *x,float *wsave,int *ifac);
// Real cosine quarter-wave backward transform (__ogg_fdcosqb)
void __fft_cosq_backward(int n,float *x,float *wsave,int *ifac);

// Wrapper method with all fftpack parameters properly initilized
// Wrapper method with all fftpack parameters properly initilized
FFTTransformer * create_fft_transformer(int signal_length, int scale_output){
    FFTTransformer * transformer = (FFTTransformer *) malloc(sizeof(FFTTransformer));
    transformer -> ifac = (int *) calloc(15, sizeof(int));
    transformer -> output = (float *) malloc((2 * signal_length + 15) * sizeof(float));
    transformer -> n = signal_length;
    if(scale_output == FFT_SCALED_OUTPUT) transformer -> scale_output = FFT_SCALED_OUTPUT;
    else transformer -> scale_output = FFT_UNSCALED_OUTPUT;
    return transformer;
}

void free_fft_transformer(FFTTransformer * transformer){
    free(transformer -> output);
    free(transformer -> ifac);
    free(transformer);
}

float * fft_forward(FFTTransformer * transformer, float* input){
    __fft_real_forward(transformer -> n, input, transformer -> output, transformer -> ifac);
    // Rescale output for valid region
    if(transformer -> scale_output == FFT_SCALED_OUTPUT){
        for(int i = 0; i < transformer -> n; i++) transformer -> output[i] /= transformer -> n;
    }
    return transformer -> output;
}

float * fft_backward(FFTTransformer * transformer, float* input){
    __fft_real_backward(transformer -> n, input, transformer -> output, transformer -> ifac);

    // Rescale output for valid region
    if(transformer -> scale_output == FFT_SCALED_OUTPUT){
        for(int i = 0; i < transformer -> n; i++) transformer -> output[i] *= transformer -> n;
    }
    return transformer -> output;
}

FFTCosqTransformer * create_fft_cosq_transformer(int signal_length, int scale_output){
    FFTCosqTransformer * transformer = (FFTCosqTransformer *) malloc(sizeof(FFTCosqTransformer));
    transformer -> ifac = (int *) calloc(15, sizeof(int));
    transformer -> output = (float *) malloc((3 * signal_length + 15) * sizeof(float));
    transformer -> n = signal_length;
    if(scale_output == FFT_SCALED_OUTPUT) transformer -> scale_output = FFT_SCALED_OUTPUT;
    else transformer -> scale_output = FFT_UNSCALED_OUTPUT;
    return transformer;
}

void free_cosq_fft_transformer(FFTCosqTransformer * transformer){
    free(transformer -> output);
    free(transformer -> ifac);
    free(transformer);
}

float * fft_cosq_forward(FFTCosqTransformer * transformer, float* input){
    __fft_cosq_forward(transformer -> n, input, transformer -> output, transformer -> ifac);
    // Rescale output for valid region
    if(transformer -> scale_output == FFT_SCALED_OUTPUT){
        for(int i = 0; i < transformer -> n; i++) transformer -> output[i] /= transformer -> n;
    }
    return transformer -> output;
}

float * fft_cosq_backward(FFTCosqTransformer * transformer, float* input){
    __fft_cosq_backward(transformer -> n, input, transformer -> output, transformer -> ifac);
    // Rescale output for valid region
    if(transformer -> scale_output == FFT_SCALED_OUTPUT){
        for(int i = 0; i < transformer -> n; i++) transformer -> output[i] *= transformer -> n;
    }
    return transformer -> output;
}
#ifdef __cplusplus
}
#endif

#endif /* _fft32_h */
