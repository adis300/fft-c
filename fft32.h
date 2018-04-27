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

#ifndef _fft_h
#define _fft_h


#ifdef __cplusplus
extern "C" {
#endif

// Initialization real fft transform (__ogg_fdrffti)
void fft_real_init(int n, float *wsave, int *ifac);
// Forward transform of a real periodic sequence (__ogg_fdrfftf)
void fft_real_forward(int n,float *r,float *wsave,int *ifac);
// Real FFT backward (__ogg_fdrfftb)
void fft_real_backward(int n, float *r, float *wsave, int *ifac); 

// Initialize cosine quarter-wave transform (__ogg_fdcosqi)
void fft_cosq_init(int n, float *wsave, int *ifac);
// Real cosine quarter-wave forward transform (__ogg_fdcosqf)
void fft_cosq_forward(int n,float *x,float *wsave,int *ifac);
// Real cosine quarter-wave backward transform (__ogg_fdcosqb)
void fft_cosq_backward(int n,float *x,float *wsave,int *ifac);

#ifdef __cplusplus
}
#endif

#endif /* _fft_h */
