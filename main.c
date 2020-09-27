#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum
{
   N = 2000
};

static uint32_t a[N][N];
static uint32_t b[N][N];
static uint32_t c[N][N];

int main()
{
   printf("Hello world\n");

   // set up buffers
   arc4random_buf(a, sizeof(a));
   arc4random_buf(b, sizeof(b));
   memset(c, 0x00, sizeof(c));

   for(uint32_t i = 0; i < N; i++)
   {
      for(uint32_t j = 0; j < N; j++)
      {
         for(uint32_t k = 0; k < N; k++)
         {
            c[j][i] += a[k][i] * b[j][k];
         }
      }
   }

   printf("result: %d %d ...\n", c[0][0], c[0][1]);

   return 0;
}
