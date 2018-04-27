# fft-c
FFTPACK is one of the package that has the best performance comparing all other tools. This repository makes fft.c from fftpack user-friendly.

Original code at [http://www.netlib.org/fftpack/](http://www.netlib.org/fftpack/)
* `fft32` is the original package in float precision
* `fft` is the default package using double precision for modern computers

# Alternative libraries
* CCMATH: [http://freshmeat.sourceforge.net/projects/ccmath](http://freshmeat.sourceforge.net/projects/ccmath)

# Run example
```
make example
./example
```

# Steps to transform your signal
1. Create and manage your input signal, including memory
2. Initialize fourier transformer
```
// n: length of the signal
// scale_output: FFT_SCALED_OUTPUT or FFT_UNSCALED_OUTPUT
FFTTransformer* transformer = create_fft_transformer(n, FFT_SCALED_OUTPUT);
```
3. Transform signal
```
double * output = fft_forward(transformer, input);
```
4. Your output is here 
```
for(int i = 0; i < transformer -> n; i ++) printf("freq:%f, mag: %f\n" i/SAMPLE_RATE, fabs(output[i]));
```
5. After all transformation is done, release memory
```
free_fft_transformer(transformer);
```
* NOTE: You could also fetch previous transform result by looking at
`transformer -> output` of type` (double*)`. 

# Methods available from `fft.h`
1. `FFTTransformer * create_fft_transformer(int signal_length, int scale_output);`
2. `void free_fft_transformer(FFTTransformer * transformer);`
3. `double * fft_forward(FFTTransformer * transformer, double* input);`
4. `double * fft_backward(FFTTransformer * transformer, double* input);`

5. `FFTCosqTransformer * create_fft_cosq_transformer(int signal_length, int scale_output);`
6. `void free_cosq_fft_transformer(FFTCosqTransformer * transformer);`
7. `double * fft_cosq_forward(FFTCosqTransformer * transformer, double* input);`
8. `double * fft_cosq_backward(FFTCosqTransformer * transformer, double* input);`