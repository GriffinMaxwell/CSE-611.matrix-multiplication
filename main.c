/*!
 * @author Griffin Maxwell
 * @date October 1, 2020
 * @assignment Homework 4
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
   N = 500,
   MatrixSize = N * N * sizeof(int32_t)
};

//! Function type for performing the matrix multiplication C = A * B in a particular loop order
typedef void (*MatrixMultiply_t)(int32_t *A, int32_t *B, int32_t *C);

static void ijk(int32_t *A, int32_t *B, int32_t *C)
{
   for(uint16_t i = 0; i < N; i++)
   {
      for(uint16_t j = 0; j < N; j++)
      {
         for(uint16_t k = 0; k < N; k++)
         {
            C[i + j * N] += A[i + k * N] * B[k + j * N];
         }
      }
   }
}

static void ikj(int32_t *A, int32_t *B, int32_t *C)
{
   for(uint16_t i = 0; i < N; i++)
   {
      for(uint16_t k = 0; k < N; k++)
      {
         for(uint16_t j = 0; j < N; j++)
         {
            C[i + j * N] += A[i + k * N] * B[k + j * N];
         }
      }
   }
}

static void jik(int32_t *A, int32_t *B, int32_t *C)
{
   for(uint16_t j = 0; j < N; j++)
   {
      for(uint16_t i = 0; i < N; i++)
      {
         for(uint16_t k = 0; k < N; k++)
         {
            C[i + j * N] += A[i + k * N] * B[k + j * N];
         }
      }
   }
}

static void jki(int32_t *A, int32_t *B, int32_t *C)
{
   for(uint16_t j = 0; j < N; j++)
   {
      for(uint16_t k = 0; k < N; k++)
      {
         for(uint16_t i = 0; i < N; i++)
         {
            C[i + j * N] += A[i + k * N] * B[k + j * N];
         }
      }
   }
}

static void kij(int32_t *A, int32_t *B, int32_t *C)
{
   for(uint16_t k = 0; k < N; k++)
   {
      for(uint16_t i = 0; i < N; i++)
      {
         for(uint16_t j = 0; j < N; j++)
         {
            C[i + j * N] += A[i + k * N] * B[k + j * N];
         }
      }
   }
}

static void kji(int32_t *A, int32_t *B, int32_t *C)
{
   for(uint16_t k = 0; k < N; k++)
   {
      for(uint16_t j = 0; j < N; j++)
      {
         for(uint16_t i = 0; i < N; i++)
         {
            C[i + j * N] += A[i + k * N] * B[k + j * N];
         }
      }
   }
}

static void PeformTrialWithOrder(MatrixMultiply_t multiply)
{
   int32_t *A = malloc(MatrixSize);
   arc4random_buf(A, MatrixSize);

   int32_t *B = malloc(MatrixSize);
   arc4random_buf(B, MatrixSize);

   int32_t *C = malloc(MatrixSize);
   memset(C, 0x00, MatrixSize);

   clock_t beforeTime, afterTime;

   beforeTime = clock();
   multiply(A, B, C);
   afterTime = clock();

   printf("before: %lu\n", beforeTime);
   printf("after: %lu\n", afterTime);
   printf("difference: %lu\n", (afterTime - beforeTime) / 1000);
   printf("result: %d %d ...\n", C[0], C[1]);

   free(A);
   free(B);
   free(C);
}

int main()
{
   printf("Hello world\n");

   printf("run: ijk\n");
   PeformTrialWithOrder(ijk);

   printf("\nrun: ikj\n");
   PeformTrialWithOrder(ikj);

   printf("\nrun: jik\n");
   PeformTrialWithOrder(jik);

   printf("\nrun: jki\n");
   PeformTrialWithOrder(jki);

   printf("\nrun: kij\n");
   PeformTrialWithOrder(kij);

   printf("\nrun: kji\n");
   PeformTrialWithOrder(kji);

   return 0;
}
