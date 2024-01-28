#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifndef  M_PI
  #define  M_PI  3.1415926535897932384626433
#endif

/******************************************************
 * ddft -- Computes the Discrete Fourier Transform
 *
 * Parameters
 *    dest -- The pointer to the array for the result
 *    x    -- The pointer to the sequence of N numbers
 *    k    -- Length of the transformed axis of the output (Size of the *dest array).
 *    N    -- Size of the *x array
 *
 * Returns
 *    result code:
 *      0    -- For success
 *     -1    -- Something got failed
 *
 * Notes
 *    this function will change values inside the *src
 ******************************************************/
int8_t ddft(double complex *dest, double complex *x, uint16_t k, uint16_t N)
{
  /* Output array should be >= initial array */
  if (k < N) return -1;
  if (dest == NULL || x == NULL) return -1;

  int32_t i, j;
  double complex res_dft[k], v_exp;

  for (i = 0; i < k; ++i)
    res_dft[i] = 0;

  for(j = 0; j < k; ++j) {
    for (i = 0; i < N; ++i) {
      /* Compute the principal Nth root of unity */
      v_exp = cexp((-I * 2 * M_PI * j * i) / N);

      res_dft[j] += x[i] * v_exp;
    }
  }

  /* Copy the result to the destination array */
  for(i = 0; i < k; ++i)
    dest[i] = res_dft[i];

  return 0;
}



int32_t main(int argc, char *argv[])
{
  uint32_t i, j, N, k;

  printf("Enter size of an Fourier coeffs: ");
  scanf("%d %d", &N, &k);
  printf("\n");

  double complex x[N], X[k];

  for (i = 0; i < k; ++i) {
    X[i] = 0;
  }

  /* printf("%f + i%f", creal(a), cimag(a));

   for(i = 0; i < N; ++i) {
     printf("%f\n", creal(x[i]));
   }
  */

  ddft(X, x, N, k);

  printf("------\n");

  for(i = 0; i < k; ++i) {
    printf("%f + i%f\n", creal(X[i]), cimag(X[i]));
  }

  return 0;
}
