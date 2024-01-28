#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifndef  M_PI
  #define  M_PI  3.1415926535897932384626433
#endif

#define putnl() putc('\n', stdout)

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


int8_t _main()
{
  uint32_t i, j, N, k;
  double tmp;

  /* Input the number of Fourier coeffs */
  printf("Enter the number of Fourier coeffs: ");
  scanf("%d", &N);
  putnl();
  if (N < 1) return -1;

  /* Input the size of output Fourier series */
  printf("Enter size of the final Fourier series: ");
  scanf("%d", &k);
  putnl();
  if (k < N) return -1;

  double complex x[N], X[k];

  /* Input an array of Fourier coeffs */
  printf("Enter %d Fourier coeffs:\n", N);
  for (i = 0; i < N; ++i)
  {
    x[i] = 0;

    /* Scan the real part */
    printf("[%d] Real part: ", i + 1);
    scanf("%lf", &tmp);
    putnl();
    x[i] += tmp;

    /* Scan the imagine part */
    printf("[%d] Imagine part: ", i + 1);
    scanf("%lf", &tmp);
    putnl();
    x[i] += tmp * I;
  }
  putnl();

  /* Print the initial array on the screen */
  for(i = 0; i < N; ++i)
    printf("%f + i%f\n", creal(x[i]), cimag(x[i]));

  /* Initialize X array */
  for (i = 0; i < k; ++i)
    X[i] = 0;

  /* Compute the DFT */
  ddft(X, x, N, k);

  /* Print result array on the screen */
  puts("Result:");
  for(i = 0; i < k; ++i)
    printf("%f + i%f\n", creal(X[i]), cimag(X[i]));

  return 0;
}


int32_t main(int argc, char *argv[])
{
  return _main();
}
