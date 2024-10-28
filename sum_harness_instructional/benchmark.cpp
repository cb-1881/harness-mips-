#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>

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


   double BANDWIDTH = 204.8e9;  // calculated from perlmutter specs
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

      // calc metrics
      double operations = element_operations * n;
      double get_total_bytes = bytes_needed * n;

      double mf = mflop_compute(operations, runtime_ns / 1e9);  // nano to seconds
      double bw = bandwith_compute(get_total_bytes, runtime_ns / 1e9, BANDWIDTH);
      double lat = latency_compute(runtime_ns, n);  // latency call

 

      //  metrics
      printf("MFLOP/s: %.2f\n", mf);
      printf("Memory Bandwidth Utilization: %.2f%%\n", bw);
      printf("Average Memory Latency: %.8e ns/access\n", lat);
      
      printf("====END_METRICS====\n");
   }




   return 0;
}
