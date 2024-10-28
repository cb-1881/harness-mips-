#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

const double BANDWIDTH = 204.8e9;  // calculated from perlmutter specs
// Function declarations
extern void setup(int64_t N, uint64_t A[]);
extern int64_t sum(int64_t N, uint64_t A[]);

double mflop_compute(double ops, double runtime) {
    return ops / (runtime * 1e6);  // operations defided by 1million times runtime
}

double bandwith_compute(double bytes, double runtime, double peakBandwidth) {
    return ((bytes / runtime) / peakBandwidth) * 100;  // bandwith in percentage
}

double latency_compute(double nanoseconds, double accesses) {
    if (accesses == 0) return 0.0;  // if divide by zero
    return nanoseconds / accesses;  // formula for latency
}

void calculate_performance_metrics(int64_t n, std::chrono::duration<double> elapsed_time) {
    // Calculate MFLOP/s
    double ops = (n - 1) / 1e6; // (N-1) additions
    double mflops = ops / elapsed_time.count();
    printf("MFLOP/s for N=%lld is : %lf \n", n, mflops);

    // Calculate % of memory bandwidth utilized
    double bytes_accessed = n * sizeof(uint64_t) * 2;
    double percentage_bandwidth = (bytes_accessed / elapsed_time.count()) / BANDWIDTH * 100;
    printf("Memory bandwidth utilized for N=%lld is : %lf%% \n", n, percentage_bandwidth);

    // Calculate estimated memory latency
    double latency = (elapsed_time.count() / (2 * n)) * 1e9;
    printf("Estimated memory latency for N=%lld is : %lf nanoseconds\n", n, latency);
}



  // double BANDWIDTH = 204.8e9;  // calculated from perlmutter specs
   double element_operations = 2.0;  // 2 operations per element
   double bytes_needed = sizeof(uint64_t);  // bytes for manipulating metrics
/* The benchmarking program */
int main(int argc, char** argv) 
{
   std::cout << std::fixed << std::setprecision(2);

   #define MAX_PROBLEM_SIZE 1 << 28  // 256M
   std::vector<int64_t> problem_sizes{ MAX_PROBLEM_SIZE >> 5, MAX_PROBLEM_SIZE >> 4, MAX_PROBLEM_SIZE >> 3, MAX_PROBLEM_SIZE >> 2, MAX_PROBLEM_SIZE >> 1, MAX_PROBLEM_SIZE};
   std::vector<uint64_t> A(MAX_PROBLEM_SIZE);
   // double BANDWIDTH = 204.8e9;  // calculated from perlmutter specs
   // double element_operations = 2.0;  // 2 operations per element
   // double bytes_needed = sizeof(uint64_t);  // bytes for manipulating metrics



   /* For each test size */
   for (int64_t n : problem_sizes) 
   {
      printf("Working on problem size N=%lld \n", n);

     
      setup(n, &A[0]);

      // timer start
      auto start_time = std::chrono::high_resolution_clock::now();

      // sum code
      int64_t t = sum(n, &A[0]);

      // timer stop
      auto end_time = std::chrono::high_resolution_clock::now();

      // get nanoseconds
     std::chrono::duration<double, std::nano> elapsed_time = end_time - start_time;
      double runtime_ns = elapsed_time.count();



       printf("====METRICS====\n");
      printf("Elapsed time for N=%lld is : %lf seconds\n", n, runtime_ns / 1e9);
      printf(" Sum result = %lld \n", t);


      calculate_performance_metrics(n, elapsed_time);
  
      
      printf("====END_METRICS====\n");
   }




   return 0;
}
