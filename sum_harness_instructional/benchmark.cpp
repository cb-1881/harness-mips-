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

double computeMFLOPS(double ops, double runtime) {
    return ops / (runtime * 1e6);  // ops divided by 1 million and time in seconds
}

double computeBandwidthUtilization(double bytes, double runtime, double peakBandwidth) {
    return ((bytes / runtime) / peakBandwidth) * 100;  // Result in percentage
}

double computeAvgMemoryLatency(double nanoseconds, double accesses) {
    if (accesses == 0) return 0.0;  // Avoid division by zero
    return nanoseconds / accesses;  // Nanoseconds per memory access
}

// Function to log results to a .log file
void logResults(const std::vector<int64_t>& problem_sizes,
                const std::vector<double>& mflops,
                const std::vector<double>& bandwidthUtilization,
                const std::vector<double>& memoryLatency) {
    std::ofstream logFile("benchmark_results.log");
    logFile << std::fixed << std::setprecision(8);  // Increased precision

    logFile << "'N': [";
    for (size_t i = 0; i < problem_sizes.size(); ++i) {
        logFile << problem_sizes[i];
        if (i != problem_sizes.size() - 1) logFile << ", ";
    }
    logFile << "],\n";

    logFile << "'MFLOPs': [";
    for (size_t i = 0; i < mflops.size(); ++i) {
        logFile << mflops[i];
        if (i != mflops.size() - 1) logFile << ", ";
    }
    logFile << "],\n";

    logFile << "'Mem_Bandwidth': [";
    for (size_t i = 0; i < bandwidthUtilization.size(); ++i) {
        logFile << bandwidthUtilization[i];
        if (i != bandwidthUtilization.size() - 1) logFile << ", ";
    }
    logFile << "],\n";

    logFile << "'Mem_Latency': [";
    for (size_t i = 0; i < memoryLatency.size(); ++i) {
        logFile << memoryLatency[i];
        if (i != memoryLatency.size() - 1) logFile << ", ";
    }
    logFile << "]\n";

    logFile.close();
}

/* The benchmarking program */
int main(int argc, char** argv) 
{
   std::cout << std::fixed << std::setprecision(2);

   #define MAX_PROBLEM_SIZE 1 << 28  // 256M
   std::vector<int64_t> problem_sizes{ MAX_PROBLEM_SIZE >> 5, MAX_PROBLEM_SIZE >> 4, 
                                       MAX_PROBLEM_SIZE >> 3, MAX_PROBLEM_SIZE >> 2, 
                                       MAX_PROBLEM_SIZE >> 1, MAX_PROBLEM_SIZE };
   std::vector<uint64_t> A(MAX_PROBLEM_SIZE);

   double BANDWIDTH = 204.8e9;  // Peak memory bandwidth (204.8 GB/s)
   double opsPerElement = 2.0;  // Assume 2 operations per element
   double bytesPerElement = sizeof(uint64_t);  // Bytes accessed per element

   // Vectors to store metrics for logging
   std::vector<double> mflops;
   std::vector<double> bandwidthUtilization;
   std::vector<double> memoryLatency;

   /* For each test size */
   for (int64_t n : problem_sizes) 
   {
      printf("Working on problem size N=%lld \n", n);

      // Set up the problem
      setup(n, &A[0]);

      // timer start
      auto start_time = std::chrono::high_resolution_clock::now();

      // sum code
      int64_t t = sum(n, &A[0]);

      // timer stop
      auto end_time = std::chrono::high_resolution_clock::now();

      // Calculate elapsed time in nanoseconds
      auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
      double runtime_ns = static_cast<double>(elapsed.count());  // Convert to double


       printf("====METRICS====\n");
      printf("Elapsed time for N=%lld is : %lf seconds\n", n, runtime_ns / 1e9);
      printf(" Sum result = %lld \n", t);

      // calc metrics
      double totalOps = opsPerElement * n;
      double totalBytes = bytesPerElement * n;

      double mf = computeMFLOPS(totalOps, runtime_ns / 1e9);  // Convert ns to seconds
      double bw = computeBandwidthUtilization(totalBytes, runtime_ns / 1e9, BANDWIDTH);
      double lat = computeAvgMemoryLatency(runtime_ns, n);  // Nanoseconds per access

      // // Store metrics for logging
      // mflops.push_back(mf);
      // bandwidthUtilization.push_back(bw);
      // memoryLatency.push_back(lat);

      //  metrics
      printf("MFLOP/s: %.2f\n", mf);
      printf("Memory Bandwidth Utilization: %.2f%%\n", bw);
      printf("Average Memory Latency: %.8e ns/access\n", lat);
      
      printf("====END_METRICS====\n");
   }


//   logResults(problem_sizes, mflops, bandwidthUtilization, memoryLatency);

   return 0;
}
