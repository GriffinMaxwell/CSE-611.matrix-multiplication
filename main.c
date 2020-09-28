/*!
 * @author Griffin Maxwell
 * @date October 1, 2020
 * @assignment Homework 4
 *
 * @brief An experiment to measure the time it takes to perform a 5000x5000
 * matrix multiplication for each of the 6 possible loop orderings. The setup
 * for this experiment is as follows:
 *
 * Each "trial" allocates three 5000x5000 U32 matrices: A, B, and C. A and B
 * are filled with random data, while C is initially zeroed out. Then, the
 * multiplication C = A * B will be performed using an assigned loop order and
 * the time it takes to do this calculation will be measured and displayed.
 *
 * A "run" consists of a single trial for each loop ordering.
 *
 * The "full experiment" consists of 5 runs. The resulting 5 time measurements
 * for each loop ordering are averaged and displayed. Then these averages can
 * be compared and analyzed.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
   N = 500, // Matrix dimension
   NumberOfRuns = 5
};

//! Function type for performing the matrix multiplication C = A * B in a particular loop order
typedef void (*MatrixMultiplication_t)(int32_t *A, int32_t *B, int32_t *C);

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

static void PeformTrial(MatrixMultiplication_t multiply, clock_t *timeElapsedUsec)
{
   size_t MatrixNumBytes = N * N * sizeof(int32_t);

   int32_t *A = malloc(MatrixNumBytes);
   arc4random_buf(A, MatrixNumBytes);

   int32_t *B = malloc(MatrixNumBytes);
   arc4random_buf(B, MatrixNumBytes);

   int32_t *C = malloc(MatrixNumBytes);
   memset(C, 0x00, MatrixNumBytes);

   clock_t before, after;

   before = clock();
   multiply(A, B, C);
   after = clock();

   *timeElapsedUsec = after - before;

   printf(" %lu usec\n", *timeElapsedUsec);

   free(A);
   free(B);
   free(C);
}

static void PerformRunOfTrials(void)
{
   clock_t timeElapsedUsec;

   printf("- Trial ijk:");
   PeformTrial(ijk, &timeElapsedUsec);

   printf("- Trial ikj:");
   PeformTrial(ikj, &timeElapsedUsec);

   printf("- Trial jik:");
   PeformTrial(jik, &timeElapsedUsec);

   printf("- Trial jki:");
   PeformTrial(jki, &timeElapsedUsec);

   printf("- Trial kij:");
   PeformTrial(kij, &timeElapsedUsec);

   printf("- Trial kji:");
   PeformTrial(kji, &timeElapsedUsec);
}

int main(void)
{
   printf("# Experimental Data:\n");

   for(uint8_t i = 0; i < NumberOfRuns; i++)
   {
      printf("\n## Run %d:\n", i);
      PerformRunOfTrials();
   }
   return 0;
}
