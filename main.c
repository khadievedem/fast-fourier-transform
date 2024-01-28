#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifndef  M_PI
  #define  M_PI  3.1415926535897932384626433
#endif

/* 
 * This function will change the values inside X
 *
 * */
void ddft(double complex *X, double complex x[], uint16_t N, uint16_t k)
{
  int32_t i, j;
  double complex res_dft[k], v_exp;

  for (i = 0; i < k; ++i) {
    res_dft[i] = 0;
  }

  for(j = 0; j < k; ++j) {
    for (i = 0; i < N; ++i) {
      /* 
       * printf("[%d] %f * exp((-I * 2 * PI * %d * %d) / N)\n", j, creal(x[i]), j, i);
       */
      v_exp = cexp((-I * 2 * M_PI * j * i) / N);
      
      printf("TEST: i%f + %f\n", creal(v_exp), cimag(v_exp));

      res_dft[j] += x[i] * v_exp;
      /* double complex test = exp((-I * 2 * M_PI * j * i) / N); */
    }
    printf("= i%f + %f\n", creal(res_dft[j]), cimag(res_dft[j]));
  }

  for(i = 0; i < k; ++i) {
    X[i] = res_dft[i];
  }
}



int32_t main(int argc, char *argv[])
{
  int32_t i = 0, j = 0;
  double complex *X;
  uint16_t N = 8, k = 8;

  double complex x[] = {1 , -1, 1, -1, 5, 4, 3, 2};

  X = malloc(sizeof(X) * k);

  /* printf("%f + i%f", creal(a), cimag(a)); */

  for(i = 0; i < N; ++i) {
    printf("%f\n", creal(x[i]));
  }

  ddft(X, x, N, k);
  printf("------\n");

  for(i = 0; i < k; ++i) {
    printf("%f + i%f\n", creal(X[i]), cimag(X[i]));
  }

  free(X);

  return 0;
}
