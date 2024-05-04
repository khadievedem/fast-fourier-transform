#include "fourier.h"
#include <complex.h>
#include <stdlib.h>
#include <math.h>

int8_t ddft(/* out */ double complex* v_out, /* in */ const int32_t* const v_in, /* in */ uint32_t k, /* in */ uint32_t N)
{
  /* Output array should be >= initial array */
  if (k < N) return -1;
  if (v_out == NULL || v_in == NULL) return -1;

  /* Use in loops */
  uint32_t i, j;
  double complex res_dft[k], v_exp;

  for(j = 0; j < k; ++j) {
    res_dft[j] = 0;

    for (i = 0; i < N; ++i) {
      /* Compute the principal Nth root of unity */
      v_exp = cexp((-I * 2 * M_PI * j * i) / N);

      res_dft[j] += v_in[i] * v_exp;
    }
  }

  /* Copy the result to the destination array */
  for(i = 0; i < k; ++i)
    v_out[i] = res_dft[i];

  return 0;
}

int8_t fft_(/* out */ double complex *v_out,  /* in */ const int32_t * const v_in, /* in */ uint32_t stride, /* in */ uint32_t N)
{
    /* Use in loops */
    uint32_t i;
    /* Temporary variables */
    double complex tmp_out, tmp_exp;

    /* Output array should be >= initial array */
    if (v_in == NULL || v_out == NULL) return -1;

    /* At the lowest level pass through */
    if (N == 1) {
        v_out[0] = v_in[0];
        return 0;
    }
    /* Recursively split in two, then combine beneath. */
    fft_(v_out, v_in, 2 * stride, N/2);
    fft_(v_out + N/2, v_in + stride, 2 * stride, N/2);

    for (i = 0; i < N/2; i++) {
        tmp_out = v_out[i];
        tmp_exp = cexp(0 + (2 * M_PI * i / N) * I);

        /* Odd numbers */
        v_out[i] = tmp_out + (tmp_exp * v_out[i + N/2]);

        /* Even numbers */
        v_out[i + N/2] = tmp_out - (tmp_exp * v_out[i + N/2]);
    }
    return 0;
}

int8_t fft(/* out */ double complex* v_out, /* in */ const int32_t* const v_in, /* in */ uint32_t N)
{
  return fft_(v_out, v_in, 1, N);
}
