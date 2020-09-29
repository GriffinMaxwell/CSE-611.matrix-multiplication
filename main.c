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
   N = 500,
   NumberOfRuns = 5
};

typedef struct
{
   double ijk;
   double ikj;
   double jik;
   double jki;
   double kij;
   double kji;
} Results_t;

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

static void PeformTrial(MatrixMultiplication_t multiply, double *results)
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

   *results = ((double)after - before) / 1000000.;

   printf(" %f seconds\n", *results);

   free(A);
   free(B);
   free(C);
}

static void PerformRunOfTrials(Results_t *results)
{
   printf("- Trial ijk:");
   PeformTrial(ijk, &results->ijk);

   printf("- Trial ikj:");
   PeformTrial(ikj, &results->ikj);

   printf("- Trial jik:");
   PeformTrial(jik, &results->jik);

   printf("- Trial jki:");
   PeformTrial(jki, &results->jki);

   printf("- Trial kij:");
   PeformTrial(kij, &results->kij);

   printf("- Trial kji:");
   PeformTrial(kji, &results->kji);
}

int main(void)
{
   Results_t runResults[NumberOfRuns];

   printf("# Experimental Data:\n");

   for(uint8_t i = 1; i <= NumberOfRuns; i++)
   {
      printf("\n## Run %d:\n", i);
      PerformRunOfTrials(&runResults[i]);
   }

   printf("\n# Results\n");

   Results_t averages = { 0 };

   for(uint8_t i = 0; i < NumberOfRuns; i++)
   {
      averages.ijk += runResults[i].ijk;
      averages.ikj += runResults[i].ikj;
      averages.jik += runResults[i].jik;
      averages.jki += runResults[i].jki;
      averages.kij += runResults[i].kij;
      averages.kji += runResults[i].kji;
   }

   averages.ijk /= NumberOfRuns;
   averages.ikj /= NumberOfRuns;
   averages.jik /= NumberOfRuns;
   averages.jki /= NumberOfRuns;
   averages.kij /= NumberOfRuns;
   averages.kji /= NumberOfRuns;

   printf("- Average time for ijk: %f seconds\n", averages.ijk);
   printf("- Average time for ikj: %f seconds\n", averages.ikj);
   printf("- Average time for jik: %f seconds\n", averages.jik);
   printf("- Average time for jki: %f seconds\n", averages.jki);
   printf("- Average time for kij: %f seconds\n", averages.kij);
   printf("- Average time for kji: %f seconds\n", averages.kji);

   return 0;
}
