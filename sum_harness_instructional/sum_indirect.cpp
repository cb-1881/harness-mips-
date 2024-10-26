#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>



void 
setup(int64_t N, uint64_t A[])
{
   printf(" inside sum_indirect problem_setup, N=%lld \n", N);

// code is based off hint that you gave us in specifications doc
  srand48(time(NULL));

   for(int64_t i = 0; i < N; i++)
    {
     A[i] = lrand48() % N;

    }

}

int64_t
sum(int64_t N, uint64_t A[])
{
   printf(" inside sum_indirect perform_sum, N=%lld \n", N);


    int64_t total = 0;
    int64_t i = 0;  // loop index 

    
    while (i < N) {

        total += A[i];  // accumulate

        i++;  
    }

    return total; 

   // printf("======END SUM=======");
   //return 0;
}

