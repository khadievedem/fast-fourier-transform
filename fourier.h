#include <stdint.h>
#include <complex.h>

#ifndef  M_PI
  #define M_PI 3.1415926535897932384626433
#endif

#define putnl() putc('\n', stdout)

/******************************************************
 * ddft -- Computes the Discrete Fourier Transform
 *
 * Parameters
 *    v_out -- The pointer to the array for the result
 *    v_in  -- The pointer to the sequence of N numbers
 *    k    -- Length of the transformed axis of the output (Size of the *dest array).
 *    N    -- Size of the *x array
 *
 * Returns
 *    result code:
 *      0    -- For success
 *     -1    -- Something got failed
 *
 * Notes
 *    this function will change values inside the *v_out
 ******************************************************/
int8_t ddft(/* out */ double complex* v_out, /* in */ const int32_t* const v_in, /* in */ uint32_t k, /* in */ uint32_t N);


/******************************************************
 * fft -- Fast Fourier Transform
 *
 * Parameters
 *    v_out -- The pointer to the array for the result
 *    v_in  -- The pointer to the sequence of N numbers
 *    N    -- Size of the *x array
 *
 * Returns
 *    result code:
 *      0    -- For success
 *     -1    -- Something got failed
 *
 * Notes
 *    this function will change values inside the *v_out
 ******************************************************/
int8_t fft(/* out */ double complex* v_out, /* in */ const int32_t* const v_in, /* in */ uint32_t N);
