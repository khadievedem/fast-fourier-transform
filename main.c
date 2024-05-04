#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "fourier.h"

static void free_(void *ptr) 
{
    free(*(void**) ptr); 
}

int8_t _main()
{
  uint32_t i, j, N, k;
  __attribute__((cleanup(free_))) int32_t* src;
  __attribute__((cleanup(free_))) double complex* dest;

  /* Input the number of Fourier coeffs */
  printf("Enter the number of Fourier coeffs: ");
  scanf("%d", &N); putnl();
  if (N < 1) {
    fprintf(stderr, "Error. The number of Fourier coeffs shouble be > 1");
    return -1;
  }

  /* Input the size of output Fourier series */
  printf("Enter size of the final Fourier series: ");
  scanf("%d", &k); putnl();
  if (k < N) {
    fprintf(stderr, "Error. The final Fourier series size should be >= N");
    return -1;
  }

  src = malloc(k * sizeof(int32_t));
  dest = malloc(k * sizeof(double complex));
  memset((void*)src, 0, k * sizeof(int32_t));
  memset((void*)dest, 0, k * sizeof(double complex));

  /* Input an array of Fourier coeffs */
  printf("Enter %d Fourier coeffs:\n", N);
  for (i = 0; i < N; ++i)
  {
    /* Scan the real part */
    printf("[%d]: ", i + 1);
    scanf("%d", &src[i]); putnl();
  }
  putnl();

  /* Print the initial array on the screen */
  for(i = 0; i < N; ++i)
    printf("%d\n", src[i]);

  /* Initialize dest array */
  for (i = 0; i < k; ++i)
    dest[i] = 0;

  /* Compute the DFT */
  ddft(dest, src, N, k);

  /* Print result array on the screen */
  puts("Result:");
  for(i = 0; i < k; ++i)
    printf("%.2f + i%.2f\n", creal(dest[i]), cimag(dest[i]));

  return 0;
}


int32_t main(int argc, char *argv[])
{
  return _main();
}
