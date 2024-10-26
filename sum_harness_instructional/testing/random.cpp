#include <iostream>
#include <random>  // Include the random library

int main() {

        // Define the size of the array
    int64_t N = 5;  // Example size, can be any positive integer

    // Create a vector to store the random numbers
    std::vector<uint64_t> A(N);
    // Create a random device to generate a seed
    std::random_device rd;

    // Initialize the mt19937_64 generator with the seed
    std::mt19937_64 generator(rd());

    // Define a distribution over the entire uint64_t range
    std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);


for(int64_t i = 0; i < N; i++){

    A[i] = distribution(generator);
}


    // Generate and print five random numbers
    for (int i = 0; i < N; ++i) {
        //uint64_t random_number = distribution(generator);
        std::cout << "Random number: " << A[i] << std::endl;
    }

    return 0;
}
