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
   printf(" inside direct_sum problem_setup, N=%lld \n", N);

    // random seed at runtime
    std::random_device seed;

    // mt19937_64 generator needs to get initialized with the seed
    std::mt19937_64 generator(seed());

    //distribution over the entire uint64_t range
    std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);

   for (int64_t i = 0; i < N; ++i)
    {
        A[i] = distribution(generator);
    }

}

int64_t sum(int64_t N, uint64_t A[]) {
    printf("Inside direct_sum perform_sum, N=%lld \n", N);
    
    int64_t total = 0;
    int64_t i = 0;  // loop index 

    
    while (i < N) {

        total += A[i];  // accumulate

        i++;  
    }



    return total; 

    printf("======END SUM=======");
}

