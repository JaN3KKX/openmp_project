#include "primes_algorithms.h"
#include <omp.h>

void run_k5(long long m, long long n, const bool* primeArray, bool* result, long long blockSize) {
    long long numberOfBlocks = (n - m) / blockSize;
    if ((n - m) % blockSize != 0) numberOfBlocks++;

    #pragma omp parallel for schedule(runtime)
    for (long long i = 0; i < numberOfBlocks; i++) {
        long long low = m + i * blockSize;
        long long high = low + blockSize - 1;
        if (high > n) high = n;

        for (long long j = 2; j * j <= high; j++) {
            if (primeArray[j]) {
                long long firstMultiple = (low / j);
                if (firstMultiple <= 1) firstMultiple = j + j;
                else if (low % j) firstMultiple = (firstMultiple * j) + j;
                else firstMultiple = (firstMultiple * j);

                for (long long k = firstMultiple; k <= high; k += j) {
                    result[k - m] = false; 
                }
            }
        }
    }
}